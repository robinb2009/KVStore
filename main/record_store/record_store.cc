#include "main/record_store/record_store.h"

#include <filesystem>
#include <glog/logging.h>

using std::shared_ptr;
using std::string;

namespace kv_store {
namespace record {

//------------------------------------------------------------------

RecordStore::RecordStore(const string &path)
    : base_path_(path + '/' + kRecordStoreDirName) {
  CHECK_EQ(__cplusplus, 202002L);
  CHECK(std::filesystem::create_directory(base_path_));
  LOG(INFO) << "Created RecordStore";
}

//------------------------------------------------------------------

RecordStore::RecordID RecordStore::Write(shared_ptr<RecordInterface> record) {
  CHECK(record);
  RecordID id;
  return id;
}

//------------------------------------------------------------------

shared_ptr<RecordInterface> RecordStore::Read(const RecordID record_id) {
  CHECK_GE(record_id.file_num, 0);
  CHECK_GE(record_id.offset, 0);

  shared_ptr<RecordInterface> record;
  return record;
}

//------------------------------------------------------------------

} // namespace record
} // namespace kv_store