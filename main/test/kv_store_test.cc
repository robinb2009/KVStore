#include "main/kv_store.h"

int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);

  auto kv_store = kv_store::KVStore();
  kv_store.Read("Key1");
  kv_store.Write("Key2");
  return 0;
}