#include "main/record_store/record.h"

using std::move;
using std::string;

namespace kv_store {
namespace record {

//------------------------------------------------------------------

Record::Record(std::string data) : data_(move(data)) {}

//------------------------------------------------------------------

string Record::Serialize() const { return data_; }

//------------------------------------------------------------------

bool Record::Deserialize(std::string data) {
  data_ = move(data);
  return true;
}

//------------------------------------------------------------------

int Record::Size() const { return data_.size(); }

//------------------------------------------------------------------

} // namespace record
} // namespace kv_store