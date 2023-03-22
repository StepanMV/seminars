export module CppMisc:ArraySorts;

import <cstddef>;

export class ArraySorts
{
    public:
        template <typename T> static void bubbleSort(T* arr, size_t n)
        {
            for (size_t i = 0; i < n - 1; i++) {
                for (size_t j = 0; j < n - i - 1; j++) {
                    if (arr[j] > arr[j + 1]) {
                        swap<T>(arr[j], arr[j + 1]);
                    }
                }
            }
        }

        template <typename T> static void selectionSort(T* arr, size_t n)
        {
            for (size_t i = 0; i < n - 1; i++) {
                size_t minIndex = i;
                for (size_t j = i + 1; j < n; j++) {
                    if (arr[j] < arr[minIndex]) {
                        minIndex = j;
                    }
                }
                swap<T>(arr[i], arr[minIndex]);
            }
        }

        template <typename T> static void insertionSort(T* arr, size_t n)
        {
            for (size_t i = 1; i < n; i++) {
                T key = arr[i];
                size_t j = i - 1;
                while (j >= 0 && arr[j] > key) {
                    arr[j + 1] = arr[j];
                    j--;
                }
                arr[j + 1] = key;
            }
        }

        template <typename T> static void mergeSort(T* arr, size_t left, size_t right)
        {
            if (left < right) {
                size_t mid = left + (right - left) / 2;

                mergeSort<T>(arr, left, mid);
                mergeSort<T>(arr, mid + 1, right);

                merge<T>(arr, left, mid, right);
            }
        }
        template <typename T> static void quickSort(T* arr, int p, int r)
        {
            if (p < r)
            {
                int q = partition<T>(arr, p, r);
                quickSort<T>(arr, p, q - 1);
                quickSort<T>(arr, q + 1, r);
                
            }
        }

    private:
        template <typename T> static void swap(T& a, T& b)
        {
            auto temp = a;
            a = b;
            b = temp;
        }

        template <typename T> static void merge(T* arr, size_t left, size_t mid, size_t right)
        {
            size_t n1 = mid - left + 1;
            size_t n2 = right - mid;

            T L[n1], R[n2];

            for (size_t i = 0; i < n1; i++) {
                L[i] = arr[left + i];
            }
            for (size_t j = 0; j < n2; j++) {
                R[j] = arr[mid + 1 + j];
            }

            size_t i = 0, j = 0, k = left;

            while (i < n1 && j < n2) {
                if (L[i] <= R[j]) {
                    arr[k] = L[i];
                    i++;
                } else {
                    arr[k] = R[j];
                    j++;
                }
                k++;
            }

            while (i < n1) {
                arr[k] = L[i];
                i++;
                k++;
            }

            while (j < n2) {
                arr[k] = R[j];
                j++;
                k++;
            }
        }

        template <typename T> static int partition(T* arr, int p, int r)
        {
            T x = arr[r];
            int i = p - 1;
            for (int j = p; j <= r - 1; j++)
            {
                if (arr[j] < x)
                {
                    i++;
                    swap<T>(arr[i], arr[j]);
                }
            }
            swap<T>(arr[i + 1], arr[r]);
            return i + 1;
        }
};









