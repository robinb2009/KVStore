#pragma once

// Class that defines a record and how it is stored.
//
// TODO: Add checksum support.

#include <string>

namespace kv_store {
namespace record {

class Record {
public:
  explicit Record(std::string value);
  Record() = default;
  ~Record() = default;

  std::string Serialize() const;

  bool Deserialize(std::string data);

  int Size() const;

  // Accessors
  const std::string &data() const { return data_; }

private:
  // This record only contains a value string.
  std::string data_;
};

} // namespace record
} // namespace kv_store