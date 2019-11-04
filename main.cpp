#include <iostream>
#include <memory>
#include "HashTable.h"
using namespace std;

int main() {
    HashTable<string, string> testTable;
    testTable.insert("aaa", "bbb");
    return 0;
}