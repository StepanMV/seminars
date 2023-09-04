#include "BinarySearchTree.h"
#include <utility>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <iomanip>

// Node

BinarySearchTree::Node::Node(const BinarySearchTree::Node &other) {
    this->keyValuePair = other.keyValuePair;
    this->isRed = other.isRed;
}

// Node

BinarySearchTree::Node::Node(Key key, Value value, BinarySearchTree::Node *parent, BinarySearchTree::Node *left,
                             BinarySearchTree::Node *right) {
    this->keyValuePair = std::pair<Key, Value>(key, value);
    this->parent = parent;
    this->left = left;
    this->right = right;
}

BinarySearchTree::Node *BinarySearchTree::Node::findSuccessor(const Node *_nil) const {
    Node *node = const_cast<Node *>(this);
    if (node->right != _nil) {
        node = node->right;
        while (node->left != _nil) {
            node = node->left;
        }
    } else {
        auto tmp = node;
        while (node->parent != _nil && node->parent->keyValuePair.first <= node->keyValuePair.first) {
            node = node->parent;
        }
        node = node->parent == _nil ? tmp : node->parent;
    }
    return node;
}

BinarySearchTree::Node *BinarySearchTree::Node::findPredecessor(const Node *_nil) const {
    Node *node = const_cast<Node *>(this);
    if (node->left != _nil) {
        node = node->left;
        while (node->right != _nil) {
            node = node->right;
        }
    } else {
        auto tmp = node;
        while (node->parent != _nil && node->parent->keyValuePair.first >= node->keyValuePair.first) {
            node = node->parent;
        }
        node = node->parent == _nil ? tmp : node->parent;
    }
    return node;
}

// BinarySearchTree

BinarySearchTree::BinarySearchTree(const BinarySearchTree &other) : nil(new Node()) {
    this->_size = other._size;
    if (other._root) {
        this->_root = rootCopy(other._root, other.nil);
        this->_root->parent = nil;
    }
}

BinarySearchTree::Node *
BinarySearchTree::rootCopy(const BinarySearchTree::Node *root, const BinarySearchTree::Node *otherNil) {
    Node *newRoot = new BinarySearchTree::Node(*root);
    if (root->left != otherNil) {
        Node *subRoot = rootCopy(root->left, otherNil);
        newRoot->left = subRoot;
        newRoot->left->parent = _root;
    } else {
        newRoot->left = nil;
    }
    if (root->right != otherNil) {
        Node *subRoot = rootCopy(root->right, otherNil);
        newRoot->right = subRoot;
        newRoot->right->parent = _root;
    } else {
        newRoot->right = nil;
    }
    return newRoot;
}

void BinarySearchTree::rootDelete(BinarySearchTree::Node *root) {
    if (root->left != nil) {
        rootDelete(root->left);
    }
    if (root->right != nil) {
        rootDelete(root->right);
    }
    delete root;
}

BinarySearchTree &BinarySearchTree::operator=(const BinarySearchTree &other) {
    if (this == &other) {
        return *this;
    }
    delete _root;
    this->_size = other._size;
    if (other._root) {
        this->_root = rootCopy(other._root, other.nil);
        this->_root->parent = nil;
    }
    return *this;
}

BinarySearchTree::BinarySearchTree(BinarySearchTree &&other) noexcept: nil(new Node()) {
    this->_size = other._size;
    this->_root = other._root;
    other._size = 0;
    other._root = nil;
}

BinarySearchTree &BinarySearchTree::operator=(BinarySearchTree &&other) noexcept {
    if (this == &other) {
        return *this;
    }
    delete _root;
    this->_size = other._size;
    this->_root = other._root;
    other._size = 0;
    other._root = nil;
    return *this;
}

BinarySearchTree::~BinarySearchTree() {
    if (_root != nil) rootDelete(_root);
    delete nil;
}

