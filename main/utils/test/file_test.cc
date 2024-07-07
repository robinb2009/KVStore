#include "main/utils/file.h"

#include <memory>

#include "main/utils/test_util.h"

using std::make_shared;
using std::shared_ptr;
using std::string;

namespace kv_store {
namespace utils {
namespace test {

//------------------------------------------------------------------

class FileTest : public TestUtil {
public:
  FileTest()
      : file_name_("file.txt"),
        file_(make_shared<File>(test_path_ + '/' + file_name_)) {
    LOG(INFO) << "FileTest class instantiated.";
  }

protected:
  string file_name_;
  shared_ptr<File> file_;
};

//------------------------------------------------------------------

TEST_F(FileTest, BasicTest) {
  LOG(INFO) << "Opening file";
  file_->Open();

  string data;
  for (int ii = 0; ii < 10; ++ii) {
    auto str = RandomString(RandomInt(10, 20));
    LOG(INFO) << "Writing " << str;
    CHECK_EQ(file_->Write(data.size() /* offset */, str),
             static_cast<int>(str.size()));
    data += str;
  }

  LOG(INFO) << "Verifying data via Read.";
  CHECK_EQ(file_->Read(0 /* offset */, data.size() /* size */), data);

  file_.reset();
}

//------------------------------------------------------------------

TEST_MAIN()

//------------------------------------------------------------------

} // namespace test
} // namespace utils
} // namespace kv_store