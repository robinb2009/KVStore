// Executable binary for KVStore.

#include <glog/logging.h>

#include "main/kv_store.h"

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);

  LOG(INFO) << "KVStore exec started";
  auto kv_store = kv_store::KVStore();
  return 0;
}