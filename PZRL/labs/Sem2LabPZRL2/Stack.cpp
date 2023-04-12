#include <stddef.h>
#include "Stack.h"
#include "Vector.h"
#include "LinkedList.h"

Stack::Stack(StackContainer container)
{
    _containerType = container;
    if (container == StackContainer::Vector)
    {
        _pimpl = (IStackImplementation*) new Vector();
    }
    else if (container == StackContainer::List)
    {
        _pimpl = (IStackImplementation*) new LinkedList();
    }
}

Stack::Stack(const ValueType* valueArray, const size_t arraySize,
      StackContainer container)
{
    _containerType = container;
    if (container == StackContainer::Vector)
    {
        _pimpl = (IStackImplementation*) new Vector(valueArray, arraySize);
    }
    else if (container == StackContainer::List)
    {
        _pimpl = (IStackImplementation*) new LinkedList(valueArray, arraySize);
    }
}

Stack::Stack(const Stack& copyStack)
{
    _pimpl = copyStack._pimpl;
}
Stack& Stack::operator=(const Stack& copyStack)
{
    _pimpl = copyStack._pimpl;
    return *this;
}

Stack::~Stack()
{
    delete _pimpl;
}

void Stack::push(const ValueType& value)
{
    _pimpl->push(value);
}

void Stack::pop()
{
    _pimpl->pop();
}

const ValueType& Stack::top() const
{
    return _pimpl->top();
}

bool Stack::isEmpty() const
{
    return _pimpl->isEmpty();
}

size_t Stack::size() const
{
    return _pimpl->size();
}
