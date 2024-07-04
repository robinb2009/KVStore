#pragma once

// Append only record writer. Writes records to a set of files under a specific
// directory.
//
// Each record will be stored using variable size encoding:
// <4 bytes for size><serialized record: string>
// (4 bytes implies a maximum record size of 2^32 - 1)

#include <memory>
#include <string>

#include "main/record_store/record_interface.h"

namespace kv_store {
namespace record {

static const std::string kRecordStoreDirName = "RecordStore";

// TODO(robin): Use templates instead of RecordInterface? Might be safe to
// assume that a record store
class RecordStore {
public:
  RecordStore(const std::string &path);

  // Struct that uniquely identifies a record.
  struct RecordID {
    int file_num = -1;
    int offset = -1;
  };

  // Writes the record. Returns the record id.
  RecordID Write(std::shared_ptr<RecordInterface> record);

  // Returns the record.
  std::shared_ptr<RecordInterface> Read(const RecordID record_id);

private:
  const std::string base_path_;

  // The current record file being written to.
  int file_num = 0;
};

} // namespace record
} // namespace kv_store