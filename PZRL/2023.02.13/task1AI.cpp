#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void insertionSort(int arr[], int n) {
    int key, j;
    for (int i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        // Move elements of arr[0..i-1], that are greater than key, to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int n;
    cout << "Enter the length of the array: ";
    cin >> n;

    int arr[n];

    // generate random numbers and store in the array
    srand(time(0)); // set the seed of the random number generator to the current time
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % (n + 1);
    }

    cout << "Unsorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Sort the array using insertion sort and calculate the time taken
    clock_t start, end;
    double time_taken;
    start = clock();

    insertionSort(arr, n);

    end = clock();
    time_taken = double(end - start) / CLOCKS_PER_SEC;

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "Time taken: " << time_taken << " seconds" << endl;

    return 0;
}
