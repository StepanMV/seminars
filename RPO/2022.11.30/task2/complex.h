#ifndef STUDYING_COMPLEX_H
#define STUDYING_COMPLEX_H

typedef struct {
    float re;
    float im;
} Complex;

Complex add(Complex a, Complex b);

Complex multiply(Complex a, Complex b);

Complex divide(Complex a, Complex b);

Complex getLinked(Complex a);

float module(Complex a);

float getArgument(Complex a);

void printAlg(Complex a);

void printTrig(Complex a);

void printExp(Complex a);

#endif //STUDYING_COMPLEX_H
