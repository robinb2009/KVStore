#pragma once

// Common interface for storage engine.

#include <string>
#include <vector>

namespace kv_store {
namespace storage_engine {

class StorageEngineInterface {
public:
  virtual std::string Read(std::string key) = 0;

  virtual void Write(std::string key, std::string value) = 0;

  struct ScanResult {
    std::vector<std::string> keys;

    // Whether all keys have been returned.
    bool eof;
  };
};

} // namespace storage_engine
} // namespace kv_store