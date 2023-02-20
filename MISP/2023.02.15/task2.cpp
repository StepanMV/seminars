#include <iostream>

using namespace std;

namespace MySpace {
    int* facts(const int N) {
        int* arr = new int[N];
        arr[0] = 1;

        int current_fact = 1;
        for (size_t i = 1; i < N; ++i) {
            current_fact *= i;
            arr[i] = current_fact;
        }
        return arr;
    }
}


int main() {
    int N;
    cin >> N;
    int* arr = MySpace::facts(N);
    for (size_t i = 0; i < N; ++i) {
        cout << hex << arr[i] << " ";
    }
    cout << endl;
    delete[] arr;
    return 0;
}
