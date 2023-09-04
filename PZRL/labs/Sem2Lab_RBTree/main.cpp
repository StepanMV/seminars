#include "RBTree.h"
#include "BST.h"
#include <iostream>
#include <chrono>
#include <random>

using namespace std;

int amount;
int mode;

int main(int argc, char *argv[]) {
    if (argc != 3) return -1;
    amount = std::stoi(argv[1]);
    mode = std::stoi(argv[2]);
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, amount);
    BinarySearchTree binarySearchTree;
    RBTree rbTree;


    auto insertBSTStart = std::chrono::system_clock::now().time_since_epoch();
    if (mode == 0) for (int i = 0; i < amount; ++i) binarySearchTree.insert(i, 0);
    else if (mode == 1) for (int i = 0; i < amount; ++i) binarySearchTree.insert(dist(mt), 0);
    auto insertBSTEnd = std::chrono::system_clock::now().time_since_epoch();

    auto insertRBTStart = std::chrono::system_clock::now().time_since_epoch();
    if (mode == 0) for (int i = 0; i < amount; ++i) rbTree.insert(i, 0);
    else if (mode == 1) for (int i = 0; i < amount; ++i) rbTree.insert(dist(mt), 0);
    auto insertRBTEnd = std::chrono::system_clock::now().time_since_epoch();
    cout << "==========================================\n";
    cout << "Happy little RBTree:\n";
    cout << "==========================================\n\n";
    rbTree.visualise();

    auto findBSTStart = std::chrono::system_clock::now().time_since_epoch();
    for (int i = 0; i < amount / 100; ++i) binarySearchTree.find(dist(mt));
    auto findBSTEnd = std::chrono::system_clock::now().time_since_epoch();

    auto findRBTStart = std::chrono::system_clock::now().time_since_epoch();
    for (int i = 0; i < amount / 100; ++i) rbTree.find(dist(mt));
    auto findRBTEnd = std::chrono::system_clock::now().time_since_epoch();

    auto eraseBSTStart = std::chrono::system_clock::now().time_since_epoch();
    for (int i = 0; i < amount; ++i) binarySearchTree.erase(i);
    auto eraseBSTEnd = std::chrono::system_clock::now().time_since_epoch();

    auto eraseRBTStart = std::chrono::system_clock::now().time_since_epoch();
    for (int i = 0; i < amount; ++i) rbTree.erase(i);
    auto eraseRBTEnd = std::chrono::system_clock::now().time_since_epoch();

    cout << "==========================================\n";
    if (mode == 0) cout << "Worst case, " << amount << " nodes:\n";
    else if (mode == 1) cout << "Average case, " << amount << " nodes:\n";
    cout << "==========================================\n\n";
    cout << "INSERTION\n";
    cout << static_cast<double>((insertBSTEnd - insertBSTStart).count()) / 1000000000 << " - BST\n";
    cout << static_cast<double>((insertRBTEnd - insertRBTStart).count()) / 1000000000 << " - RBTree\n\n";
    cout << "SEARCH\n";
    cout << static_cast<double>((findBSTEnd - findBSTStart).count()) / 1000000000 << " - BST\n";
    cout << static_cast<double>((findRBTEnd - findRBTStart).count()) / 1000000000 << " - RBTree\n\n";
    cout << "ERASE\n";
    cout << static_cast<double>((eraseBSTEnd - eraseBSTStart).count()) / 1000000000 << " - BST\n";
    cout << static_cast<double>((eraseRBTEnd - eraseRBTStart).count()) / 1000000000 << " - RBTree\n\n";

    return 0;
}

/*
int main() {
    RBTree rbTree;
    rbTree.insert(9, 0);
    rbTree.insert(6, 0);
    rbTree.insert(7, 0);
    rbTree.insert(5, 0);
    rbTree.insert(999, 0);
    rbTree.insert(1, 0);
    rbTree.insert(99, 0);
    rbTree.insert(3, 0);
    rbTree.insert(3, 2);
    rbTree.insert(3, 3);
    rbTree.visualise();
    rbTree.insert(4, 0);
    rbTree.visualise();
    return 0;
}
*/