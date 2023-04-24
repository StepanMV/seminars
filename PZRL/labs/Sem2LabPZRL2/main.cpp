
#include <iostream>
#include "Stack.h"

using namespace std;

int main()
{
    ValueType* values = new ValueType[10];
    for (size_t i = 0; i < 10; ++i)
    {
        values[i] = i;
    }
    Stack stack = Stack(values, 10, StackContainer::Vector);
    for (size_t i = 0; i < 10; ++i)
    {
        stack.pop();
    }
    cout << stack.top() << endl;
    cout << stack.isEmpty() << endl;
    cout << "Hello World!" << endl;
    Stack stack2;
    stack2 = Stack(stack);
    cout << stack2.top() << endl;
    return 0;
}
