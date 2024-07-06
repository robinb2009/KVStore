#include "main/utils/test_util.h"

#include <cstdlib>

using std::string;

DECLARE_bool(logtostderr);

namespace kv_store {
namespace utils {

//------------------------------------------------------------------

TestUtil::TestUtil() {
  auto test_dir = std::getenv("TEST_UNDECLARED_OUTPUTS_DIR");
  CHECK(test_dir);
  test_path_ = string(test_dir);

  FLAGS_logtostderr = true;

  srand(time(NULL));
}

//------------------------------------------------------------------

int TestUtil::RandomInt(int from, int to) {
  int width = to - from + 1;
  CHECK_GT(width, 0);

  return (rand() % width) + from;
}

//------------------------------------------------------------------

string TestUtil::RandomString(int length) {
  CHECK_GT(length, 0);
  auto randchar = []() -> char {
    const char charset[] = "0123456789"
                           "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                           "abcdefghijklmnopqrstuvwxyz";
    const size_t max_index = (sizeof(charset) - 1);
    return charset[rand() % max_index];
  };

  string str(length, 0);
  std::generate_n(str.begin(), length, randchar);
  return str;
}

//------------------------------------------------------------------

} // namespace utils
} // namespace kv_store