#include <gtest/gtest.h> // googletest header file
#include <string>
#include <vector>
#include "LFU.h"

using namespace std;


TEST(LFUTests, trivial) {
    LFU<string> lfu(2);
    lfu.insert("aaa");
    auto keys = lfu.allKeys();
    ASSERT_EQ(keys.size(), 1);
    auto counter1 = keys.find(1);
    ASSERT_EQ(counter1->second.size(), 1);
    ASSERT_EQ(counter1->second[0], "aaa");
    //
    lfu.insert("bbb");
    keys = lfu.allKeys();
    ASSERT_EQ(keys.size(), 1);
    counter1 = keys.find(1);
    ASSERT_EQ(counter1->second.size(), 2);
    ASSERT_EQ(counter1->second[0], "bbb");
    ASSERT_EQ(counter1->second[1], "aaa");
    //
    lfu.insert("ccc");
    keys = lfu.allKeys();
    ASSERT_EQ(keys.size(), 1);
    counter1 = keys.find(1);
    ASSERT_EQ(counter1->second.size(), 2);
    ASSERT_EQ(counter1->second[0], "ccc");
    ASSERT_EQ(counter1->second[1], "bbb");
}
//
TEST(LFUTests, sameKeyTest) {
    LFU<string> lfu(2);
    lfu.insert("aaa");
    lfu.insert("aaa");
    lfu.insert("aaa");
    auto keys = lfu.allKeys();
    ASSERT_EQ(keys.size(), 1);
    auto counter3 = keys.find(3);
    ASSERT_EQ(counter3->second.size(), 1);
    ASSERT_EQ(counter3->second[0], "aaa");
    //
    lfu.insert("bbb");
    lfu.insert("bbb");
    keys = lfu.allKeys();
    ASSERT_EQ(keys.size(), 2);
    auto counter2 = keys.find(2);
    ASSERT_EQ(counter2->second.size(), 1);
    ASSERT_EQ(counter2->second[0], "bbb");

    // Должен быть удален ключ bbb с частотой 2
    lfu.insert("ccc");
    keys = lfu.allKeys();
    ASSERT_EQ(keys.size(), 2);
    auto counter1 = keys.find(1);
    ASSERT_EQ(counter1->second.size(), 1);
    ASSERT_EQ(counter1->second[0], "ccc");
    //
    counter2 = keys.find(2);
    ASSERT_EQ(counter2, keys.end());
    counter3 = keys.find(3);
    ASSERT_EQ(counter3->second.size(), 1);
    ASSERT_EQ(counter3->second[0], "aaa");
}

TEST(LFUTests, topKeysTest) {
    int cap = 2;
    LFU<string> lfu(cap);
    lfu.insert("aaa");
    lfu.insert("aaa");
    lfu.insert("aaa");
    lfu.insert("bbb");
    lfu.insert("aaa");
    auto topKeys = lfu.topKeys(4);
    ASSERT_EQ(topKeys.size(), cap);
    ASSERT_EQ(topKeys[0].counter, 4);
    ASSERT_EQ(topKeys[0].keys[0], "aaa");
    //
    ASSERT_EQ(topKeys[1].counter, 1);
    ASSERT_EQ(topKeys[1].keys[0], "bbb");
}
