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
  int num_records = 20;

  // Let's create the records.
  int cur_offset = 0;
  vector<pair<int /* offset */, shared_ptr<Record>>> records;
  for (int ii = 0; ii < num_records; ++ii) {
    // Random string between 10 and 10,000 bytes.
    const int size = RandomInt(10, 10000);
    string data = RandomString(size);
    auto record = make_shared<Record>(data);

    records.push_back(make_pair(cur_offset, record));
    cur_offset += size + 4;
  }

  // Add 1 byte record.
  {
    string data = RandomString(1);
    auto record = make_shared<Record>(data);
    records.push_back(make_pair(cur_offset, record));
    cur_offset += 1 + 4;
    num_records++;
  }

  // Add 5mb record.
  {
    int size = 5 * 1024 * 1024;
    string data = RandomString(size);
    auto record = make_shared<Record>(data);
    records.push_back(make_pair(cur_offset, record));
    cur_offset += size + 4;
    num_records++;
  }

  // Let's write the records.
  LOG(INFO) << "Writing " << num_records << " records";
  for (int ii = 0; ii < num_records; ++ii) {
    int offset = rs_->Write(records[ii].second);
    CHECK_EQ(offset, records[ii].first);
  }

  // Let's read back the records.
  LOG(INFO) << "Reading " << num_records << " records";
  for (int ii = 0; ii < num_records; ++ii) {
    auto record = rs_->Read(records[ii].first);
    CHECK(record);

    CHECK_EQ(record->Size(), records[ii].second->Size());
    CHECK_EQ(record->data(), records[ii].second->data());
  }
}

//------------------------------------------------------------------

} // namespace test
} // namespace record
} // namespace kv_store

//------------------------------------------------------------------

TEST_MAIN()

//------------------------------------------------------------------