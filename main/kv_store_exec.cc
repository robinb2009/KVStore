// Executable binary for KVStore.

#include <gflags/gflags.h>
#include <glog/logging.h>

#include "main/kv_store.h"

DECLARE_bool(logtostderr);

int main(int argc, char *argv[]) {
  // TODO(robin): Enable dumping logs to separate files on disk based on the
  // severity.
  FLAGS_logtostderr = true;
  google::InitGoogleLogging(argv[0]);

  LOG(INFO) << "KVStore exec started";
  auto kv_store = kv_store::KVStore();
  return 0;
}