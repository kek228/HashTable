#include <iostream>
#include <memory>
#include "HashTableWithAnalyser.h"
using namespace std;

int main() {
    HashTableWithAnalyser<int, string> table;
    HashTableWithAnalyser<int, int> table1;
    table.topKeys(10);
    table1.allKeys();
    return 0;
}