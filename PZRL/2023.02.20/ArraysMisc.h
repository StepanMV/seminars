#ifndef ARRAYS_MISC_H
#define ARRAYS_MISC_H

class ArraysMisc
{
    public:
        static int* enterIntArray(size_t len);
        static double* enterDoubleArray(size_t len);
        static int* randIntArray(size_t len);
        static int* randIntArray(size_t len, int min, int max);
        static double* randDoubleArray(size_t len);
        static double* randDoubleArray(size_t len, double min, double max);
        static void printArray(int* array, size_t len);
        static void printArray(double* array, size_t len);
};

#endif
