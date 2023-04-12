#include <iostream>
#include <string>
#include <array>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "ArraysMisc.h"

int* ArraysMisc::enterIntArray(size_t len)
{
    std::string line;
    std::getline(std::cin, line);

    std::stringstream ss(line);
    std::vector<int> vec;

    int num;
    while (ss >> num)
    {
        vec.push_back(num);
    }
    int* array = new int[vec.size()];
    std::copy(vec.begin(), vec.end(), array);

    return array;
}

double* ArraysMisc::enterDoubleArray(size_t len)
{
    std::string line;
    std::getline(std::cin, line);

    std::stringstream ss(line);
    std::vector<double> vec;

    double num;
    while (ss >> num) 
    {
        vec.push_back(num);
    }
    double* array = new double[vec.size()];
    std::copy(vec.begin(), vec.end(), array);

    return array;
}

int* ArraysMisc::randIntArray(size_t len)
{
    srand(time(NULL));
    int* array = new int[len];
    for (size_t i = 0; i < len; ++i)
    {
        array[i] = rand() % (10 * len);
    }
    return array;
}

int* ArraysMisc::randIntArray(size_t len, int min, int max)
{
    srand(time(NULL));
    int* array = new int[len];
    for (size_t i = 0; i < len; ++i)
    {
        array[i] = rand() % (max - min + 1) + min;
    }
    return array;
}

double* ArraysMisc::randDoubleArray(size_t len)
{
    srand(time(NULL));
    double* array = new double[len];
    for (size_t i = 0; i < len; ++i)
    {
        double r = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
        array[i] = r * 10 * len;
    }
    return array;
}

double* ArraysMisc::randDoubleArray(size_t len, double min, double max)
{
    srand(time(NULL));
    double* array = new double[len];
    for (size_t i = 0; i < len; ++i)
    {
        double r = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
        array[i] = min + r * (max - min);
    }
}

void ArraysMisc::printArray(int* array, size_t len)
{
    for (size_t i = 0; i < len; ++i)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}

void ArraysMisc::printArray(double* array, size_t len)
{
    for (size_t i = 0; i < len; ++i)
    {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;
}
