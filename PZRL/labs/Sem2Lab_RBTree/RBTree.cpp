#include "RBTree.h"
#include <utility>
#include <stdexcept>
#include <iostream>
#include <cmath>
#include <iomanip>

// Node

RBTree::Node::Node(const RBTree::Node &other) {
    this->keyValuePair = other.keyValuePair;
    this->isRed = other.isRed;
}

// Node

RBTree::Node::Node(Key key, Value value, RBTree::Node *parent, RBTree::Node *left,
                   RBTree::Node *right) {
    this->keyValuePair = std::pair<Key, Value>(key, value);
    this->parent = parent;
    this->left = left;
    this->right = right;
}

RBTree::Node *RBTree::Node::findSuccessor(const Node *_nil) const {
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

RBTree::Node *RBTree::Node::findPredecessor(const Node *_nil) const {
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

// RBTree

RBTree::RBTree(const RBTree &other) : nil(new Node()) {
    this->_size = other._size;
    if (other._root) {
        this->_root = rootCopy(other._root, other.nil);
        this->_root->parent = nil;
    }
}

RBTree::Node *
RBTree::rootCopy(const RBTree::Node *root, const RBTree::Node *otherNil) {
    Node *newRoot = new RBTree::Node(*root);
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

void RBTree::rootDelete(RBTree::Node *root) {
    if (root->left != nil) {
        rootDelete(root->left);
    }
    if (root->right != nil) {
        rootDelete(root->right);
    }
    delete root;
}

RBTree &RBTree::operator=(const RBTree &other) {
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

RBTree::RBTree(RBTree &&other) noexcept: nil(new Node()) {
    this->_size = other._size;
    this->_root = other._root;
    other._size = 0;
    other._root = nil;
}

RBTree &RBTree::operator=(RBTree &&other) noexcept {
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

RBTree::~RBTree() {
    if (_root != nil) rootDelete(_root);
    delete nil;
}

void RBTree::insert(const Key &key, const Value &value) {
    //std::cout << "Is NIL nullptr? " << (nil == nullptr) << std::endl;
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

void RBTree::erase(const Key &key) {
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
    delete y;
    --_size;
}

RBTree::ConstIterator RBTree::find(const Key &key) const {
    Node *node = _root;
    while (node != nil && node->keyValuePair.first != key) {
        if (key < node->keyValuePair.first) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return RBTree::ConstIterator(node, nil);
}

RBTree::Iterator RBTree::find(const Key &key) {
    Node *node = _root;
    while (node != nil && node->keyValuePair.first != key) {
        if (key < node->keyValuePair.first) {
            node = node->left;
        } else {
            node = node->right;
        }
    }
    return RBTree::Iterator(node, nil);
}

std::pair<RBTree::Iterator, RBTree::Iterator> RBTree::equalRange(const Key &key) {
    Node *node = findNode(key);
    auto first = RBTree::Iterator(node, nil);
    while (node != nil && node->right != nil && node->right->keyValuePair.first == key) {
        node = node->right;
    }
    auto second = ++RBTree::Iterator(node, nil);
    return {first, second};
}

std::pair<RBTree::ConstIterator, RBTree::ConstIterator>
RBTree::equalRange(const Key &key) const {
    Node *node = findNode(key);
    auto first = RBTree::ConstIterator(node, nil);
    while (node != nil && node->right != nil && node->right->keyValuePair.first == key) {
        node = node->right;
    }
    auto second = ++RBTree::ConstIterator(node, nil);
    return {first, second};
}

RBTree::ConstIterator RBTree::min(const Key &key) const {
    Node *node = findNode(key);
    while (node != nil && node->left != nil) {
        node = node->left;
    }
    return RBTree::ConstIterator(node, nil);
}

RBTree::ConstIterator RBTree::max(const Key &key) const {
    Node *node = findNode(key);
    while (node != nil && node->right != nil) {
        node = node->right;
    }
    return RBTree::ConstIterator(node, nil);
}

RBTree::Iterator RBTree::begin() {
    if (_root == nil) {
        return RBTree::Iterator(nil, nil);
    }
    Node *node = _root;
    while (node->left != nil) {
        node = node->left;
    }
    return RBTree::Iterator(node, nil);
}

RBTree::Iterator RBTree::end() {
    if (_root == nil) {
        return RBTree::Iterator(nil, nil);
    }
    Node *node = _root;
    while (node->right != nil) {
        node = node->right;
    }
    return RBTree::Iterator(node, nil);
}

RBTree::ConstIterator RBTree::cbegin() const {
    if (_root == nil) {
        return RBTree::ConstIterator(nil, nil);
    }
    Node *node = _root;
    while (node->left != nil) {
        node = node->left;
    }
    return RBTree::ConstIterator(node, nil);
}

RBTree::ConstIterator RBTree::cend() const {
    if (_root == nil) {
        return RBTree::ConstIterator(nil, nil);
    }
    Node *node = _root;
    while (node->right != nil) {
        node = node->right;
    }
    return RBTree::ConstIterator(node, nil);
}

size_t RBTree::size() const {
    return _size;
}

bool RBTree::operator==(const RBTree &other) const {
    return this->_root == other._root;
}

bool RBTree::operator!=(const RBTree &other) const {
    return this->_root != other._root;
}

RBTree::Node *RBTree::findNode(const Key &key) const {
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

void RBTree::leftRotate(RBTree::Node *x) {
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

void RBTree::rightRotate(RBTree::Node *x) {
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

void RBTree::insertFixup(RBTree::Node *z) {
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

void RBTree::eraseFixup(RBTree::Node *x) {
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

void RBTree::visualise() const {
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
    for (int i = 0; i < levels; ++i) delete[] array[i];
    delete[] array;
}

void RBTree::fillArray(int **array, Node *root, int level, int pos) const {
    int levels = findHeight(_root);
    int arrayLen = pow(2, levels) - 1;
    int blockSize = arrayLen / pow(2, level);
    array[level][pos * blockSize + blockSize / 2 + pos] = root->keyValuePair.first;
    if (root->left != nil) fillArray(array, root->left, level + 1, 2 * pos);
    if (root->right != nil) fillArray(array, root->right, level + 1, 2 * pos + 1);
}

int RBTree::findHeight(Node *root) const {
    if (root->left != nil && root->right != nil) return std::max(findHeight(root->left), findHeight(root->right)) + 1;
    else if (root->left != nil) return findHeight(root->left) + 1;
    else if (root->right != nil) return findHeight(root->right) + 1;
    else return 1;

}

// Iterator

RBTree::Iterator::Iterator(RBTree::Node *node, const RBTree::Node *nil) {
    this->_node = node;
    this->nil = nil;
}

std::pair<Key, Value> &RBTree::Iterator::operator*() {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    return _node->keyValuePair;
}

const std::pair<Key, Value> &RBTree::Iterator::operator*() const {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    return _node->keyValuePair;
}

std::pair<Key, Value> *RBTree::Iterator::operator->() {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    return &_node->keyValuePair;
}

const std::pair<Key, Value> *RBTree::Iterator::operator->() const {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    return &_node->keyValuePair;
}

RBTree::Iterator RBTree::Iterator::operator++() {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    _node = _node->findSuccessor(nil);
    return *this;
}

RBTree::Iterator RBTree::Iterator::operator++(int) {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    RBTree::Iterator temp = *this;
    _node = _node->findSuccessor(nil);
    return temp;
}

RBTree::Iterator RBTree::Iterator::operator--() {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    _node = _node->findPredecessor(nil);
    return *this;
}

RBTree::Iterator RBTree::Iterator::operator--(int) {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    RBTree::Iterator temp = *this;
    _node = _node->findPredecessor(nil);
    return temp;
}

bool RBTree::Iterator::operator==(const RBTree::Iterator &other) const {
    return this->_node == other._node;
}

bool RBTree::Iterator::operator!=(const RBTree::Iterator &other) const {
    return this->_node != other._node;
}

// ConstIterator

RBTree::ConstIterator::ConstIterator(const RBTree::Node *node, const RBTree::Node *nil) {
    this->_node = node;
    this->nil = nil;
}

const std::pair<Key, Value> &RBTree::ConstIterator::operator*() const {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    return _node->keyValuePair;
}

const std::pair<Key, Value> *RBTree::ConstIterator::operator->() const {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    return &_node->keyValuePair;
}

RBTree::ConstIterator RBTree::ConstIterator::operator++() {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    _node = _node->findSuccessor(nil);
    return *this;
}

RBTree::ConstIterator RBTree::ConstIterator::operator++(int) {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    RBTree::ConstIterator temp = *this;
    _node = _node->findSuccessor(nil);
    return temp;
}

RBTree::ConstIterator RBTree::ConstIterator::operator--(int) {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    _node = _node->findPredecessor(nil);
    return *this;
}

RBTree::ConstIterator RBTree::ConstIterator::operator--() {
    if (_node == nil) {
        throw std::runtime_error("Iterator of nil");
    }
    RBTree::ConstIterator temp = *this;
    _node = _node->findPredecessor(nil);
    return temp;
}

bool RBTree::ConstIterator::operator==(const RBTree::ConstIterator &other) const {
    return this->_node == other._node;
}

bool RBTree::ConstIterator::operator!=(const RBTree::ConstIterator &other) const {
    return this->_node != other._node;
}
