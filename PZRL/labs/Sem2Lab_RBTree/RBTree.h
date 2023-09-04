#pragma once

#include <utility>
#include <cstdint>
#include <cstddef>

using Key = uint32_t;
using Value = double;

/*!
    Имплементация бинарного дерева поиска
*/
class RBTree {
    struct Node {
        Node() = default;

        Node(Key key, Value value, RBTree::Node *parent, RBTree::Node *left, RBTree::Node *right);

        Node(const Node &other);

        Node *findSuccessor(const Node *_nil) const;

        Node *findPredecessor(const Node *_nil) const;

        std::pair<Key, Value> keyValuePair = std::pair<Key, Value>(0, 0);
        bool isRed = false;
        Node *parent = nullptr;
        Node *left = nullptr;
        Node *right = nullptr;
    };

public:
    RBTree() = default;

    RBTree(const RBTree &other);

    RBTree &operator=(const RBTree &other);

    RBTree(RBTree &&other) noexcept;

    RBTree &operator=(RBTree &&other) noexcept;

    bool operator==(const RBTree &other) const;

    bool operator!=(const RBTree &other) const;

    ~RBTree();

    class Iterator {
    public:
        explicit Iterator(Node *node, const RBTree::Node *nil);

        std::pair<Key, Value> &operator*();

        const std::pair<Key, Value> &operator*() const;

        std::pair<Key, Value> *operator->();

        const std::pair<Key, Value> *operator->() const;

        Iterator operator++();

        Iterator operator++(int);

        Iterator operator--();

        Iterator operator--(int);

        bool operator==(const Iterator &other) const;

        bool operator!=(const Iterator &other) const;

    private:
        Node *_node;
        const Node *nil;
    };

    class ConstIterator {
    public:
        explicit ConstIterator(const Node *node, const RBTree::Node *nil);

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
        const Node *nil;
    };

    void insert(const Key &key, const Value &value);


    // удалить все элементы с ключем key
    void erase(const Key &key);

    ConstIterator find(const Key &key) const;

    Iterator find(const Key &key);

    std::pair<Iterator, Iterator> equalRange(const Key &key);

    std::pair<ConstIterator, ConstIterator> equalRange(const Key &key) const;

    // получить итератор на минимальное значение в дереве
    ConstIterator min(const Key &key) const;

    // получить итератор на максимальное значение в дереве
    ConstIterator max(const Key &key) const;

    Iterator begin();

    Iterator end();

    ConstIterator cbegin() const;

    ConstIterator cend() const;

    size_t size() const;

    void visualise() const;

private:
    void fillArray(int **array, Node *_root, int level, int pos) const;

    int findHeight(Node *root) const;

    Node *rootCopy(const RBTree::Node *root, const RBTree::Node *otherNil);

    void rootDelete(RBTree::Node *root);

    Node *findNode(const Key &key) const;

    void rightRotate(Node *node);

    void leftRotate(Node *x);

    void insertFixup(Node *z);

    void eraseFixup(Node *node);

    size_t _size = 0;
    Node * const nil = new Node();
    Node *_root = nil; //!< корневой узел дерева
};
