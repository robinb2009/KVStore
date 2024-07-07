#pragma once

// Simple class for file operations with strings. Open is not thread safe. Read
// and Write are thread safe since they rely on 'pread' and 'pwrite'. Caller has
// to worry about data races. The file is closed upon destruction.

#include <string>

namespace kv_store {
namespace utils {

class File {
public:
  // Path should not be empty.
  File(std::string path);

  ~File();

  // Always opens with fixed set of modes and flags.
  void Open();

  // Offset and size are in bytes. Read may be partial (pread behaviour).
  std::string Read(int offset, int size);

  // offset is in bytes. Returns the number of bytes written.
  int Write(int offset, const std::string &data);

private:
  std::string path_;
  int fd_ = -1;

private:
  // Let's disallow copy and assign.
  File(File &f) = delete;
  File &operator=(const File &f) = delete;
};

} // namespace utils
} // namespace kv_store