void BinarySearchTree::insert(const Key &key, const Value &value) {
    std::cout << "Is NIL nullptr? " << (nil == nullptr) << std::endl;
    Node *z = findNode(key);
    if (z != nil) {
        z->keyValuePair.second = value;
        return;
    }
    z = new Node(key, value, nil, nil, nil);
    Node *y = nil;
    Node *x = _root;
    while (x != nil) {
        y = x;
        if (z->keyValuePair.first < x->keyValuePair.first) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == nil) {
        _root = z;
    } else if (z->keyValuePair.first < y->keyValuePair.first) {
        y->left = z;
    } else {
        y->right = z;
    }
    z->left = nil;
    z->right = nil;
    z->isRed = true;
    insertFixup(z);
    ++_size;
}

void BinarySearchTree::erase(const Key &key) {
    Node *z = findNode(key);
    if (z == nil) return;
    Node *y;
    if (z->left == nil || z->right == nil) {
        y = z;
    } else {
        y = z->findPredecessor(nil);
    }
    Node *x;
    if (y->left != nil) {
        x = y->left;
    } else {
        x = y->right;
    }
    x->parent = y->parent;
    if (y->parent == nil) {
        _root = x;
    } else if (y == y->parent->left) {
        y->parent->left = x;
    } else {
        y->parent->right = x;
    }
    if (y != z) {
        z->keyValuePair = y->keyValuePair;
    }
    if (!y->isRed) {
        eraseFixup(x);
    }
    --_size;
}

