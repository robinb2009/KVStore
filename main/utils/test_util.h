#pragma once

// Basic test utility class. Let's keep common test functionality here.

#include <gflags/gflags.h>
#include <glog/logging.h>
#include <gtest/gtest.h>
#include <string>

// Basic test main macro.
#define TEST_MAIN()                                                            \
  int main(int argc, char *argv[]) {                                           \
    google::InitGoogleLogging(argv[0]);                                        \
    testing::InitGoogleTest(&argc, argv);                                      \
    return RUN_ALL_TESTS();                                                    \
  }

namespace kv_store {
namespace utils {

class TestUtil : public ::testing::Test {
public:
  // Ctor.
  TestUtil();

protected:
  std::string RandomString(int length);
  int RandomInt(int from, int to);

protected:
  std::string test_path_;
};

} // namespace utils
} // namespace kv_store