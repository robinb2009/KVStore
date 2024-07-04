#include "main/kv_store.h"

#include <cstdlib>
#include <gflags/gflags.h>
#include <glog/logging.h>
#include <gtest/gtest.h>
#include <iostream>

using std::string;

DECLARE_bool(logtostderr);

//------------------------------------------------------------------

TEST(KVStoreTest, DummyTest) {
  LOG(INFO) << "Dummy test";

  auto test_dir = std::getenv("TEST_UNDECLARED_OUTPUTS_DIR");
  CHECK(test_dir);

  auto kv_store = kv_store::KVStore(string(test_dir));
  kv_store.Read("Key1" /* key */);
  kv_store.Write("Key2" /* key */);
}

//------------------------------------------------------------------

int main(int argc, char *argv[]) {
  FLAGS_logtostderr = true;
  google::InitGoogleLogging(argv[0]);
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}