#include <iostream>

#include "forward_list.h"

int main() {
    ForwardList<int> list;
    list.pushFront(3);
    list.pushFront(2);
    list.pushFront(1);

    while (!list.empty()) {
        std::cout << list.front() << " ";
        list.popFront();
    }

    return 0;
}
