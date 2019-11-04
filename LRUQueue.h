#pragma once

#include <unordered_map>
#include <list>

template<typename KeyType>
class LRUQueue {
public:
    using ItemCache = std::unordered_map<KeyType, typename std::list<KeyType>::iterator>;

    LRUQueue() = default;

    ~LRUQueue() = default;

    template<typename KEY>
    void insert(KEY &&item) {
        _items.emplace_front(std::forward<KEY>(item));
        _itemCache[item] = _items.begin();
    }

    KeyType pop() {
        KeyType res = _items.back();
        _items.pop_back();
        _itemCache.erase(res);
        return res;
    }

    template<typename KEY>
    void erase(KEY &&item) {
        auto listItem = _itemCache.find(item);
        _items.erase(listItem->second);
        _itemCache.erase(listItem);
    }

    size_t size(){
        return _itemCache.size();
    }

    std::vector<KeyType> getItems(){
        std::vector<KeyType> res;
        res.reserve(_items.size());
        for(const auto &i: _items)
            res.push_back(i);
        return res;
    }

private:
    ItemCache _itemCache;
    std::list<KeyType> _items;
};
