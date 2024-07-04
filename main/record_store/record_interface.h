#pragma once

#include <string>

// Record interface.

namespace kv_store {
namespace record {

class RecordInterface {
public:
  // Returns serialized record in string form.
  virtual std::string Serialize() const = 0;

  // Returns whether the deserialization succeeded.
  virtual bool Deserialize(std::string data) = 0;
};

} // namespace record
} // namespace kv_store