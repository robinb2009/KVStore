#include <utility>
#include <vector>

#include "main/record_store/record.h"
#include "main/record_store/record_store.h"
#include "main/utils/test_util.h"

using std::make_pair;
using std::make_shared;
using std::pair;
using std::shared_ptr;
using std::string;
using std::vector;

DECLARE_int32(record_store_max_file_size_mb);
DECLARE_int32(record_store_max_records_per_file);

namespace kv_store {
namespace record {
namespace test {

//------------------------------------------------------------------

class RecordStoreTest : public utils::TestUtil {
public:
  RecordStoreTest() { rs_ = make_shared<RecordStore>(test_path_); }

protected:
  shared_ptr<RecordStore> rs_;
};

//------------------------------------------------------------------

// Basic test that writes and reads records.
TEST_F(RecordStoreTest, BasicTest) {
  const int num_records = 10;

  // Let's create the records.
  vector<pair<RecordStore::RecordID, shared_ptr<Record>>> records;
  for (int ii = 0; ii < num_records; ++ii) {
    RecordStore::RecordID id;
    id.file_num = 0;
    id.offset = (ii == 0) ? 0
                          : records[ii - 1].first.offset +
                                records[ii - 1].second->Size() +
                                4 /* 4 bytes for the record's size encoding */;

    auto record =
        make_shared<Record>(RandomString((ii + 1) * 1000 /* length */));
    records.push_back(make_pair(id, record));
  }

  // Let's write the records.
  LOG(INFO) << "Writing num_records one by one";
  for (int ii = 0; ii < num_records; ++ii) {
    auto id = rs_->Write(records[ii].second);
    CHECK_EQ(id.file_num, records[ii].first.file_num) << ii;
    CHECK_EQ(id.offset, records[ii].first.offset) << ii;
  }

  // Let's read back the records.
  LOG(INFO) << "Writing num_records one by one";
  for (int ii = 0; ii < num_records; ++ii) {
    auto record = rs_->Read(records[ii].first);
    CHECK(record);

    auto written_record = records[ii].second;
    CHECK_EQ(record->Size(), written_record->Size());
    CHECK(written_record->Compare(dynamic_cast<Record &>(*record)));
  }
}

//------------------------------------------------------------------

TEST_F(RecordStoreTest, RecordFileSizeExceedTest) {
  // Reduce the max record file size and write records.
  google::FlagSaver f;
  FLAGS_record_store_max_file_size_mb = 1;

  // Write 5 0.5MB records. This should create 3 record files.
  for (int ii = 0; ii < 5; ++ii) {
    auto record = make_shared<Record>(RandomString(500 * 1024 /* 500 KB */));
    auto record_id = rs_->Write(move(record));
    if (ii < 2) {
      CHECK_EQ(record_id.file_num, 0);
    } else if (ii < 4) {
      CHECK_EQ(record_id.file_num, 1);
    } else {
      CHECK_EQ(record_id.file_num, 2);
    }
  }

  // Read and validate data.
  for (int ii = 0; ii < 5; ++ii) {
    RecordStore::RecordID record_id{
        .file_num = ii % 2, .offset = (ii % 2 == 0) ? 0 : 500 * 1024 + 4};
    auto record = rs_->Read(record_id);
    CHECK(record);
    CHECK_EQ(record->Size(), 500 * 1024);
  }
}

//------------------------------------------------------------------

TEST_F(RecordStoreTest, RecordFileMaxRecordExceedTest) {
  // Reduce the max number of records.
  google::FlagSaver f;
  FLAGS_record_store_max_records_per_file = 2;

  // Write 5 records. This should create 3 record files since each record file
  // can only have 2 records per file.
  for (int ii = 0; ii < 5; ++ii) {
    auto record = make_shared<Record>(RandomString(100));
    auto record_id = rs_->Write(move(record));
    if (ii < 2) {
      CHECK_EQ(record_id.file_num, 0);
    } else if (ii < 4) {
      CHECK_EQ(record_id.file_num, 1);
    } else {
      CHECK_EQ(record_id.file_num, 2);
    }
  }

  // Read and validate data.
  for (int ii = 0; ii < 5; ++ii) {
    RecordStore::RecordID record_id{.file_num = ii % 2,
                                    .offset = (ii % 2 == 0) ? 0 : 100 + 4};
    auto record = rs_->Read(record_id);
    CHECK(record);
    CHECK_EQ(record->Size(), 100);
  }
}

//------------------------------------------------------------------

} // namespace test
} // namespace record
} // namespace kv_store

//------------------------------------------------------------------

TEST_MAIN()

//------------------------------------------------------------------