#include <stddef.h>
#include "Stack.h"
#include "Vector.h"
#include "LinkedList.h"

Stack::Stack(StackContainer container)
{
    _containerType = container;
    if (container == StackContainer::Vector)
    {
        Vector* vector = new Vector();
        _pimpl = dynamic_cast<IStackImplementation*>(vector);
    }
    else if (container == StackContainer::List)
    {
        LinkedList* linkedList = new LinkedList();
        _pimpl = dynamic_cast<IStackImplementation*>(linkedList);
    }
}

Stack::Stack(const ValueType* valueArray, const size_t arraySize,
             StackContainer container)
{
    _containerType = container;
    if (container == StackContainer::Vector)
    {
        Vector* vector = new Vector(valueArray, arraySize);
        _pimpl = dynamic_cast<IStackImplementation*>(vector);
    }
    else if (container == StackContainer::List)
    {
        LinkedList* linkedList = new LinkedList(valueArray, arraySize);
        _pimpl = dynamic_cast<IStackImplementation*>(linkedList);
    }
}

Stack::Stack(const Stack& copyStack)
{
    _containerType = copyStack._containerType;
    if (_containerType == StackContainer::Vector)
    {
        Vector* vector = new Vector(*dynamic_cast<Vector*>(copyStack._pimpl));
        _pimpl = dynamic_cast<IStackImplementation*>(vector);
    }
    else if (_containerType == StackContainer::List)
    {
        LinkedList* linkedList = new LinkedList(*dynamic_cast<LinkedList*>(copyStack._pimpl));
        _pimpl = dynamic_cast<IStackImplementation*>(linkedList);
    }
}
Stack& Stack::operator=(const Stack& copyStack)
{
    if (copyStack._pimpl != this->_pimpl)
    {
        _containerType = copyStack._containerType;
        delete _pimpl;
        if (_containerType == StackContainer::Vector)
        {
            Vector* vector = new Vector(*dynamic_cast<Vector*>(copyStack._pimpl));
            _pimpl = dynamic_cast<IStackImplementation*>(vector);
        }
        else if (_containerType == StackContainer::List)
        {
            LinkedList* linkedList = new LinkedList(*dynamic_cast<LinkedList*>(copyStack._pimpl));
            _pimpl = dynamic_cast<IStackImplementation*>(linkedList);
        }
    }
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
