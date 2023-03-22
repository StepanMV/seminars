#include <iostream>
#include "MyList.h"

int main()
{
    MyList<std::string> newList = MyList<std::string>();
    newList.push_back("123");
    newList.push_back("Hello");
    newList.push_back("world");
    newList.print();
    newList.remove_first();
    newList.remove_last();
    newList.print();
    return 0;
}
