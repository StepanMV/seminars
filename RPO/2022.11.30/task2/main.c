#include <stdio.h>
#include "complex.h"

int main() {
    Complex comp1 = {10, -3};
    Complex comp2 = {6, 7};
    Complex comp = divide(comp1, comp2);
    printAlg(comp);
    printTrig(comp);
    printExp(comp);
    return 0;
}