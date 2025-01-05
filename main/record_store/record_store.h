#pragma once

// Append only record writer. Writes records to a single record file.
//
// Each record will be stored using variable size encoding:
// <4 bytes for size><serialized record: string>
// (4 bytes implies a maximum record size of 2^32 - 1)
//
// This class is thread safe.

#include <atomic>
#include <memory>
#include <string>

#include "main/record_store/record.h"
#include "main/utils/file.h"

namespace kv_store {
namespace record {

// constants
static const std::string kRecordFileName = "record_file.txt";
static const int kMaxRecordSize = 5 * 1024 * 1024 /* 5MB */;

class RecordStore {
public:
  RecordStore(const std::string &path);
  ~RecordStore();

  // Writes the record. Returns the offset. Returns -1 write fails.
  int Write(std::shared_ptr<Record> record);

  // Returns the record. Returns nullptr if read fails.
  std::shared_ptr<Record> Read(const int offset);

private:
  // Record file path.
  const std::string path_;

  // The record file.
  std::shared_ptr<utils::File> file_;

  // Size in bytes of the record file.
  std::atomic<int> size_;
};

} // namespace record
} // namespace kv_store