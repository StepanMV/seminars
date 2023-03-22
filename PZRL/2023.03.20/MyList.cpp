#include <iostream>
#include "MyList.h"

template <typename T>
Node::Node<T>(T _val) : val(_val), next(nullptr) {}

template <typename T>
MyList::MyList<T>() : first(nullptr), last(nullptr) {}

bool MyList::is_empty()
{
    return first == nullptr;
}

template <typename T>
void MyList::push_back(T _val)
{
    Node<T>* p = new Node<T>(_val);
    if (this->is_empty())
    {
        this->first = p;
        this->last = p;
        return;
    }
    last->next = p;
    last = p;
}

void MyList::print()
{
    if (this->is_empty()) return;
    Node<T>* p = this->first;
    while (p)
    {
        std::cout << p->val << " ";
        p = p->next;
    }
    std::cout << std::endl;
}

template <typename T>
Node* MyList::find(T _val)
{
    Node* p = first;
    while (p && p->val != _val) p = p->next;
    return (p && p->val == _val) ? p : nullptr;
}

void MyList::remove_first()
{
    if (is_empty()) return;
    Node* p = first;
    first = p->next;
    delete p;
}

void MyList::remove_last()
{
    if (is_empty()) return;
    if (first == last)
    {
        remove_first();
        return;
    }
    Node* p = first;
    while (p->next != last) p = p->next;
    p->next = nullptr;
    delete last;
    last = p;
}

template <typename T>
void MyList::remove(T _val)
{
    if (is_empty()) return;
    if (first->val == _val)
    {
        remove_first();
        return;
    }
    else if (last->val == _val)
    {
        remove_last();
        return;
    }
    Node* slow = first;
    Node* fast = first->next;
    while (fast && fast->val != _val)
    {
        fast = fast->next;
        slow = slow->next;
    }
    if (!fast)
    {
        std::cout << "This element does not exist" << std::endl;
        return;
    }
    slow->next = fast->next;
    delete fast;
}

Node* MyList::operator[] (const int index)
{
    if (is_empty()) return nullptr;
    Node* p = first;
    for (int i = 0; i < index; i++)
    {
        p = p->next;
        if (!p) return nullptr;
    }
    return p;
}
