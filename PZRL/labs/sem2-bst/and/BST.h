#pragma once

#include <utility>
#include <stdint.h>
#include <cstdlib>

using Key = uint32_t;
using Value = double;

/*!
    Имплементация бинарного дерева поиска
*/
class BinarySearchTree
{
    

public:

struct Node
    {
        Node(Key key, 
             Value value, 
             Node* parent = nullptr, 
             Node* left = nullptr, 
             Node* right = nullptr);

        ~Node() {
            delete left;
            delete right;
        }

        std::pair<Key, Value> keyValuePair;
        Node* parent = nullptr;
        Node* left = nullptr;
        Node* right = nullptr;
    };

    
    //! Конструктор по умолчанию
    BinarySearchTree() = default;
    
    //! Копирование
    explicit BinarySearchTree(const BinarySearchTree& other);
    BinarySearchTree& operator=(const BinarySearchTree& other);
    //! Перемещение
    explicit BinarySearchTree(BinarySearchTree&& other) noexcept;
    BinarySearchTree& operator=(BinarySearchTree&& other) noexcept;

    //! Деструктор
    ~BinarySearchTree();

    /*!
        Итератор бинарного дерева поиска

        Обходит дерево последовательно от меньшего ключа к большему 
    */
    class Iterator
    {
    public:
        explicit Iterator(Node* node);

        std::pair<Key, Value>& operator*();
        const std::pair<Key, Value>& operator*() const;

        std::pair<Key, Value>* operator->();
        const std::pair<Key, Value>* operator->() const;

        Iterator operator++();
        Iterator operator++(int);

        Iterator operator--();
        Iterator operator--(int);

        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

    private:
        Node* _node;

    };

    class ConstIterator {
    public:
        explicit ConstIterator(const Node *node);

        const std::pair<Key, Value> &operator*() const;

        const std::pair<Key, Value> *operator->() const;

        ConstIterator operator++();

        ConstIterator operator++(int);

        ConstIterator operator--();

        ConstIterator operator--(int);

        bool operator==(const ConstIterator &other) const;

        bool operator!=(const ConstIterator &other) const;

    private:
        const Node *_node;
    };

    // вставить элемент с ключем key и значением value
    void insert(const Key& key, const Value& value);

    // удалить все элементы с ключем key
    void erase(const Key& key);

    // найти первый элемент в дереве, равный ключу key
    Iterator find(const Key& key);

    Node* findKey(const Key& key) const;

    // найти все элементы, у которых ключ равен key
    // первый итератор пары - первый элемент в дереве, равный key
    // второй итератор пары - первый элемент в дереве больший, чем key
    // [pair.first, pair.second) - полуинтервал, содержащий все элементы с ключем key
    std::pair<Iterator, Iterator> equalRange(const Key& key);


    // получить итератор на минимальное значение в дереве (по ключу, в поддереве?)
    Iterator min(const Key& key) const;
    // получить итератор на максимальное значение в дереве (по ключу, в поддереве?)
    Iterator max(const Key& key) const;

    Iterator begin();   // min element
    Iterator end();     // max element

    ConstIterator cbegin() const;

    ConstIterator cend() const;

    size_t size() const;

    void print();                                           // вывод дерева
    void printWithValues();                               // вывод дерева

private:
    size_t _size = 0;
    Node* _root = nullptr;  //!< корневой узел дерева
    

    void insert(const Key& key, const Value& value, Node* node);
    void erase(const Key& key, Node* node);     // удаляем из поддерева

    Node* find(Key key, Node* node) const;      // ищем в поддереве

    void print(Node* node);                     // вывод поддерева
    void printWithValues(Node* node);
};
