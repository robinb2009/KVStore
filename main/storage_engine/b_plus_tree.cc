#include "main/storage_engine/b_plus_tree.h"

#include <filesystem>
#include <glog/logging.h>

using std::string;

namespace kv_store {
namespace storage_engine {

//------------------------------------------------------------------

BPlusTree::BPlusTree(const string &path)
    : base_path_(path + '/' + kBPlusTreeDirName) {
  CHECK_EQ(__cplusplus, 202002L);
  CHECK(std::filesystem::create_directory(base_path_));
  LOG(INFO) << "Created BPlusTree based storage engine.";
}

//------------------------------------------------------------------

BPlusTree::~BPlusTree() {
  std::filesystem::remove_all(base_path_);
  LOG(INFO) << "Destroyed BPlusTree based storage engine.";
}

//------------------------------------------------------------------

string BPlusTree::Read(string key) {
  LOG(INFO) << "BPlusTree::Read " << key;
  return string();
}

//------------------------------------------------------------------

void BPlusTree::Write(string key, string value) {
  LOG(INFO) << "BPlusTree::Write " << key << " " << value;
  return;
}

//------------------------------------------------------------------

StorageEngineInterface::ScanResult BPlusTree::Scan(string start_key,
                                                   int num_keys) {
  LOG(INFO) << "BPlusTree::Scan " << start_key << " " << num_keys;
  ScanResult res;
  return res;
}

//------------------------------------------------------------------

} // namespace storage_engine
} // namespace kv_store