#pragma once

#include <map>
#include <unordered_map>
#include <queue>
#include "LRUQueue.h"

#define DEF_LFU_CAPACITY 1024


template<typename KeyType>
struct KeysWithFreq {

    size_t counter;
    std::vector<KeyType> keys;
};

template<typename KeyType>
class LFU {
public:
    explicit LFU(const size_t capacity = DEF_LFU_CAPACITY) : _capacity(capacity), _filled(0) {}

    ~LFU() = default;

    template<typename KEY>
    void insert(KEY &&item) {
        auto keyCounter = _keyToCounter.find(item);
        if (keyCounter == _keyToCounter.end()) {
            ++_filled;
            if (_filled > _capacity) {
                // удалим самый поздний элемент из самого не частого счетчика
                auto leastCounter = _countersQueues.begin();
                KeyType leastFreqKey = leastCounter->second.pop();
                _keyToCounter.erase(leastFreqKey);
                if (leastCounter->second.size() == 0)
                    _countersQueues.erase(leastCounter);
                --_filled;
            }
            _keyToCounter[item] = 1;
            _insertToQueues(1, item);
        } else {
            // нужно перенести в другую очередь
            auto prevCounter = keyCounter->second;
            auto prevCounterQueue = _countersQueues.find(prevCounter);
            prevCounterQueue->second.erase(item);
            // пустой счетчик не нужен
            if (prevCounterQueue->second.size() == 0)
                _countersQueues.erase(prevCounterQueue);
            _insertToQueues(prevCounter + 1, item);
            keyCounter->second++;
        }
    }

    std::map<size_t, std::vector<KeyType>> allKeys() {
        std::map<size_t, std::vector<KeyType> > res;
        for (auto &it: _countersQueues) {
            res[it.first] = it.second.getItems();
        }
        return res;
    };

    std::vector<KeysWithFreq<KeyType>> topKeys(int n) {
        if (n <= 0)
            return {};
        std::vector<KeysWithFreq<KeyType>> res;
        for (auto rit = _countersQueues.rbegin(); rit != _countersQueues.rend(); ++rit) {
            res.push_back({rit->first, {}});
            auto items = rit->second.getItems();
            for (auto &i: items) {
                res.back().keys.push_back(i);
                --n;
                if (n == 0) {
                    return res;
                }
            }
        }
        return res;
    }

private:
    template<typename KEY>
    void _insertToQueues(const size_t counter, KEY &&item) {
        auto counterQueue = _countersQueues.find(counter);
        if (counterQueue == _countersQueues.end()) {
            auto inserted = _countersQueues.emplace(counter, LRUQueue<KeyType>());
            inserted.first->second.insert(item);
            return;
        }
        counterQueue->second.insert(item);
    }

private:
    size_t _capacity;
    size_t _filled;
    std::unordered_map<KeyType, size_t> _keyToCounter;
    std::map<size_t, LRUQueue<KeyType> > _countersQueues;
};