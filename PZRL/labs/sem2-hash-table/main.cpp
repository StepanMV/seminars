#include <iostream>
#include "HashTable.h"

int main() {
    HashTable hashTable;
    hashTable.insert("ABC", 1);
    hashTable.insert("ABC", 2);
    hashTable.insert("ABD", 1);
    hashTable.insert("ACC", 1);
    hashTable.insert("I wetijiotwjeotwietjwoeijw", 1);
    std::cout << "Hello, World! " << hashTable["ACC"] << std::endl;
    return 0;
}
