#include <iostream>

#include "main/kv_store.h"

using std::cout;
using std::endl;

namespace kv_store {

//------------------------------------------------------------------

KVStore::KVStore() {
    cout << "Creating KVStore. CPP version: " << __cplusplus << endl;
}

//------------------------------------------------------------------

KVStore::~KVStore() {
    cout << "Destroying KVStore" << endl;
}

//------------------------------------------------------------------

void KVStore::Read(std::string key) {
    cout << "Read " << key << endl;
}

//------------------------------------------------------------------

void KVStore::Write(std::string key) {
    cout << "Write " << key << endl;
}

//------------------------------------------------------------------

}