#include "main/utils/file.h"

#include <fcntl.h>
#include <glog/logging.h>

using std::string;

namespace kv_store {
namespace utils {

//------------------------------------------------------------------

File::File(std::string path) : path_(move(path)) { CHECK(!path_.empty()); }

//------------------------------------------------------------------

File::~File() {
  if (fd_ >= 0) {
    PCHECK(close(fd_) >= 0);
  }
}

//------------------------------------------------------------------

void File::Open() {
  auto mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
  fd_ = open(path_.c_str() /* pathname */, O_RDWR | O_CREAT /* flags */,
             mode /* mode */);
  PCHECK(fd_ >= 0) << path_;
}

//------------------------------------------------------------------

string File::Read(int offset, int size) {
  CHECK_GE(fd_, 0);
  CHECK_GT(size, 0);
  CHECK_GE(offset, 0);

  char buf[size];
  const auto num_bytes_read = pread(fd_, buf, size /* count */, offset);
  PCHECK(num_bytes_read >= 0);

  if (num_bytes_read != size) {
    LOG(INFO) << "Partial bytes read: " << num_bytes_read
              << ", requested: " << size;
  }

  return string(buf, num_bytes_read);
}

//------------------------------------------------------------------

int File::Write(int offset, const string &data) {
  CHECK_GE(fd_, 0);
  CHECK_GT(data.size(), 0U);

  const auto num_bytes_written =
      pwrite(fd_, data.c_str(), data.size() /* count */, offset);
  PCHECK(num_bytes_written >= 0);
  return num_bytes_written;
}

//------------------------------------------------------------------

} // namespace utils
} // namespace kv_store