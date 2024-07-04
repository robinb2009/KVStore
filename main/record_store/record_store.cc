#include "main/record_store/record_store.h"

#include <filesystem>
#include <glog/logging.h>

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

//------------------------------------------------------------------

} // namespace record
} // namespace kv_store