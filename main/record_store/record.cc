#include "main/record_store/record.h"

using std::move;
using std::string;

namespace kv_store {
namespace record {

//------------------------------------------------------------------

Record::Record(std::string value) : value_(move(value)) {}

//------------------------------------------------------------------

string Record::Serialize() const { return value_; }

//------------------------------------------------------------------

bool Record::Deserialize(std::string data) {
  value_ = move(data);
  return true;
}

//------------------------------------------------------------------

} // namespace record
} // namespace kv_store