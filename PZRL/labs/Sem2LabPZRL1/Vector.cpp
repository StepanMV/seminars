#include "Vector.h"
#include <cstring>
#include <stdexcept>
#include <iostream>

Vector::Vector(const Value* rawArray, const size_t size, float coef)
{
    this->_multiplicativeCoef = coef;
    this->_size = size;
    this->_capacity = size;
    this->_data = new Value[size];
    for (size_t i = 0; i < size; ++i)
    {
        _data[i] = rawArray[i];
    }
}

Vector::Vector(const Vector& other)
{
    this->_multiplicativeCoef = other._multiplicativeCoef;
    this->_size = other.size();
    this->_capacity = other.size();
    this->_data = new Value[other.size()];
    for (size_t i = 0; i < other.size(); ++i)
    {
        _data[i] = other[i];
    }
}

Vector& Vector::operator=(const Vector& other)
{
    if (other._data == this->_data)
    {
        return *this;
    }
    this->_multiplicativeCoef = other._multiplicativeCoef;
    this->_size = other.size();
    this->_capacity = other.size();
    this->_data = new Value[other.size()];
    for (size_t i = 0; i < other.size(); ++i)
    {
        _data[i] = other[i];
    }
    return *this;
}

Vector::Vector(Vector&& other) noexcept
{
    this->_multiplicativeCoef = other._multiplicativeCoef;
    this->_size = other.size();
    this->_capacity = other.capacity();
    this->_data = other._data;
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
    other._multiplicativeCoef = 2.0f;
}

Vector& Vector::operator=(Vector&& other) noexcept
{
    this->_multiplicativeCoef = other._multiplicativeCoef;
    this->_size = other.size();
    this->_capacity = other.capacity();
    this->_data = other._data;
    return *this;
}

Vector::~Vector()
{
    delete[] this->_data;
}

void Vector::pushBack(const Value& value)
{
    if (_size == 0)
    {
        this->reserve(_multiplicativeCoef);
    }
    else if (this->loadFactor() == 1)
    {
        this->reserve(_size * _multiplicativeCoef);
    }
    *this->end() = value;
    _size++;
}

void Vector::pushFront(const Value& value)
{
    if (_size == 0)
    {
        this->reserve(_multiplicativeCoef);
    }
    else if (this->loadFactor() == 1)
    {
        this->reserve(_size * _multiplicativeCoef);
    }
    std::memmove(_data + 1, _data, _size * sizeof(Value));
    *this->begin() = value;
    _size++;
}

void Vector::insert(const Value& value, size_t pos)
{
    if (pos > _size)
    {
        return;
    }
    if (_size == 0)
    {
        this->reserve(_multiplicativeCoef);
    }
    else if (this->loadFactor() == 1)
    {
        this->reserve(_size * _multiplicativeCoef);
    }
    // size = 10; pos = 7; 7,8,9 - move;
    std::memmove(_data + pos + 1, _data + pos, (_size - pos) * sizeof(Value));
    _data[pos] = value;
    _size++;
}

void Vector::insert(const Value* values, size_t size, size_t pos)
{
    if (pos > _size)
    {
        return;
    }
    if (_size == 0)
    {
        this->reserve(size);
    }
    else if(_size + size > _capacity)
    {
        double coef = (1 + size / _size) / _multiplicativeCoef;
        coef = (int) coef == coef ? coef : (int) coef + 1;
        this->reserve(_size * _multiplicativeCoef * coef);
    }
    // _size = 10; pos = 3; size = 5; 3,4,5,6,7,8,9 - move;
    std::memmove(_data + pos + size, _data + pos, (_size - pos) * sizeof(Value));
    std::memcpy(_data + pos, values, size * sizeof(Value));
    _size += size;
}

