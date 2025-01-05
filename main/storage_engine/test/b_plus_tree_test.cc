#pragma once

#include "main/storage_engine/b_plus_tree.h"
#include "main/utils/test_util.h"

using std::make_shared;
using std::shared_ptr;
using std::string;

namespace kv_store {
namespace storage_engine {
namespace test {
//------------------------------------------------------------------

class BPlusTreeTest : public utils::TestUtil {
public:
  BPlusTreeTest() { b_tree_ = make_shared<BPlusTree>(test_path_); }

protected:
  shared_ptr<BPlusTree> b_tree_;
};

//------------------------------------------------------------------

TEST_F(BPlusTreeTest, BasicTest) {
  b_tree_->Read("Hello");
  b_tree_->Write("Hello", "Hi");
}

//------------------------------------------------------------------

} // namespace test
} // namespace storage_engine
} // namespace kv_store

//------------------------------------------------------------------

TEST_MAIN()

//------------------------------------------------------------------