#include <iostream>
#include "IntervalMeter.h"
using namespace std;

void merge(int array[], int const left, int const mid, int const right) {
	const int subArrayOne = mid - left + 1;
	const int subArrayTwo = right - mid;

	int *leftArray = new int[subArrayOne];
    int *rightArray = new int[subArrayTwo];

	for (int i = 0; i < subArrayOne; i++) leftArray[i] = array[left + i];
	for (int j = 0; j < subArrayTwo; j++) rightArray[j] = array[mid + 1 + j];

	int indexOfSubArrayOne = 0;
    int indexOfSubArrayTwo = 0;
	int indexOfMergedArray = left;

	while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
			array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else {
			array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}

	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}

	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}

	delete[] leftArray;
	delete[] rightArray;
}

void mergeSort(int array[], int const begin, int const end) {
	if (begin < end) {
        double mid = begin + (end - begin) / 2;
        mergeSort(array, begin, mid);
        mergeSort(array, mid + 1, end);
        merge(array, begin, mid, end);
    }
}

void printArray(int A[], int size)
{
	for (auto i = 0; i < size; i++)
		cout << A[i] << " ";
}

int main()
{
	int arr[] = { 12, 11, 13, 5, 6, 7 };
	double arr_size = sizeof(arr) / sizeof(arr[0]);
    IntervalMeter timer;

	cout << "Given array is \n";
	printArray(arr, arr_size);
    auto start = timer.getTS();
	mergeSort(arr, 0, arr_size - 1);
    auto end = timer.getTS();

	cout << "\nSorted array is \n";
	printArray(arr, arr_size);
    cout << endl;
    cout << "Sorted in " << reinterpret_cast<chrono::duration<double>>(timer.getDiff(start, end)) << " ns\n";
	return 0;
}

