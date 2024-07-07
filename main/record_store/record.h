#pragma once

#include "main/record_store/record_interface.h"

// Record class that defines a simple string record. We don't really need this
// class, but it helps abstract out functionality for the record. We can also
// add more functionality (like checksums, additional fields) here without
// modifying RecordStore implementation.

namespace kv_store {
namespace record {

class Record : public RecordInterface {
public:
  explicit Record(std::string value);
  Record() = default;

  std::string Serialize() const override;

  bool Deserialize(std::string data) override;

  int Size() const override;

  bool Compare(const Record &record) const;

  // Accessors
  std::string value() const { return value_; }

private:
  // This record only contains a value string.
  std::string value_;
};

} // namespace record
} // namespace kv_store