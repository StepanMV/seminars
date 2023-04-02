#include <iostream>
#include "MyList.h"

int main()
{
    MyList newList = MyList();
    newList.add(1);
    newList.add(345345);
    newList.add(671);
    newList.add(3, 999);
    newList.print();
    return 0;
}
