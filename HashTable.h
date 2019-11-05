#pragma once
#include <unordered_set>
#include <memory>

template<typename KeyType, typename ValType>
struct Entry {
    enum class STATE{EMPTY, DEL, FILLED};
    Entry() : _key{}, _value{}, _state(STATE::EMPTY) {}

    Entry(const KeyType &key, const ValType &value, STATE state) :
            _key(key), _value(value), _state(state) {}


    Entry(const Entry &) = default;

    Entry(Entry &&) noexcept = default;

    Entry &operator=(const Entry &entry) {
        _key = entry._key;
        _value = entry._value;
        _state = entry._state;
        return *this;
    }

    Entry &operator=(Entry &&entry) noexcept {
        _key = entry._key;
        _value = entry._value;
        _state = entry._state;
        return *this;
    }

    bool deleted(){
        return _state == STATE::DEL;
    }

    bool empty(){
        return _state == STATE::EMPTY;
    }

    bool filled(){
        return _state == STATE::FILLED;
    }


    KeyType _key;
    ValType _value;
    STATE _state;
};

#define DEF_CAPACITY 16
#define DEF_REHASH_FACTOR 0.5

template<typename KeyType, typename ValType>
class HashTable {
public:
    using _Entry = Entry<KeyType, ValType>;

    explicit HashTable(const size_t capacity = DEF_CAPACITY, const double rehashFactor = DEF_REHASH_FACTOR) :
            _capacity(capacity),
            _rehashFactor(rehashFactor),
            _filled(0) {
        //
        _table.reset(new _Entry[_capacity]);
    }

    virtual ~HashTable() = default;

    template<typename KEY, typename VAL>
    void insert(KEY &&key, VAL &&value) {
        if (static_cast<double>(_filled) / _capacity >= _rehashFactor)
            _rehash();
        size_t iter = 0;
        size_t index = _hash(key, iter) % _capacity;
        while (!_ithPos(index).empty() && !_ithPos(index).deleted() && _ithPos(index)._key != key) {
            index = _hash(key, ++iter) % _capacity;
        }

        if(_ithPos(index).deleted() || _ithPos(index).empty()){
            ++_filled;
        }
        _ithPos(index) = {key, value, _Entry::STATE::FILLED};
    }

    template<typename KEY>
    _Entry* get(KEY &&key) {
        size_t iter = 0;
        size_t index = _hash(key, iter) % _capacity;
        while(!_ithPos(index).empty()){
            if(_ithPos(index)._key == key){
                if(_ithPos(index).deleted())
                    return nullptr;
                return _table.get() + index;
            }
            index = _hash(key, ++iter) % _capacity;
        }
        return nullptr;
    }

    template<typename KEY>
    void erase(KEY &&key) {
        size_t iter = 0;
        size_t index = _hash(key, iter) % _capacity;

        while(!_ithPos(index).empty()){
            if(_ithPos(index)._key == key){
                _ithPos(index)._state = _Entry::STATE::DEL;
                break;
            }
            index = _hash(key, ++iter) % _capacity;
        }
    }

    size_t size() {
        return _filled;
    }

private:
    _Entry &_ithPos(const size_t i) {
        return _table.get()[i];
    }

    size_t _hash(const KeyType &key, const size_t iter) {
        return (std::hash<KeyType>{}(key) + iter + iter * iter);
    }

    void _rehash() {
        size_t _oldCapacity = _capacity;
        _capacity *= 2;
        _filled = 0;
        auto oldTable = std::move(_table);
        _table.reset(new _Entry[_capacity]);

        for (size_t i = 0; i < _oldCapacity; ++i) {
            auto &oldVal = oldTable.get()[i];
            if (oldVal.filled())
                insert(oldVal._key, oldVal._value);
        }
    }

private:
    size_t _capacity;
    const double _rehashFactor;
    size_t _filled;
    std::unique_ptr<_Entry[]> _table;
};
