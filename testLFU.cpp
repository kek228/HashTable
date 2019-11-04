#include <gtest/gtest.h> // googletest header file
#include <string>
#include <vector>
#include "LFU.h"

using namespace std;


TEST(LFUTests, trivial) {
    LFUCache<string> lfu(2);
    lfu.insert("aaa");
    auto keys = lfu.topKeys();
    ASSERT_EQ(keys.size(), 1);
    auto counter1 = keys.find(1);
    ASSERT_EQ(counter1->second.size(), 1);
    ASSERT_EQ(counter1->second[0], "aaa");
    //
    lfu.insert("bbb");
    keys = lfu.topKeys();
    ASSERT_EQ(keys.size(), 1);
    counter1 = keys.find(1);
    ASSERT_EQ(counter1->second.size(), 2);
    ASSERT_EQ(counter1->second[0], "bbb");
    ASSERT_EQ(counter1->second[1], "aaa");
    //
    lfu.insert("ccc");
    keys = lfu.topKeys();
    ASSERT_EQ(keys.size(), 1);
    counter1 = keys.find(1);
    ASSERT_EQ(counter1->second.size(), 2);
    ASSERT_EQ(counter1->second[0], "ccc");
    ASSERT_EQ(counter1->second[1], "bbb");
}
//
TEST(LFUTests, sameKeyTest) {
    LFUCache<string> lfu(2);
    lfu.insert("aaa");
    lfu.insert("aaa");
    lfu.insert("aaa");
    auto keys = lfu.topKeys();
    ASSERT_EQ(keys.size(), 1);
    auto counter3 = keys.find(3);
    ASSERT_EQ(counter3->second.size(), 1);
    ASSERT_EQ(counter3->second[0], "aaa");
//    //
    lfu.insert("bbb");
    lfu.insert("bbb");
    keys = lfu.topKeys();
    ASSERT_EQ(keys.size(), 2);
    auto counter2 = keys.find(2);
    ASSERT_EQ(counter2->second.size(), 1);
    ASSERT_EQ(counter2->second[0], "bbb");
    //
    lfu.insert("ccc");
    keys = lfu.topKeys();
    for (auto &k: keys) {
        cout << k.first;
    }

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
