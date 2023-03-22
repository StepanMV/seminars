#include "MyVector.h"

using Value = int;

MyVector::MyVector()
{
    _capacity = 8;
    _size = 0;
    _ptrToArray = new Value[_capacity];
}
/*
MyVector::MyVector(const MyVector& other)
{
    _capacity = other.capacity();
    _size = other.size();

    _ptrToArray = new Value[_capacity];
    for (size_t i = 0; i < _size; ++i)
    {
        _ptrToArray[i] = other[i];
    }
}

MyVector& MyVector::operator=(const MyVector& other)
{
    _capacity = other.capacity();
    _size = other.size();

    _ptrToArray = new Value[_capacity];
    for (size_t i = 0; i < _size; ++i)
    {
        _ptrToArray[i] = other[i];
    }
}
*/
MyVector::MyVector(MyVector&& other) noexcept
{

}

MyVector& MyVector::operator=(MyVector&& other) noexcept
{

}

MyVector::~MyVector()
{
    delete[] _ptrToArray;
}

bool MyVector::empty() const
{
    return _size == 0;
}

size_t MyVector::size() const
{
    return _size;
}

size_t MyVector::capacity() const
{
    return _capacity;
}

void MyVector::reserve(const size_t& newSize)
{

}

void MyVector::resize(const size_t& newSize)
{

}

void MyVector::shrink_to_fit()
{

}

void MyVector::clear()
{

}

MyVector::Iterator MyVector::insert(MyVector::Iterator pos, const Value& value)
{

}

MyVector::Iterator MyVector::insert(MyVector::Iterator pos, const size_t& count, const Value& value)
{

}

MyVector::Iterator MyVector::erase(MyVector::Iterator pos)
{
    for(size_t i = pos; i < _size - 1; ++i)
    {
        _ptrToArray[i] = _ptrToArray[i + 1];
    }

    _ptrToArray[_size - 1] = 0;
    --_size;
}

MyVector::Iterator MyVector::erase(MyVector::Iterator first, MyVector::Iterator last)
{

}

MyVector::Iterator MyVector::end()
{

}

MyVector::Iterator MyVector::begin()
{

}

void MyVector::push_back(const Value& value)
{

}

void MyVector::pop_back()
{

}

int& MyVector::operator[](const size_t& pos)
{
    return _ptrToArray[pos];
}

void MyVector::isort()
{

}

void MyVector::qsort()
{

}
