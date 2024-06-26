#include "BST.h"
#include <utility>
#include <stdexcept>
#include <iostream>

// Node

BinarySearchTree::Node::Node(Key key, Value value, BinarySearchTree::Node *parent, BinarySearchTree::Node *left,
                             BinarySearchTree::Node *right) {
    this->keyValuePair = std::pair<Key, Value>(key, value);
    this->parent = parent;
    this->left = left;
    this->right = right;
}

BinarySearchTree::Node::~Node() {
    delete this->left;
    delete this->right;
}

BinarySearchTree::Node::Node(const BinarySearchTree::Node &other) {
    this->keyValuePair = other.keyValuePair;
    if (other.left != nullptr) {
        this->left = new BinarySearchTree::Node(*other.left);
        this->left->parent = this;
    }
    if (other.right != nullptr) {
        this->right = new BinarySearchTree::Node(*other.right);
        this->right->parent = this;
    }
}

// BST

BinarySearchTree::BinarySearchTree() {
    std::cout << "Hello\n";
}

BinarySearchTree::BinarySearchTree(const BinarySearchTree &other) {
    this->_size = other._size;
    this->_root = new BinarySearchTree::Node(*other._root);
}

BinarySearchTree &BinarySearchTree::operator=(const BinarySearchTree &other) {
    if (this->_root != other._root) {
        delete _root;
        this->_size = other._size;
        this->_root = new BinarySearchTree::Node(*other._root);
    }
    return *this;
}

BinarySearchTree::BinarySearchTree(BinarySearchTree &&other) noexcept {
    this->_size = other._size;
    this->_root = other._root;
    other._size = 0;
    other._root = nullptr;
}

BinarySearchTree &BinarySearchTree::operator=(BinarySearchTree &&other) noexcept {
    if (this->_root != other._root) {
        delete _root;
        this->_size = other._size;
        this->_root = other._root;
        other._size = 0;
        other._root = nullptr;
    }
    return *this;
}

BinarySearchTree::~BinarySearchTree() {
    delete _root;
}

