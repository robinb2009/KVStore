#pragma once

// Append only record writer. Writes records to a set of files under a specific
// directory. These records will contains the key and value stored in the db.
//
// Each record will be stored using variable size encoding:
// <4 bytes for size><Serialized record>
// (4 bytes implies a maximum record size of 2^32 - 1)

#include <string>

namespace kv_store {
namespace record {

static const std::string kRecordStoreDirName = "RecordStore";

class RecordStore {
public:
  RecordStore(const std::string &path);

private:
  const std::string base_path_;

  // The current record file being written to.
  int file_num = 0;
};

} // namespace record
} // namespace kv_store