#pragma once

// The KVStore works with string keys and string values.

#include <string>

#include "main/record_store/record_store.h"

namespace kv_store {

static constexpr int kMaxKeySize = 1 * 1024 /* 1KB */;
static constexpr int kMaxValueSize = 5 * 1024 * 1024 /* 5MB */;
static const std::string kKVStoreDirName = "KVStore";

} // namespace kv_store