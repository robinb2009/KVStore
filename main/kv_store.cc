#include <gflags/gflags.h>
#include <glog/logging.h>

#include "main/kv_store.h"

DEFINE_int32(kv_store_max_value_size_mb, 5,
             "The maximium size of the value for each key-value pair to be "
             "stored in the KVStore.");

namespace kv_store {

//------------------------------------------------------------------

KVStore::KVStore() {
  LOG(INFO) << "Creating KVStore. Max value size: "
            << FLAGS_kv_store_max_value_size_mb;
  CHECK_EQ(__cplusplus, 202002L);
}

//------------------------------------------------------------------

KVStore::~KVStore() { LOG(INFO) << "Destroying KVStore"; }

//------------------------------------------------------------------

void KVStore::Read(std::string key) { LOG(INFO) << "Read " << key; }

//------------------------------------------------------------------

void KVStore::Write(std::string key) { LOG(INFO) << "Write " << key; }

//------------------------------------------------------------------

} // namespace kv_store