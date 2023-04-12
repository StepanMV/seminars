#pragma once

#include <stddef.h>
#include "StackImplementation.h"

using Value = double;
//! \brief Класс, реализующий С++ контейнер vector для типа int
class Vector : IStackImplementation
{
    public:
        //! Конструктор без параметров
        Vector() = default;
        //! Конструктор с параметрами
        Vector(const Value* rawArray, const size_t size, float coef = 2.0f);
        //! Конструктор копирования
        //! \param other - копируемый объект
        explicit Vector(const Vector& other);
        //! Оператор присваивания копированием
        //! \param other - копируемый объект
        Vector& operator=(const Vector& other);
        //! Конструктор перемещения
        //! \param other - перемещаемый объект
        explicit Vector(Vector&& other) noexcept;
        //! Оператор присваивания перемещением
        //! \param other - перемещаемый объект
        Vector& operator=(Vector&& other) noexcept;
        //! Деструктор
        ~Vector();


        void push(const Value& value);
        void pop();
        const ValueType& top() const;

        bool isEmpty() const;
        size_t size() const;
        double loadFactor() const;

        void reserve(size_t capacity);
        void shrinkToFit();

        //! Доступ к элементу по индексу
        Value& operator[](size_t idx);
        //! Доступ к элементу по индексу
        const Value& operator[](size_t idx) const;

        class Iterator
        {
            Value* _ptr;
            public:
            explicit Iterator(Value* ptr);

            Value& operator*();

            const Value& operator*() const;

            Value* operator->();

            const Value* operator->() const;

            Iterator operator++();

            Iterator operator++(int);

            bool operator==(const Iterator& other) const;

            bool operator!=(const Iterator& other) const;
        };

        Iterator begin();
        Iterator end();
    private:
        Value* _data = nullptr;
        size_t _size = 0;
        size_t _capacity = 0;
        float _multiplicativeCoef = 2.0f;
};