void Vector::insert(const Vector& vector, size_t pos)
{
    if (pos > _size)
    {
        return;
    }
    if (_size == 0)
    {
        this->reserve(vector.size());
    }
    else if(_size + vector.size() > _capacity)
    {
        double coef = (1 + vector.size() / _size) / _multiplicativeCoef;
        coef = (int) coef == coef ? coef : (int) coef + 1;
        this->reserve(_size * _multiplicativeCoef * coef);
    }
    std::memmove(_data + pos + vector.size(), _data + pos, (_size - pos) * sizeof(Value));
    for (size_t i = pos; i < pos + vector.size(); ++i)
    {
        _data[i] = vector[i - pos];
    }
    _size += vector.size();
}

void Vector::popBack()
{
    if (_size == 0)
    {
        throw std::out_of_range ("blah");
    }
    _size--;
}

void Vector::popFront()
{
    if (_size == 0)
    {
        throw std::out_of_range ("blah");
    }
    std::memmove(_data, _data + 1, (_size - 1) * sizeof(Value));
    _size--;
}

void Vector::erase(size_t pos, size_t count)
{
    if (_size == 0)
    {
        throw std::out_of_range ("blah");
    }
    if (pos >= _size)
    {
        return;
    }
    else if (pos + count >= _size)
    {
        _size = pos;
    }
    else
    { // size = 10, pos = 5, count = 2; 5,6 - delete, 7,8,9 - keep;
        std::memmove(_data + pos, _data + pos + count, (_size - pos - count) * sizeof(Value));
        _size -= count;
    }
}

void Vector::eraseBetween(size_t beginPos, size_t endPos)
{
    if (_size == 0)
    {
        throw std::out_of_range ("blah");
    }
    if (beginPos >= _size)
    {
        return;
    }
    else if (endPos >= _size)
    {
        _size = beginPos;
    }
    else
    { // size = 10, begin = 5, end = 7; 5,6 - delete, 7,8,9 - keep;
        std::memmove(_data + beginPos, _data + endPos, (_size - endPos) * sizeof(Value));
        _size -= endPos - beginPos;
    }
}

size_t Vector::size() const
{
    return _size;
}

size_t Vector::capacity() const
{
    return _capacity;
}

double Vector::loadFactor() const
{
    return _size / _capacity;
}

Value& Vector::operator[](size_t idx)
{
    return *(_data + idx);
}

const Value& Vector::operator[](size_t idx) const
{
    return *(_data + idx);
}

long long Vector::find(const Value& value) const
{
    for (size_t i = 0; i < this->size(); ++i)
    {
        if (_data[i] == value)
        {
            return i;
        }
    }
    return -1;
}

void Vector::reserve(size_t capacity)
{
    if (capacity <= _capacity)
    {
        return;
    }
    Value* newData = new Value[capacity];
    std::memcpy(newData, _data, _size * sizeof(Value));
    delete[] _data;
    _data = newData;
    _capacity = capacity;
}

void Vector::shrinkToFit()
{
    Value* newData = new Value[_size];
    std::memcpy(newData, _data, _size * sizeof(Value));
    delete[] _data;
    _data = newData;
    _capacity = _size;
}

Vector::Iterator::Iterator(Value* ptr)
{
    this->_ptr = ptr;
}

Value& Vector::Iterator::operator*()
{
    return *_ptr;
}

const Value& Vector::Iterator::operator*() const
{
   return *_ptr;
}

Value* Vector::Iterator::operator->()
{
   return _ptr;
}

const Value* Vector::Iterator::operator->() const
{
    return _ptr;
}

Vector::Iterator Vector::Iterator::operator++()
{
    _ptr++;
    return *this;
}

Vector::Iterator Vector::Iterator::operator++(int)
{
    Vector::Iterator it = *this;
    _ptr++;
    return it;
}

bool Vector::Iterator::operator==(const Vector::Iterator& other) const
{
    return other._ptr == _ptr;
}

bool Vector::Iterator::operator!=(const Vector::Iterator& other) const
{
    return other._ptr != _ptr;
}

Vector::Iterator Vector::begin()
{
    return Vector::Iterator(_data);
}

Vector::Iterator Vector::end()
{
    return Vector::Iterator(_data + _size);
}