BinarySearchTree::ConstIterator BinarySearchTree::find(const Key &key) const {
    Node *node = _root;
    while (node != nil && node->keyValuePair.first != key) {
        if (key < node->keyValuePair.first) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return BinarySearchTree::ConstIterator(node, nil);
}

BinarySearchTree::Iterator BinarySearchTree::find(const Key &key) {
    Node *node = _root;
    while (node != nil && node->keyValuePair.first != key) {
        if (key < node->keyValuePair.first) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return BinarySearchTree::Iterator(node, nil);
}

std::pair<BinarySearchTree::Iterator, BinarySearchTree::Iterator> BinarySearchTree::equalRange(const Key &key) {
    Node *node = findNode(key);
    auto first = BinarySearchTree::Iterator(node, nil);
    while (node != nil && node->right != nil && node->right->keyValuePair.first == key) {
        node = node->right;
    }
    auto second = ++BinarySearchTree::Iterator(node, nil);
    return {first, second};
}

std::pair<BinarySearchTree::ConstIterator, BinarySearchTree::ConstIterator>
BinarySearchTree::equalRange(const Key &key) const {
    Node *node = findNode(key);
    auto first = BinarySearchTree::ConstIterator(node, nil);
    while (node != nil && node->right != nil && node->right->keyValuePair.first == key) {
        node = node->right;
    }
    auto second = ++BinarySearchTree::ConstIterator(node, nil);
    return {first, second};
}

BinarySearchTree::ConstIterator BinarySearchTree::min(const Key &key) const {
    Node *node = findNode(key);
    while (node != nil && node->left != nil) {
        node = node->left;
    }
    return BinarySearchTree::ConstIterator(node, nil);
}

BinarySearchTree::ConstIterator BinarySearchTree::max(const Key &key) const {
    Node *node = findNode(key);
    while (node != nil && node->right != nil) {
        node = node->right;
    }
    return BinarySearchTree::ConstIterator(node, nil);
}

BinarySearchTree::Iterator BinarySearchTree::begin() {
    if (_root == nil) {
        return BinarySearchTree::Iterator(nil, nil);
    }
    Node *node = _root;
    while (node->left != nil) {
        node = node->left;
    }
    return BinarySearchTree::Iterator(node, nil);
}

BinarySearchTree::Iterator BinarySearchTree::end() {
    if (_root == nil) {
        return BinarySearchTree::Iterator(nil, nil);
    }
    Node *node = _root;
    while (node->right != nil) {
        node = node->right;
    }
    return BinarySearchTree::Iterator(node, nil);
}

BinarySearchTree::ConstIterator BinarySearchTree::cbegin() const {
    if (_root == nil) {
        return BinarySearchTree::ConstIterator(nil, nil);
    }
    Node *node = _root;
    while (node->left != nil) {
        node = node->left;
    }
    return BinarySearchTree::ConstIterator(node, nil);
}

BinarySearchTree::ConstIterator BinarySearchTree::cend() const {
    if (_root == nil) {
        return BinarySearchTree::ConstIterator(nil, nil);
    }
    Node *node = _root;
    while (node->right != nil) {
        node = node->right;
    }
    return BinarySearchTree::ConstIterator(node, nil);
}

size_t BinarySearchTree::size() const {
    return _size;
}

bool BinarySearchTree::operator==(const BinarySearchTree &other) const {
    return this->_root == other._root;
}

bool BinarySearchTree::operator!=(const BinarySearchTree &other) const {
    return this->_root != other._root;
}

BinarySearchTree::Node *BinarySearchTree::findNode(const Key &key) const {
    Node *node = _root;
    while (node != nil && node->keyValuePair.first != key) {
        if (key < node->keyValuePair.first) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return node;
}

void BinarySearchTree::leftRotate(BinarySearchTree::Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != nil) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nil) {
        _root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void BinarySearchTree::rightRotate(BinarySearchTree::Node *x) {
    Node *y = x->left;
    x->left = y->right;
    if (y->right != nil) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nil) {
        _root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void BinarySearchTree::insertFixup(BinarySearchTree::Node *z) {
    while (z->parent->isRed) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;
            if (y->isRed) {
                z->parent->isRed = false;
                y->isRed = false;
                z->parent->parent->isRed = true;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->isRed = false;
                z->parent->parent->isRed = true;
                rightRotate(z->parent->parent);
            }
        } else {
            Node *y = z->parent->parent->left;
            if (y->isRed) {
                z->parent->isRed = false;
                y->isRed = false;
                z->parent->parent->isRed = true;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->isRed = false;
                z->parent->parent->isRed = true;
                leftRotate(z->parent->parent);
            }
        }
    }
    _root->isRed = false;
}

void BinarySearchTree::eraseFixup(BinarySearchTree::Node *x) {
    while (x != _root && !x->isRed) {
        if (x == x->parent->left) {
            Node *w = x->parent->right; //brother of x
            if (w->isRed) {
                w->isRed = false;
                x->parent->isRed = true;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (!w->left->isRed && !w->right->isRed) {
                w->isRed = true;
                x = x->parent;
            } else if (!w->right->isRed) {
                w->left->isRed = false;
                w->isRed = true;
                rightRotate(w);
                w = x->parent->right;
            } else {
                w->isRed = x->parent->isRed;
                x->parent->isRed = false;
                w->right->isRed = false;
                leftRotate(x->parent);
                x = _root;
            }
        } else {
            Node *w = x->parent->left;
            if (w->isRed) {
                w->isRed = false;
                x->parent->isRed = true;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            if (!w->right->isRed && !w->left->isRed) {
                w->isRed = true;
                x = x->parent;
            } else if (!w->left->isRed) {
                w->right->isRed = false;
                w->isRed = true;
                leftRotate(w);
                w = x->parent->left;
            } else {
                w->isRed = x->parent->isRed;
                x->parent->isRed = false;
                w->left->isRed = false;
                rightRotate(x->parent);
                x = _root;
            }
        }
    }
    x->isRed = false;
}

void BinarySearchTree::visualise() const {
    int numLen = floor(log10(max(_root->keyValuePair.first)->first)) + 1;
    int levels = findHeight(_root);
    int arrayLen = pow(2, levels) - 1;
    int **array;
    std::string emptyStr;
    for (int i = 0; i < numLen; ++i) emptyStr += " ";
    array = new int *[levels];
    for (int i = 0; i < levels; ++i)
        array[i] = new int[arrayLen];
    for (int i = 0; i < levels; ++i) {
        for (int j = 0; j < arrayLen; ++j) {
            array[i][j] = 0;
        }
    }
    fillArray(array, _root, 0, 0);
    for (int i = 0; i < levels; ++i) {
        for (int j = 0; j < arrayLen; ++j) {
            if (array[i][j] == 0) std::cout << emptyStr;
            else std::cout << std::setw(numLen) << array[i][j];
        }
        std::cout << "\n\n";
    }
}

void BinarySearchTree::fillArray(int **array, Node *root, int level, int pos) const {
    int levels = findHeight(_root);
    int arrayLen = pow(2, levels) - 1;
    int blockSize = arrayLen / pow(2, level);
    array[level][pos * blockSize + blockSize / 2 + pos] = root->keyValuePair.first;
    if (root->left != nil) fillArray(array, root->left, level + 1, 2 * pos);
    if (root->right != nil) fillArray(array, root->right, level + 1, 2 * pos + 1);
}

int BinarySearchTree::findHeight(Node *root) const {
    if (root->left != nil && root->right != nil) return std::max(findHeight(root->left), findHeight(root->right)) + 1;
    else if (root->left != nil) return findHeight(root->left) + 1;
    else if (root->right != nil) return findHeight(root->right) + 1;
    else return 1;

}

// Iterator

BinarySearchTree::Iterator::Iterator(BinarySearchTree::Node *node, const BinarySearchTree::Node *nil) {
    this->_node = node;
    this->nil = nil;
}

std::pair<Key, Value> &BinarySearchTree::Iterator::operator*() {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    return _node->keyValuePair;
}

const std::pair<Key, Value> &BinarySearchTree::Iterator::operator*() const {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    return _node->keyValuePair;
}

std::pair<Key, Value> *BinarySearchTree::Iterator::operator->() {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    return &_node->keyValuePair;
}

const std::pair<Key, Value> *BinarySearchTree::Iterator::operator->() const {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    return &_node->keyValuePair;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++() {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    _node = _node->findSuccessor(nil);
    return *this;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++(int) {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    BinarySearchTree::Iterator temp = *this;
    _node = _node->findSuccessor(nil);
    return temp;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--() {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    _node = _node->findPredecessor(nil);
    return *this;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--(int) {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    BinarySearchTree::Iterator temp = *this;
    _node = _node->findPredecessor(nil);
    return temp;
}

bool BinarySearchTree::Iterator::operator==(const BinarySearchTree::Iterator &other) const {
    return this->_node == other._node;
}

bool BinarySearchTree::Iterator::operator!=(const BinarySearchTree::Iterator &other) const {
    return this->_node != other._node;
}

// ConstIterator

BinarySearchTree::ConstIterator::ConstIterator(const BinarySearchTree::Node *node, const BinarySearchTree::Node *nil) {
    this->_node = node;
    this->nil = nil;
}

const std::pair<Key, Value> &BinarySearchTree::ConstIterator::operator*() const {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    return _node->keyValuePair;
}

const std::pair<Key, Value> *BinarySearchTree::ConstIterator::operator->() const {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    return &_node->keyValuePair;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++() {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    _node = _node->findSuccessor(nil);
    return *this;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++(int) {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    BinarySearchTree::ConstIterator temp = *this;
    _node = _node->findSuccessor(nil);
    return temp;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--(int) {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    _node = _node->findPredecessor(nil);
    return *this;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--() {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    BinarySearchTree::ConstIterator temp = *this;
    _node = _node->findPredecessor(nil);
    return temp;
}

bool BinarySearchTree::ConstIterator::operator==(const BinarySearchTree::ConstIterator &other) const {
    return this->_node == other._node;
}

bool BinarySearchTree::ConstIterator::operator!=(const BinarySearchTree::ConstIterator &other) const {
    return this->_node != other._node;
}
