#pragma once

#include <stddef.h>
#include "StackImplementation.h"

using Value = double;

struct Node {
    Value val;
    Node* next;
    Node(Value _val);
};

class LinkedList : public IStackImplementation
{
public:
    LinkedList() = default;
    //! Конструктор с параметрами
    LinkedList(const Value* rawArray, const size_t size);
    //! Конструктор копирования
    //! \param other - копируемый объект
    explicit LinkedList(const LinkedList& other);
    //! Оператор присваивания копированием
    //! \param other - копируемый объект
    LinkedList& operator=(const LinkedList& other);
    //! Конструктор перемещения
    //! \param other - перемещаемый объект
    explicit LinkedList(LinkedList&& other) noexcept;
    //! Оператор присваивания перемещением
    //! \param other - перемещаемый объект
    LinkedList& operator=(LinkedList&& other) noexcept;
    //! Деструктор
    ~LinkedList();


    // добавление в хвост
    void push(const ValueType& value);
    // удаление с хвоста
    void pop();
    // посмотреть элемент в хвосте
    const ValueType& top() const;
    // проверка на пустоту
    bool isEmpty() const;
    // размер
    size_t size() const;

    class Iterator
    {
        Node* _ptr;
    public:
        explicit Iterator(Node* ptr);

        Value& operator*();

        const Value& operator*() const;

        Iterator operator++();

        Iterator operator++(int);

        bool operator==(const Iterator& other) const;

        bool operator!=(const Iterator& other) const;
    };

    Iterator begin();
    Iterator end();
private:
    Node* first = nullptr;
    Node* last = nullptr;
    size_t _size = 0;
};
