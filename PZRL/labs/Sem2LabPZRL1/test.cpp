#include <iostream>

int main()
{
    int* arr = new int[10];
    int* arr4 = new int[10000];
    int* arr2 = new int[10];
    delete[] arr4;

    arr[9] = 252;
    arr[arr2 - arr + 3] = 999;

    std::cout << "arr: \n"; 
    for (int i = 0; i < 10; ++i) 
    {
        std::cout << arr[i] << std::endl;
    }
    std::cout << std::endl;
    
    std::cout << "Element of arr2: \n";
    std::cout << arr[arr2 - arr + 3] << std::endl;
    std::cout << std::endl;
    std::cout << "arr2: \n"; 

    for (int i = 0; i < 10; ++i) 
    {
        std::cout << arr2[i] << std::endl;
    }
    delete[] arr;
    delete[] arr2;
    return 0;
}
