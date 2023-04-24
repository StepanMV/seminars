#include "LinkedList.h"
#include <stdexcept>

Node::Node(Value value) : val(value), next(nullptr) {}

LinkedList::LinkedList(const Value* rawArray, const size_t __size)
{
    this->_size = __size;
    Node* node = new Node(rawArray[0]);
    this->first = node;
    for (size_t i = 1; i < __size; ++i)
    {
        node->next = new Node(rawArray[i]);
        node = node->next;
    }
    this->last = node;
}

LinkedList::LinkedList(const LinkedList& other)
{

    if (!other.isEmpty())
    {
        this->_size = other._size;
        Node* oldNode = other.first;
        Node* node = new Node(oldNode->val);
        this->first = node;
        for (size_t i = 1; i < other._size; ++i)
        {
            oldNode = oldNode->next;
            node->next = new Node(oldNode->val);
            node = node->next;
        }
        this->last = node;
    }
}

LinkedList& LinkedList::operator=(const LinkedList& other)
{
    if (this->first != other.first && this->last != other.last)
    {
        if (!this->isEmpty())
        {
            // Deleting old data
            while (!this->isEmpty())
            {
                this->pop();
            }
        }

        if (!other.isEmpty())
        {
            this->_size = other._size;
            Node* oldNode = other.first;
            Node* node = new Node(oldNode->val);
            this->first = node;
            for (size_t i = 1; i < other._size; ++i)
            {
                oldNode = oldNode->next;
                node->next = new Node(oldNode->val);
                node = node->next;
            }
            this->last = node;
        }
        else
        {
            this->_size = 0;
            this->first = nullptr;
            this->last = nullptr;
        }
    }
    return *this;
}



LinkedList::LinkedList(LinkedList&& other) noexcept
{
    this->_size = other._size;
    this->first = other.first;
    this->last = other.last;
    other._size = 0;
    other.first = nullptr;
    other.last = nullptr;
}

LinkedList& LinkedList::operator=(LinkedList&& other) noexcept
{
    if (this->first != other.first && this->last != other.last)
    {
        if (!this->isEmpty())
        {
            // Deleting old data
            while (!this->isEmpty())
            {
                this->pop();
            }
        }

        this->_size = other._size;
        this->first = other.first;
        this->last = other.last;
        other._size = 0;
        other.first = nullptr;
        other.last = nullptr;
    }
    return *this;
}

LinkedList::~LinkedList()
{
    while (!isEmpty())
    {
        this->pop();
    }
}

void LinkedList::push(const Value& value)
{
    Node* node = new Node(value);
    if (this->isEmpty())
    {
        this->first = node;
        this->last = node;
    }
    else 
    {
        last->next = node;
        last = node;
    }
    _size++;
}

void LinkedList::pop()
{
    if (isEmpty())
    {
        throw std::out_of_range("Deleting in empty array");
    }
    if (first == last)
    {
        Node* node = first;
        first = node->next;
        delete node;
    }
    else
    {
        Node* node = first;
        while (node->next != last)
        {
            node = node->next;
        }
        node->next = nullptr;
        delete last;
        last = node;
    }
    _size--;
}

const ValueType& LinkedList::top() const
{
    return last->val;
}

bool LinkedList::isEmpty() const
{
    return first == nullptr;
}

size_t LinkedList::size() const
{
    return _size;
}

LinkedList::Iterator::Iterator(Node* ptr)
{
    this->_ptr = ptr;
}

Value& LinkedList::Iterator::operator*()
{
    return _ptr->val;
}

const Value& LinkedList::Iterator::operator*() const
{
    return _ptr->val;
}
LinkedList::Iterator LinkedList::Iterator::operator++()
{
    _ptr = _ptr->next;
    return *this;
}

LinkedList::Iterator LinkedList::Iterator::operator++(int)
{
    LinkedList::Iterator it = *this;
    _ptr = _ptr->next;
    return it;
}

bool LinkedList::Iterator::operator==(const Iterator& other) const
{
    return other._ptr == _ptr;
}

bool LinkedList::Iterator::operator!=(const Iterator& other) const
{
    return other._ptr != _ptr;
}

LinkedList::Iterator LinkedList::begin()
{
    return LinkedList::Iterator(first);
}

LinkedList::Iterator LinkedList::end()
{
    return LinkedList::Iterator(nullptr);
}
