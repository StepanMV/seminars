#include <iostream>
#include "kurwa.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <equation>\n";
        return -1;
    }
    auto *equation = new Polska(argv[1]);
    std:: cout << equation->toKurwa() << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
