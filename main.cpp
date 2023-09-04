#include <iostream>
#include "SmartPtr.h"

using namespace std;

int main() {
    SmartPtr<int> myInt(new int(10));
    cout << myInt.get() << ", usages: " << myInt.useCount() << endl;
    if (true) {
        auto testInt = myInt;
        testInt.get() *= 13;
        cout << myInt.get() << ", usages: " << myInt.useCount() << endl;
        SmartPtr<int> insideTestInt(new int(testInt.get()));
        cout << insideTestInt.get() << ", usages: " << insideTestInt.useCount() << endl;
        insideTestInt.get()++;
        cout << insideTestInt.get() << ", usages: " << insideTestInt.useCount() << endl;
    }
    cout << myInt.get() << ", usages: " << myInt.useCount() << endl;
    return 0;
}