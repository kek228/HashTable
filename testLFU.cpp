#include <gtest/gtest.h> // googletest header file
#include <string>
#include <vector>
#include "LFU.h"

using namespace std;


TEST(LFUTests, trivial) {
    LFUCache<string> lfu(2);
    lfu.insert("aaa");
    auto keys = lfu.topKeys();
    for(auto &ck: keys){
        ASSERT_EQ(ck.first, 1);
        for(auto &k: ck.second)
            ASSERT_EQ(k, "aaa");
    }

}
