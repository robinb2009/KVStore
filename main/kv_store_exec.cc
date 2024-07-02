// Executable binary for KVStore

#include <iostream>

#include "main/kv_store.h"

using std::cout;
using std::endl;

int main() {
    cout << "KVStore exec started" << endl;
    auto kv_store = kv_store::KVStore();
    return 0;
}