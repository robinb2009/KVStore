#pragma once

// The KVStore works with string keys and string values.

#include <memory>
#include <string>

#include "main/record_store/record_store.h"

namespace kv_store {

class KVStore {
public:
  // Ctor.
  KVStore(std::string path);

  // Dtor.
  ~KVStore();

  // API to read a key.
  void Read(std::string key);

  // API to write a key.
  void Write(std::string key);

private:
  const std::string base_path_;
  std::shared_ptr<record::RecordStore> record_store_;
};

} // namespace kv_store