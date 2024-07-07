#include "main/kv_store.h"

#include <filesystem>
#include <gflags/gflags.h>
#include <glog/logging.h>

#include "main/constants.h"

namespace kv_store {

//------------------------------------------------------------------

KVStore::KVStore(std::string path) : base_path_(path + '/' + kKVStoreDirName) {
  CHECK_EQ(__cplusplus, 202002L);

  CHECK(std::filesystem::create_directory(base_path_));
  record_store_ = make_shared<record::RecordStore>(base_path_);

  LOG(INFO) << "Created KVStore";
}

//------------------------------------------------------------------

KVStore::~KVStore() {
  record_store_.reset();
  std::filesystem::remove_all(base_path_);
  LOG(INFO) << "Destroying KVStore";
}

//------------------------------------------------------------------

void KVStore::Read(std::string key) { LOG(INFO) << "Read " << key; }

//------------------------------------------------------------------

void KVStore::Write(std::string key) { LOG(INFO) << "Write " << key; }

//------------------------------------------------------------------

} // namespace kv_store