#include <iostream>

using namespace std;

void mySwap(int& a, int & b) {
    int t = a;
    a = b;
    b = t;
}

int main() {
    int a, b;
    cin >> a >> b;
    swap(a, b);
    cout << a << " " << b << endl;
    return 0;
}
