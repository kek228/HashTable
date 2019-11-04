#include <gtest/gtest.h> // googletest header file
#include <string>
#include <vector>
#include "HashTable.h"
using namespace std;

TEST(HashTableTests, trivialInt){
    HashTable<int, int> testTable;
    int key = 1;
    int val = 2;
    testTable.insert(key, val);
    auto res = testTable.get(key);
    ASSERT_EQ(*res, val);
}

TEST(HashTableTests, trivial) {
    ASSERT_EQ(1,1);
    HashTable<string, string> testTable;
    vector<string> testStrings = {
            "aaaaaaa",
            "bbbbbbb",
            "ccccccc",
            "ddddddd",
            "eeeeeee",
            "fffffff",
            "ggggggg",
            "hhhhhhh",
            "iiiiiii",
            "ggggggg",
            "kkkkkkk"
    };
    for(auto &s: testStrings)
        testTable.insert(s, s);

    for(auto &str: testStrings){
        auto val = testTable.get(str);
        ASSERT_EQ(str, *val);
    }
}

TEST(HashTableTests, delTest) {
    HashTable<string, string> testTable;
    vector<string> testStrings = {
            "aaaaaaa",
            "bbbbbbb",
            "ccccccc",
            "ddddddd",
            "eeeeeee",
            "fffffff",
            "ggggggg",
            "hhhhhhh",
            "iiiiiii",
            "ggggggg",
            "kkkkkkk"
    };

    vector<string> delStrings = {
            "ccccccc",
            "ggggggg"
    };

    for(auto &s: testStrings)
        testTable.insert(s, s);

    for(auto &s: delStrings)
        testTable.erase(s);

    for(auto &str: testStrings){
        auto val = testTable.get(str);
        if(str == "ccccccc" || str == "ggggggg")
            ASSERT_EQ(val, nullptr);
        else{
            ASSERT_EQ(str, *val);
        }
    }
}


