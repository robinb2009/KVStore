#pragma once

#include <string>
#include <vector>

#include "main/storage_engine/storage_engine_interface.h"

namespace kv_store {
namespace storage_engine {

static const std::string kBPlusTreeDirName = "BPlusTree";

class BPlusTree : public StorageEngineInterface {
public:
  // Ctor.
  BPlusTree(const std::string &path);

  // Dtor.
  ~BPlusTree();

  std::string Read(std::string key) override;

  void Write(std::string key, std::string value) override;

  // Scans and returns only the keys.
  ScanResult Scan(std::string start_key, int num_keys) override;

private:
  const std::string base_path_;
};

} // namespace storage_engine
} // namespace kv_store