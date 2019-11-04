#pragma once

#include "HashTable.h"
#include "LFU.h"

template<typename KeyType, typename ValType>
class HashTableWithAnalyser: public HashTable<KeyType, ValType>{
public:
    explicit HashTableWithAnalyser( const size_t capacity = DEF_CAPACITY
                                    , const double rehashFactor = DEF_REHASH_FACTOR
                                    , const size_t cacheCapacity = DEF_LRU_CAPACITY) :
                                    HashTableWithAnalyser::HashTable(capacity, rehashFactor)
                                    , _keysCache(cacheCapacity)
                                    {}

    template<typename KEY, typename VAL>
    void insert(KEY &&key, VAL &&value) {
        _keysCache.insert(key);
        HashTableWithAnalyser::HashTable.insert(key);
    }

    template<typename KEY>
    std::unique_ptr<ValType> get(KEY &&key) {
        _keysCache.insert(key);
        return HashTableWithAnalyser::HashTable.get(key);
    }

    template<typename KEY>
    void erase(KEY &&key) {
        _keysCache.insert(key);
        HashTableWithAnalyser::HashTable.erase(key);
    }

private:
    LFU<KeyType> _keysCache;
};
