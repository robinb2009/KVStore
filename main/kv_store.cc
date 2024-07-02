#include <glog/logging.h>

#include "main/kv_store.h"

namespace kv_store {

//------------------------------------------------------------------

KVStore::KVStore() {
    LOG(INFO) << "Creating KVStore.";
    CHECK_EQ(__cplusplus, 202002L);
}

//------------------------------------------------------------------

KVStore::~KVStore() {
    LOG(INFO) << "Destroying KVStore";
}

//------------------------------------------------------------------

void KVStore::Read(std::string key) {
    LOG(INFO) << "Read " << key;
}

//------------------------------------------------------------------

void KVStore::Write(std::string key) {
    LOG(INFO) << "Write " << key;
}

//------------------------------------------------------------------

}