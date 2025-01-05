#include "main/record_store/record_store.h"

#include <filesystem>
#include <glog/logging.h>
#include <mutex>

#include "main/record_store/record.h"

using std::make_shared;
using std::shared_ptr;
using std::string;

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
    : path_(path + "/" + kRecordFileName) {
  CHECK_EQ(__cplusplus, 202002L);
  CHECK(!path.empty());

  PCHECK(std::filesystem::exists(path));
  PCHECK(std::filesystem::is_directory(path));

  file_ = make_shared<utils::File>(path_);
  CHECK(file_);

  file_->Open();
  size_.store(0);

  LOG(INFO) << "Created RecordStore";
}

//------------------------------------------------------------------

RecordStore::~RecordStore() {
  PCHECK(std::filesystem::remove(path_));
  LOG(INFO) << "Destroyed RecordStore";
}

//------------------------------------------------------------------

int RecordStore::Write(shared_ptr<Record> record) {
  CHECK(record);
  const int record_size = record->Size();
  CHECK_LE(record_size, kMaxRecordSize);
  CHECK_GT(record_size, 0);

  const int offset = size_.fetch_add(record_size + 4);

  // Every write will write to a different range, so we don't need to worry
  // about synchronisation here. We don't overwrite records.
  const string size_str = SizeToStr(static_cast<uint32_t>(record_size));
  CHECK_EQ(file_->Write(offset, size_str), 4);
  CHECK_EQ(file_->Write(offset + 4, record->Serialize()), record_size);

  LOG(INFO) << "Wrote record at offset " << offset << " of size "
            << record_size;

  return offset;
}

//------------------------------------------------------------------

shared_ptr<Record> RecordStore::Read(const int offset) {
  CHECK_LT(offset, size_.load());
  const string size_str = file_->Read(offset, 4);
  CHECK_EQ(size_str.size(), 4U);

  const int record_size = static_cast<int>(StrToSize(size_str));
  CHECK_LE(record_size, kMaxRecordSize);

  string data = file_->Read(offset + 4, record_size);
  auto record = make_shared<Record>();
  record->Deserialize(data);

  return record;
}

//------------------------------------------------------------------

} // namespace record
} // namespace kv_store