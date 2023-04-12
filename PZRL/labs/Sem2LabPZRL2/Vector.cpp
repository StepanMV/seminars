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
    std::memcpy(_data, rawArray, size * sizeof(Value));
}

Vector::Vector(const Vector& other)
{
    this->_multiplicativeCoef = other._multiplicativeCoef;
    this->_size = other._size;
    this->_capacity = other._size;
    this->_data = new Value[other._size];
    std::memcpy(_data, other._data, other._size * sizeof(Value));
}

Vector& Vector::operator=(const Vector& other)
{
    if (other._data != this->_data)
    {
        delete[] _data;

        this->_multiplicativeCoef = other._multiplicativeCoef;
        this->_size = other._size;
        this->_capacity = other._size;
        this->_data = new Value[other._size];
        std::memcpy(_data, other._data, other._size * sizeof(Value));
    }
    return *this;
}

Vector::Vector(Vector&& other) noexcept
{
    this->_multiplicativeCoef = other._multiplicativeCoef;
    this->_size = other._size;
    this->_capacity = other._capacity;
    this->_data = other._data;
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
    other._multiplicativeCoef = 2.0f;
}

Vector& Vector::operator=(Vector&& other) noexcept
{
    if (other._data != this->_data)
    {
        delete[] _data;

        this->_multiplicativeCoef = other._multiplicativeCoef;
        this->_size = other._size;
        this->_capacity = other._capacity;
        this->_data = other._data;
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
        other._multiplicativeCoef = 2.0f;
    }
    return *this;
}

Vector::~Vector()
{
    delete[] _data;
}

void Vector::push(const Value& value)
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

void Vector::pop()
{
    if (_size == 0)
    {
        throw std::out_of_range ("bruh");
    }
    _size--;
}

const ValueType& Vector::top() const
{
    return this->_data[_size - 1];
}

bool Vector::isEmpty() const
{
    return _data == nullptr;
}

size_t Vector::size() const
{
    return _size;
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
