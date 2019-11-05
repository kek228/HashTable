#include <gtest/gtest.h> // googletest header file
#include <string>
#include <vector>
#include "HashTable.h"

using namespace std;

TEST(HashTableTests, trivialInt) {
    HashTable<int, int> testTable;
    testTable.insert(1, 1);
    testTable.insert(2, 2);
    auto res = testTable.get(1);
    ASSERT_EQ(*res, 1);
    //
    res = testTable.get(3);
    ASSERT_EQ(res, nullptr);
    //
    testTable.insert(2, 1);
    res = testTable.get(2);
    ASSERT_EQ(*res, 1);
    //
    testTable.erase(2);
    res = testTable.get(2);
    ASSERT_EQ(res, nullptr);

}

TEST(HashTableTests, trivial) {
    ASSERT_EQ(1, 1);
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
    for (auto &s: testStrings)
        testTable.insert(s, s);

    for (auto &str: testStrings) {
        auto val = testTable.get(str);
        ASSERT_EQ(str, *val);
    }
}

TEST(HashTableTests, delTest) {
    HashTable<string, string> testTable(2);
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

    for (auto &s: testStrings)
        testTable.insert(s, s);

    for (auto &s: delStrings)
        testTable.erase(s);

    for (auto &str: testStrings) {
        auto val = testTable.get(str);
        if (str == "ccccccc" || str == "ggggggg")
            ASSERT_EQ(val, nullptr);
        else {
            ASSERT_EQ(str, *val);
        }
    }
}


