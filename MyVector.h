/*!********************************************
  \file MyVector.h
  \brief Реализация контейнера Вектор
  \author Sergey
  \date 10.03.2022
 ***********************************************/
#pragma once

#include <stddef.h>

using Value = int;
//! \brief Класс, реализующий С++ контейнер vector для типа int
class MyVector
{
    public:
        //! Конструктор без параметров
        MyVector();
        //! Конструктор копирования
        //! \param other - копируемый объект
        MyVector(const MyVector& other);
        //! Оператор присваивания копированием
        //! \param other - копируемый объект
        MyVector& operator=(const MyVector& other);
        //! Конструктор перемещения
        //! \param other - перемещаемый объект
        MyVector(MyVector&& other) noexcept;
        //! Оператор присваивания перемещением
        //! \param other - перемещаемый объект
        MyVector& operator=(MyVector&& other) noexcept;
        //! Деструктор
        ~MyVector();
        //! \brief Итератор для нашей реализации контейнера вектор
        class Iterator
        {
            public:
                Iterator operator+(const size_t& count);
                Iterator operator-(const size_t& count);
                Iterator operator++();
                Iterator operator--();
            private:
                Value *itPtr;
        };

        bool empty() const;
        size_t size() const;
        size_t capacity() const;

        void reserve(const size_t& newSize);
        void resize(const size_t& newSize);
        void shrink_to_fit();
        void clear();

        Iterator insert(Iterator pos, const Value& value);
        Iterator insert(Iterator pos, const size_t& count, const Value& value);
        Iterator erase(Iterator pos);
        Iterator erase(Iterator first, Iterator last);

        Iterator end();
        Iterator begin();

        void push_back(const Value& value);
        void pop_back();

        int& operator[](const size_t& pos);

        void isort();
        void qsort();
    private:
        size_t _capacity;
        size_t _size;

        int *_ptrToArray;
};
