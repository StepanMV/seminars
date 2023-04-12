export module CppMisc:ArraysMisc;

import <iostream>;
import <string>;
import <array>;
import <sstream>;
import <vector>;
import <cstdlib>;
import <ctime>;

export class ArraysMisc
{
    public:
        template <typename T> static T* enterArray(size_t len)
        {
            std::string line;
            std::getline(std::cin, line);

            std::stringstream ss(line);
            std::vector<T> vec;

            T num;
            while (ss >> num)
            {
                vec.push_back(num);
            }
            T* array = new T[vec.size()];
            std::copy(vec.begin(), vec.end(), array);

            return array;
        }

        template <typename T> static T* randomArray(size_t len, T min = 0, T max = -1)
        {
            max = max == -1 ? len * 10 - 1 : max;
            srand(time(NULL));
            T* array = new T[len];
            for (size_t i = 0; i < len; ++i)
            {
                double r = static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
                array[i] = static_cast<T>(min + r * (max - min));
            }
            return array;
        }

        template <typename T> static void printArray(T* array, size_t n)
        {
            for (size_t i = 0; i < n; ++i)
            {
                std::cout << array[i] << " ";
            }
            std::cout << std::endl;
        }
};
