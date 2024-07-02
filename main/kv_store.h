#pragma once

#include <string>

namespace kv_store {

class KVStore {
  public:
    // Ctor.
    KVStore();
    
    // Dtor.
    ~KVStore();

    // API to read a key.
    void Read(std::string key);

    // API to write a key.
    void Write(std::string key);
};

}