void BinarySearchTree::insert(const Key &key, const Value &value) {
    Node *newNode = new Node(key, value, nullptr, nullptr, nullptr);
    Node *above = nullptr;
    Node *node = _root;
    while (node != nullptr) {
        above = node;
        if (key < node->keyValuePair.first) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    newNode->parent = above;
    if (above == nullptr) {
        _root = newNode;
    } else {
        if (key < above->keyValuePair.first) {
            above->left = newNode;
        } else {
            above->right = newNode;
        }
    }
    _size++;
}

void BinarySearchTree::erase(const Key &key) {
    if (_root == nullptr) {
        return;
    }
    Node *delNode = _root;
    while (delNode != nullptr && delNode->keyValuePair.first != key) {
        if (key < delNode->keyValuePair.first) {
            delNode = delNode->left;
        } else {
            delNode = delNode->right;
        }
    }

    if (delNode->left == nullptr && delNode->right != nullptr) {
        if (delNode == _root) {
            _root = delNode->right;
        } else {
            if (delNode->parent->left == delNode) {
                delNode->parent->left = delNode->right;
            } else {
                delNode->parent->right = delNode->right;
            }
        }
    } else if (delNode->right == nullptr && delNode->left != nullptr) {
        if (delNode == _root) {
            _root = delNode->left;
        } else {
            if (delNode->parent->left == delNode) {
                delNode->parent->left = delNode->left;
            } else {
                delNode->parent->right = delNode->left;
            }
        }
    } else {
        Node *node = delNode;
        delNode = delNode->right;
        while (delNode->left != nullptr) {
            delNode = delNode->left;
        }
        if (delNode->parent == node) {
            node->right =delNode->right;
            if (delNode->right != nullptr) {
                delNode->right->parent = node;
            }
        } else if (delNode->right != nullptr) {
            delNode->parent->left = delNode->right;
            delNode->right->parent = delNode->parent;
        } else {
            delNode->parent->left = nullptr;
        }
        node->keyValuePair = delNode->keyValuePair;
    }
    delNode->left = nullptr;
    delNode->right = nullptr;
    delete delNode;
    _size--;
}

BinarySearchTree::ConstIterator BinarySearchTree::find(const Key &key) const {
    Node *node = _root;
    while (node != nullptr && node->keyValuePair.first != key) {
        if (key < node->keyValuePair.first) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return BinarySearchTree::ConstIterator(node);
}

BinarySearchTree::Iterator BinarySearchTree::find(const Key &key) {
    Node *node = _root;
    while (node != nullptr && node->keyValuePair.first != key) {
        if (key < node->keyValuePair.first) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return BinarySearchTree::Iterator(node);
}

std::pair<BinarySearchTree::Iterator, BinarySearchTree::Iterator> BinarySearchTree::equalRange(const Key &key) {
    Node *node = _root;
    while (node != nullptr && node->keyValuePair.first != key) {
        if (key < node->keyValuePair.first) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    auto first = BinarySearchTree::Iterator(node);
    while (node != nullptr && node->right != nullptr && node->right->keyValuePair.first == key) {
        node = node->right;
    }
    auto second = ++BinarySearchTree::Iterator(node);
    return {first, second};
}

std::pair<BinarySearchTree::ConstIterator, BinarySearchTree::ConstIterator>
BinarySearchTree::equalRange(const Key &key) const {
    Node *node = _root;
    while (node != nullptr && node->keyValuePair.first != key) {
        if (key < node->keyValuePair.first) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    auto first = BinarySearchTree::ConstIterator(node);
    while (node != nullptr && node->right != nullptr && node->right->keyValuePair.first == key) {
        node = node->right;
    }
    auto second = ++BinarySearchTree::ConstIterator(node);
    return {first, second};
}

BinarySearchTree::ConstIterator BinarySearchTree::min(const Key &key) const {
    Node *node = _root;
    while (node != nullptr && node->keyValuePair.first != key) {
        if (key < node->keyValuePair.first) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    while (node != nullptr && node->left != nullptr) {
        node = node->left;
    }
    return BinarySearchTree::ConstIterator(node);
}

BinarySearchTree::ConstIterator BinarySearchTree::max(const Key &key) const {
    Node *node = _root;
    while (node != nullptr && node->keyValuePair.first != key) {
        if (key < node->keyValuePair.first) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    while (node != nullptr && node->right != nullptr) {
        node = node->right;
    }
    return BinarySearchTree::ConstIterator(node);
}

BinarySearchTree::Iterator BinarySearchTree::begin() {
    if (_root == nullptr) {
        return BinarySearchTree::Iterator(nullptr);
    }
    Node *node = _root;
    while (node->left != nullptr) {
        node = node->left;
    }
    return BinarySearchTree::Iterator(node);
}

BinarySearchTree::Iterator BinarySearchTree::end() {
    if (_root == nullptr) {
        return BinarySearchTree::Iterator(nullptr);
    }
    Node *node = _root;
    while (node->right != nullptr) {
        node = node->right;
    }
    return BinarySearchTree::Iterator(node);
}

BinarySearchTree::ConstIterator BinarySearchTree::cbegin() const {
    if (_root == nullptr) {
        return BinarySearchTree::ConstIterator(nullptr);
    }
    Node *node = _root;
    while (node->left != nullptr) {
        node = node->left;
    }
    return BinarySearchTree::ConstIterator(node);
}

BinarySearchTree::ConstIterator BinarySearchTree::cend() const {
    if (_root == nullptr) {
        return BinarySearchTree::ConstIterator(nullptr);
    }
    Node *node = _root;
    while (node->right != nullptr) {
        node = node->right;
    }
    return BinarySearchTree::ConstIterator(node);
}

size_t BinarySearchTree::size() const {
    return _size;
}

// Iterator

BinarySearchTree::Iterator::Iterator(BinarySearchTree::Node *node) {
    this->_node = node;
}

std::pair<Key, Value> &BinarySearchTree::Iterator::operator*() {
    if (_node == nullptr) {
        throw std::runtime_error("Iterator of nullptr");
    }
    return _node->keyValuePair;
}

const std::pair<Key, Value> &BinarySearchTree::Iterator::operator*() const {
    if (_node == nullptr) {
        throw std::runtime_error("Iterator of nullptr");
    }
    return _node->keyValuePair;
}

std::pair<Key, Value> *BinarySearchTree::Iterator::operator->() {
    if (_node == nullptr) {
        throw std::runtime_error("Iterator of nullptr");
    }
    return &_node->keyValuePair;
}

const std::pair<Key, Value> *BinarySearchTree::Iterator::operator->() const {
    if (_node == nullptr) {
        throw std::runtime_error("Iterator of nullptr");
    }
    return &_node->keyValuePair;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++() {
    if (_node == nullptr) {
        throw std::runtime_error("Iterator of nullptr");
    }
    if (_node->right != nullptr) {
        _node = _node->right;
        while (_node->left != nullptr) {
            _node = _node->left;
        }
    } else {
        auto tmp = _node;
        while (_node->parent != nullptr && _node->parent->keyValuePair.first <= _node->keyValuePair.first) {
            _node = _node->parent;
        }
        _node = _node->parent == nullptr ? tmp : _node->parent;
    }
    return *this;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++(int) {
    if (_node == nullptr) {
        throw std::runtime_error("Iterator of nullptr");
    }
    BinarySearchTree::Iterator temp = *this;
    if (_node->right != nullptr) {
        _node = _node->right;
        while (_node->left != nullptr) {
            _node = _node->left;
        }
    } else {
        auto tmp = _node;
        while (_node->parent != nullptr && _node->parent->keyValuePair.first <= _node->keyValuePair.first) {
            _node = _node->parent;
        }
        _node = _node->parent == nullptr ? tmp : _node->parent;
    }
    return temp;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--() {
    if (_node == nullptr) {
        throw std::runtime_error("Iterator of nullptr");
    }
    if (_node->left != nullptr) {
        _node = _node->left;
        while (_node->right != nullptr) {
            _node = _node->right;
        }
    } else {
        auto tmp = _node;
        while (_node->parent != nullptr && _node->parent->keyValuePair.first >= _node->keyValuePair.first) {
            _node = _node->parent;
        }
        _node = _node->parent == nullptr ? tmp : _node->parent;
    }
    return *this;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--(int) {
    if (_node == nullptr) {
        throw std::runtime_error("Iterator of nullptr");
    }
    BinarySearchTree::Iterator temp = *this;
    if (_node->left != nullptr) {
        _node = _node->left;
        while (_node->right != nullptr) {
            _node = _node->right;
        }
    } else {
        auto tmp = _node;
        while (_node->parent != nullptr && _node->parent->keyValuePair.first >= _node->keyValuePair.first) {
            _node = _node->parent;
        }
        _node = _node->parent == nullptr ? tmp : _node->parent;
    }
    return temp;
}

bool BinarySearchTree::Iterator::operator==(const BinarySearchTree::Iterator &other) const {
    return this->_node == other._node;
}

bool BinarySearchTree::Iterator::operator!=(const BinarySearchTree::Iterator &other) const {
    return this->_node != other._node;
}

// ConstIterator

BinarySearchTree::ConstIterator::ConstIterator(const BinarySearchTree::Node *node) {
    this->_node = node;
}

const std::pair<Key, Value> &BinarySearchTree::ConstIterator::operator*() const {
    if (_node == nullptr) {
        throw std::runtime_error("Iterator of nullptr");
    }
    return _node->keyValuePair;
}

const std::pair<Key, Value> *BinarySearchTree::ConstIterator::operator->() const {
    if (_node == nullptr) {
        throw std::runtime_error("Iterator of nullptr");
    }
    return &_node->keyValuePair;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++() {
    if (_node == nullptr) {
        throw std::runtime_error("Iterator of nullptr");
    }
    if (_node->right != nullptr) {
        _node = _node->right;
        while (_node->left != nullptr) {
            _node = _node->left;
        }
    } else {
        auto tmp = _node;
        while (_node->parent != nullptr && _node->parent->keyValuePair.first <= _node->keyValuePair.first) {
            _node = _node->parent;
        }
        _node = _node->parent == nullptr ? tmp : _node->parent;
    }
    return *this;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++(int) {
    if (_node == nullptr) {
        throw std::runtime_error("Iterator of nullptr");
    }
    BinarySearchTree::ConstIterator temp = *this;
    if (_node->right != nullptr) {
        _node = _node->right;
        while (_node->left != nullptr) {
            _node = _node->left;
        }
    } else {
        auto tmp = _node;
        while (_node->parent != nullptr && _node->parent->keyValuePair.first <= _node->keyValuePair.first) {
            _node = _node->parent;
        }
        _node = _node->parent == nullptr ? tmp : _node->parent;
    }
    return temp;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--(int) {
    if (_node == nullptr) {
        throw std::runtime_error("Iterator of nullptr");
    }
    if (_node->left != nullptr) {
        _node = _node->left;
        while (_node->right != nullptr) {
            _node = _node->right;
        }
    } else {
        auto tmp = _node;
        while (_node->parent != nullptr && _node->parent->keyValuePair.first >= _node->keyValuePair.first) {
            _node = _node->parent;
        }
        _node = _node->parent == nullptr ? tmp : _node->parent;
    }
    return *this;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--() {
    if (_node == nullptr) {
        throw std::runtime_error("Iterator of nullptr");
    }
    BinarySearchTree::ConstIterator temp = *this;
    if (_node->left != nullptr) {
        _node = _node->left;
        while (_node->right != nullptr) {
            _node = _node->right;
        }
    } else {
        auto tmp = _node;
        while (_node->parent != nullptr && _node->parent->keyValuePair.first >= _node->keyValuePair.first) {
            _node = _node->parent;
        }
        _node = _node->parent == nullptr ? tmp : _node->parent;
    }
    return temp;
}

bool BinarySearchTree::ConstIterator::operator==(const BinarySearchTree::ConstIterator &other) const {
    return this->_node == other._node;
}

bool BinarySearchTree::ConstIterator::operator!=(const BinarySearchTree::ConstIterator &other) const {
    return this->_node != other._node;
}
