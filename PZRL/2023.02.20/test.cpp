#include <iostream>
#include "ArraysMisc.h"

int main()
{
    double* array = ArraysMisc::randDoubleArray(10);
    ArraysMisc::printArray(array, 10);
    return 0;
}
