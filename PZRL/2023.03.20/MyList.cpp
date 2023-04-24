#include <iostream>
#include "MyList.h"

Node::Node(int _val) : val(_val), next(nullptr) {}

MyList::MyList() : first(nullptr), last(nullptr) {}

bool MyList::is_empty()
{
    return first == nullptr;
}

void MyList::add(int _val)
{
    Node* p = new Node(_val);
    if (this->is_empty())
    {
        this->first = p;
        this->last = p;
    }
    else 
    {
        last->next = p;
        last = p;
    }
}

void MyList::add(const int index, int _val)
{
    // slow сслылается на новый
    // новый ссылается на fast
    Node* p = new Node(_val);
    if (this->is_empty())
    {
        this->first = p;
        this->last = p;
    }
    else if (index == 0)
    {
        p->next = this->first;
        this->first = p; 
    }
    else 
    {
        Node* slow = first;
        Node* fast = first->next;
        for (int i = 1; i < index; ++i)
        {
            fast = fast->next;
            slow = slow->next;
            if (!fast) break;
        }
        if (!fast)
        {
            std::cout << "This element does not exist" << std::endl;
            return;
        }
        slow->next = p;
        p->next = fast;
    }
}

int MyList::indexOf(int _val)
{
    Node* p = first;
    int i = 0;
    while (p && p->val != _val)
    {
        p = p->next;
        i++;
    }
    return (p && p->val == _val) ? i : -1;
}

void MyList::removeFirst()
{
    if (is_empty()) return;
    Node* p = first;
    first = p->next;
    delete p;
}

void MyList::removeLast()
{
    if (is_empty()) return;
    if (first == last)
    {
        removeFirst();
        return;
    }
    Node* p = first;
    while (p->next != last) p = p->next;
    p->next = nullptr;
    delete last;
    last = p;
}

void MyList::remove(int _val)
{
    if (is_empty()) return;
    if (first->val == _val)
    {
        removeFirst();
        return;
    }
    else if (last->val == _val)
    {
        removeLast();
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

void MyList::removeAt(const int index)
{
    if (is_empty()) return;
    if (index == 0)
    {
        removeFirst();
        return;
    }

    Node* slow = first;
    Node* fast = first->next;
    for (int i = 1; i < index; ++i)
    {
        fast = fast->next;
        slow = slow->next;
        if (!fast) break;
    }
    if (!fast)
    {
        std::cout << "This element does not exist" << std::endl;
        return;
    }
    slow->next = fast->next;
    delete fast;
}

void MyList::print()
{
    if (this->is_empty()) return;
    Node* p = this->first;
    while (p)
    {
        std::cout << p->val << " ";
        p = p->next;
    }
    std::cout << std::endl;
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
