#pragma once

#include <map>
#include <unordered_map>
#include <queue>
#include "LRUQueue.h"

template<typename KeyType>
class LFUCache {
public:
    explicit LFUCache(const size_t capacity) : _capacity(capacity), _filled(0) {}

    ~LFUCache() = default;

    template<typename KEY>
    void insert(KEY &&item) {
        auto valCounter = _counterMap.find(item);
        if (valCounter == _counterMap.end()) {
            _counterMap[item] = 1;
            _insertToQueues(1, item);
            ++_filled;
        } else {
            // нужно перенести в другую очередь
            auto prevCounter = valCounter->second;
            auto prevCounterQueue = _countersQueues.find(prevCounter);
            prevCounterQueue->second.erase(item);
            // пустой счетчик не нужен
            if (prevCounterQueue->second.size() == 0)
                _countersQueues.erase(prevCounterQueue);
            _insertToQueues(prevCounter + 1, item);
        }

        // удалим самый поздний элемент из самого не частого счетчика
        if (_filled > _capacity) {
            auto leastFreqEls = _countersQueues.begin();
            auto keyToErase = leastFreqEls->second.pop();
            _counterMap.erase(keyToErase);
        }
    }

    std::map<size_t, std::vector<KeyType> > topKeys() {
        std::map<size_t, std::vector<KeyType> > res;
        for (auto &it: _countersQueues) {
            res[it.first] = it.second.getItems();
        }
        return res;
    };

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

    size_t _capacity;
    size_t _filled;
    std::unordered_map<KeyType, size_t> _counterMap;
    std::map<size_t, LRUQueue<KeyType> > _countersQueues;
};