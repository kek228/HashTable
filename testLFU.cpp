#include <gtest/gtest.h> // googletest header file
#include <string>
#include <vector>
#include "LFU.h"

using namespace std;


TEST(LFUTests, trivial) {
    LFUCache<string> lfu(2);
    lfu.insert("aaa");
    auto keys = lfu.topKeys();
    auto counter1 = keys.find(1);
    ASSERT_EQ(counter1->first, 1);
    ASSERT_EQ(counter1->second.size(), 1);
    ASSERT_EQ(counter1->second[0], "aaa");
    //
    lfu.insert("bbb");
    keys = lfu.topKeys();
    counter1 = keys.find(1);
    ASSERT_EQ(counter1->first, 1);
    ASSERT_EQ(counter1->second.size(), 2);
    ASSERT_EQ(counter1->second[0], "bbb");
    ASSERT_EQ(counter1->second[1], "aaa");
    //
    lfu.insert("ccc");
    keys = lfu.topKeys();
    counter1 = keys.find(1);
    ASSERT_EQ(counter1->first, 1);
    ASSERT_EQ(counter1->second.size(), 2);
    ASSERT_EQ(counter1->second[0], "ccc");
    ASSERT_EQ(counter1->second[1], "bbb");
}
