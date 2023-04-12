
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
    Stack* stack = new Stack(values, 10, StackContainer::Vector);
    cout << stack->isEmpty() << endl;
    cout << "Hello World!" << endl;
    return 0;
}
