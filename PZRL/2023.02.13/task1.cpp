#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;


void bubbleSort(int* array, int n) {
    for(int i = 0; i < n  - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

void insertionSort(int* array, int n) {
    for(int i = 1; i < n; i++) {
        int key = array[i];
        int j = i - 1;
        while ((j >= 0) && (array[j] > key)) {
            array[j + 1] = array[j];
            j -= 1;
        }
        array[j + 1] = key;
    }
}

int main() {
    srand(time(NULL));
    int n;
    cin >> n;
    int arr[n];
    clock_t start, end;
    double time_taken;

    for(int i = 0; i < n; i++) {
        arr[i] = rand() % n;
    }

    start = clock();
    insertionSort(arr, n);
    end = clock();
    time_taken = double(end - start) / CLOCKS_PER_SEC;
    
    cout << endl;
    cout << "INSERTION Time taken: " << time_taken << " seconds" << endl;

    for(int i = 0; i < n; i++) {
        arr[i] = rand() % n;
    }

    start= clock();
    bubbleSort(arr, n);
    end = clock();
    time_taken = double(end - start) / CLOCKS_PER_SEC;
    
    cout << endl;
    cout << "BUBBLE Time taken: " << time_taken << " seconds" << endl;
    return 0;
}
