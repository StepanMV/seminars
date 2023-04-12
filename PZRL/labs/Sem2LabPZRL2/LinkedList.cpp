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
            Node* slow = this->first;
            Node* fast = this->first->next;
            while (fast != nullptr)
            {
                delete slow;
                slow = fast;
                fast = fast->next;
            }
            delete slow;
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
            Node* slow = this->first;
            Node* fast = this->first->next;
            while (fast != nullptr)
            {
                delete slow;
                slow = fast;
                fast = fast->next;
            }
            delete slow;
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
    if(first != nullptr)
    {
        Node* slow = this->first;
        Node* fast = this->first->next;
        while (fast != nullptr)
        {
            delete slow;
            slow = fast;
            fast = fast->next;
        }
        delete slow;
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

Value& LinkedList::operator[](size_t idx)
{
    if (isEmpty()) throw std::out_of_range("The list is empty");
    Node* node = first;
    for (size_t i = 0; i < idx; i++)
    {
        node = node->next;
        if (!node) throw std::out_of_range("Index out of range");
    }
    return node->val;
}

const Value& LinkedList::operator[](size_t idx) const
{
    if (isEmpty()) throw std::out_of_range("The list is empty");
    Node* node = first;
    for (size_t i = 0; i < idx; i++)
    {
        node = node->next;
        if (!node) throw std::out_of_range("Index out of range");
    }
    return node->val;
}

LinkedList::Iterator::Iterator(Node* ptr)
{
    this->_ptr = ptr;
}

long long LinkedList::find(const Value& value) const
{
    Node* node = first;
    long long i = 0;
    while (node && node->val != value)
    {
        node = node->next;
        i++;
    }
    return (node && node->val == value) ? i : -1;
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
