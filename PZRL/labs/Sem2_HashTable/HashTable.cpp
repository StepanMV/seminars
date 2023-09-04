#include "HashTable.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

using KeyType = std::string;
using ValueType = double;

const bool debugMode = false;

//! Конструктор
HashTable::HashTable(size_t size) noexcept {
    size = size == 0 ? 100 : size;
    table = std::vector<std::list<std::pair<KeyType, ValueType>>>(size);
    _capacity = size;
    _filled = 0;
}

//! Вставка элемента в хеш-таблицу
//! Если при вставке обнаруживается, что LoadFactor таблицы превышает 0.75, то таблица расширяется в 2 раза.
void HashTable::insert(const KeyType &key, const ValueType &value) {
    if (getLoadFactor() > 0.75) {
        _capacity *= 2;
        _filled = 0;
        if(debugMode) std::cout << "NEW CAPACITY: " << _capacity << std::endl;
        std::list<std::pair<KeyType, ValueType>> elements = getElements();
        table = std::vector<std::list<std::pair<KeyType, ValueType>>>(_capacity * 2);
        for (auto &it : elements) {
            this->insert(it.first, it.second);
        }

    }
    size_t hash = hash_function(key);
    for (auto &it: table[hash]) {
        if (it.first == key) {
            it.second = value;
            return;
        }
    }
    table[hash].emplace_back(key, value);
    ++_filled;
    if(debugMode) toString();
}

//! Поиск элемента в хеш таблице
bool HashTable::find(const KeyType &key, ValueType &value) const {
    size_t hash = hash_function(key);
    if(debugMode) std::cout << "searching for \"" + key + "\" -> [" << hash << "] --- ";
    for (auto &it: table[hash]) {
        if (it.first == key) {
            if(debugMode) std::cout << "SUCCESS\n";
            value = it.second;
            return true;
        }
    }
    if(debugMode) std::cout << "FAILURE\n";
    return false;
}

//! Удаление элемента из хеш-таблицы
void HashTable::remove(const KeyType &key) {
    if(debugMode) std::cout << "REMOVING: " << key << std::endl;
    size_t hash = hash_function(key);
    ValueType val;
    for (auto &it: table[hash]) {
        if (it.first == key) {
            val = it.second;
        }
    }
    table[hash].remove({key, val});
    --_filled;
}

//! Получение элемента по ключу
ValueType &HashTable::operator[](const KeyType &key) {
    size_t hash = hash_function(key);
    for (auto &it: table[hash]) {
        if (it.first == key) {
            if(debugMode) std::cout << "operator[] used, returning" << it.second << std::endl;
            return it.second;
        }
    }
    throw std::runtime_error("KeyError: \"" + key + "\"");
}

//! Загрузка хеш-таблицы. Считается как отношение количества занятых ячеек к вместимости хеш-таблицы.
double HashTable::getLoadFactor() {
    return static_cast<double>(_filled) / _capacity;
}

size_t HashTable::hash_function(const KeyType &key) const {
    long long keySum = 0;
    long long p = 1;
    for (auto &it : key) {
        keySum = keySum + it * p % 1000000009;
        p = (p * 53) % 1000000009;
    }
    double hash = (2.2360679775 - 1) / 2;
    hash *= keySum;
    hash -= static_cast<long long >(hash);
    hash = static_cast<int>(hash * _capacity);
    return static_cast<size_t>(hash);
}

std::list<std::pair<KeyType, ValueType>> HashTable::getElements() const {
    std::list<std::pair<KeyType, ValueType>> elements;
    for (auto &it : table) {
        for (auto &it2 : it) {
            elements.push_back(it2);
        }
    }
    return elements;
}

HashTable::~HashTable() {

}

void HashTable::toString() const {
    for (size_t i = 0; i < _capacity; ++i) {
        if (!table[i].empty()) {
            std::cout << "[" << i << "]: ";
            for (auto &it : table[i]) {
                std::cout << "{" << it.first << ", " << it.second << "} ";
            }
            std::cout << std::endl;
        }
    }

}
