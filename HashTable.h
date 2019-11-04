#pragma once

#include <unordered_set>
#include <memory>

template <typename KeyType, typename ValType>
struct Entry{
    enum class STATE{FREE, DEL, FILLED};

    Entry(): _key{}, _value{}, _state(STATE::FREE){}

    Entry(const KeyType &key, const ValType &value, const STATE &state):
            _key(key), _value(value), _state(state){}


    Entry& operator = (const Entry& entry){
        _key = entry._key;
        _value = entry._value;
        _state = entry._state;
    }

    Entry& operator = (Entry&& entry) noexcept {
        _key = entry._key;
        _value = entry._value;
        _state = entry._state;
    }

    bool free() const{
        return _state == STATE::FREE;
    }
    bool deleted() const{
        return _state == STATE::DEL;
    }
    bool filled() const{
        return _state == STATE::FILLED;
    }

    KeyType _key;
    ValType _value;
    STATE _state;
};

#define DEF_CAPACITY 2
#define DEF_REHASH_FACTOR 0.5

template <typename KeyType, typename ValType>
class HashTable {
public:
    using _Entry = Entry<KeyType, ValType>;
    explicit HashTable(const size_t capacity = DEF_CAPACITY, const double rehashFactor = DEF_REHASH_FACTOR):
    _capacity(capacity),
    _rehashFactor(rehashFactor),
    _filled(0){
        //
        _table.reset(new _Entry[_capacity]);
    }

    ~HashTable() = default;

    void insert(const KeyType &key, const ValType &value){
        if(static_cast<double>(_filled) / _capacity > _rehashFactor)
            _rehash();
        int iter = 0;
        int index = _hash(key, iter) % _capacity;
        if(!_ithPos(index).filled()){
            _ithPos(index) = {key, value, _Entry::STATE::FILLED};
        }
        else {
            while (_ithPos(index).filled()){
                index = _hash(key, ++iter) % _capacity;
            }
            _ithPos(index) = {key, value, _Entry::STATE::FILLED};
        }
        ++_filled;
    }

    std::unique_ptr<ValType> get(const KeyType &key){
        size_t index = _search(key);
        const _Entry &entry =  _ithPos(index);
        if(!entry.filled())
            return nullptr;
        std::unique_ptr<ValType> res(new ValType);
        *res = entry._value;
        return res;
    }

    void erase(const KeyType &key){
        size_t index = _search(key);
        _Entry &entry =  _ithPos(index);
        if(entry.filled()){
            entry._state = _Entry::STATE::DEL;
            --_filled;
        }
    }


private:
    size_t _search(const KeyType &key){
        int iter = 0;
        int index = _hash(key, iter) % _capacity;
        if(_ithPos(index).free() || _ithPos(index)._key == key)
            return index;

        while(!_ithPos(index).free() || _ithPos(index)._key != key){
            index = _hash(key, ++iter) % _capacity;
        }
        return index;
    }

    _Entry& _ithPos(const size_t i){
        return _table.get()[i];
    }

    int _hash(const KeyType &key, const int iter){
        return (std::hash<KeyType>{}(key) + iter + iter * iter);
    }

    void _rehash(){
        _capacity *= 2;
        auto oldTable = std::move(_table);
        _table.reset(new _Entry[_capacity]);

        for(size_t i = 0; i < _capacity; ++i){
            const auto &oldVal = oldTable.get()[i];
            if(oldVal.filled())
                insert(oldVal._key, oldVal._value);
        }
    }

private:
    const double _rehashFactor;
    size_t _filled;
    size_t _capacity;
    std::unique_ptr<_Entry[]> _table;
};
