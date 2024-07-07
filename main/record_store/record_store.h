#pragma once

// Append only record writer. Writes records to a set of files under a specific
// directory.
//
// Each record will be stored using variable size encoding:
// <4 bytes for size><serialized record: string>
// (4 bytes implies a maximum record size of 2^32 - 1)
//
// This class is thread safe.
//
// Current implementation only writes one record at a time. TODO: Support better
// parallelization.

#include <memory>
#include <shared_mutex>
#include <string>

#include "main/record_store/record_interface.h"
#include "main/utils/file.h"

namespace kv_store {
namespace record {

static const std::string kRecordStoreDirName = "RecordStore";
static const std::string kRecordFileNamePrefix = "File_";

// TODO(robin): Use templates instead of RecordInterface? Might be safe to
// assume that a record store
class RecordStore {
public:
  RecordStore(const std::string &path);
  ~RecordStore();

  // Struct that uniquely identifies a record.
  struct RecordID {
    int file_num = -1;
    int offset = -1;

    std::string ToString() const {
      return "{ file_num: " + std::to_string(file_num) +
             ", offset: " + std::to_string(offset) + " }";
    }
  };

  // Writes the record. Returns the record id.
  RecordID Write(std::shared_ptr<RecordInterface> record);

  // Returns the record.
  std::shared_ptr<RecordInterface> Read(const RecordID record_id);

private:
  // Creates and opens a new record file. This API must be called under
  // spinlock.
  void OpenNewRecordFile();

  std::string GetRecordFilePath(int file_num);

private:
  const std::string base_path_;

  mutable std::shared_mutex mutex_;

  // The current record file being written to, and some additional information.
  int file_num_ = -1;
  std::shared_ptr<utils::File> file_;
  int num_records_in_file_ = 0;
  int size_bytes_ = 0;
};

} // namespace record
} // namespace kv_store