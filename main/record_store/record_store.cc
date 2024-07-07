#include "main/record_store/record_store.h"

#include <filesystem>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <mutex>

#include "main/record_store/record.h"

using std::make_shared;
using std::shared_ptr;
using std::string;

DEFINE_int32(record_store_max_records_per_file, 1000,
             "Maximum allowed number of records that can be stored in a single "
             "record file.");

DEFINE_int32(record_store_max_file_size_mb, 10,
             "Maximum allowed size (in mb) of a single record file.");

DEFINE_int32(record_store_max_record_size_bytes, 1024 * 1024,
             "Maximum allowed size (in mb) of a single record file.");

namespace kv_store {
namespace record {

namespace {

string SizeToStr(const uint32_t size) {
  const char *a = reinterpret_cast<const char *>(&size);
  string ret(a, 4);
  CHECK_EQ(ret.size(), 4U);
  return ret;
}

// We do not verify that str is 4 characters long.
uint32_t StrToSize(const string &str) {
  const uint32_t x = *reinterpret_cast<const uint32_t *>(str.c_str());
  return x;
}

} // anonymous namespace

//------------------------------------------------------------------

RecordStore::RecordStore(const string &path)
    : base_path_(path + '/' + kRecordStoreDirName) {
  CHECK_EQ(__cplusplus, 202002L);
  PCHECK(std::filesystem::create_directory(base_path_));
  LOG(INFO) << "Created RecordStore";
}

//------------------------------------------------------------------

RecordStore::~RecordStore() {
  std::filesystem::remove_all(base_path_);
  LOG(INFO) << "Destroyed RecordStore";
}

//------------------------------------------------------------------

RecordStore::RecordID RecordStore::Write(shared_ptr<RecordInterface> record) {
  CHECK(record);
  CHECK_LE(record->Size(), FLAGS_record_store_max_record_size_bytes);

  std::unique_lock ul(mutex_);

  if (file_num_ == -1 ||
      num_records_in_file_ >= FLAGS_record_store_max_records_per_file ||
      size_bytes_ + record->Size() >
          FLAGS_record_store_max_file_size_mb * 1024 * 1024) {
    OpenNewRecordFile();
  }

  RecordID id;
  id.offset = size_bytes_;
  id.file_num = file_num_;

  LOG(INFO) << "Writing record " << id.ToString();

  // Write the record.
  string serialized_record = record->Serialize();
  CHECK_EQ(file_->Write(id.offset, SizeToStr(serialized_record.size())), 4);
  CHECK_EQ(file_->Write(id.offset + 4, serialized_record),
           static_cast<int>(serialized_record.size()));

  // Update the stats.
  size_bytes_ += 4 + serialized_record.size();
  num_records_in_file_++;

  return id;
}

//------------------------------------------------------------------

shared_ptr<RecordInterface> RecordStore::Read(const RecordID record_id) {
  CHECK_GE(record_id.file_num, 0);
  CHECK_GE(record_id.offset, 0);
  LOG(INFO) << "Reading record " << record_id.ToString();

  shared_ptr<utils::File> file;

  {
    std::shared_lock sl(mutex_);
    CHECK_LE(record_id.file_num, file_num_);
    if (file_num_ == record_id.file_num) {
      CHECK_GE(size_bytes_, record_id.offset);
      file = file_;
    }
  }

  // TODO: Use a cache of sorts so that we don't open too many fds for the
  // same record file.
  if (!file) {
    file = make_shared<utils::File>(GetRecordFilePath(record_id.file_num));
    file->Open();
  }

  // Read the record size.
  const string sz_str = file->Read(record_id.offset, 4);
  CHECK_EQ(sz_str.size(), 4U);
  const int sz = StrToSize(sz_str);
  CHECK_GT(sz, 0);
  CHECK_LE(sz, FLAGS_record_store_max_record_size_bytes);

  // Read the record.
  const string record_str = file->Read(record_id.offset + 4, sz);
  CHECK_EQ(record_str.size(), static_cast<size_t>(sz));

  // TODO: Abstract this out. Maybe create a RecordFactory or something? See
  // design patterns.
  auto record = make_shared<Record>();
  CHECK(record->Deserialize(move(record_str)));
  return record;
}

//------------------------------------------------------------------
//                           Helper Methods
//------------------------------------------------------------------

void RecordStore::OpenNewRecordFile() {
  // Ensure that the mutex is exclusively locked.
  CHECK(!mutex_.try_lock_shared());

  // Deleting file_ will close the file.
  file_.reset();

  file_num_++;
  num_records_in_file_ = 0;
  size_bytes_ = 0;

  LOG(INFO) << "Opening a new record file " << file_num_;
  file_ = make_shared<utils::File>(GetRecordFilePath(file_num_));
  file_->Open();
}

//------------------------------------------------------------------

string RecordStore::GetRecordFilePath(int file_num) {
  return base_path_ + '/' + kRecordFileNamePrefix + std::to_string(file_num);
}

//------------------------------------------------------------------

} // namespace record
} // namespace kv_store