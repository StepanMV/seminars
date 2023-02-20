#include <stdio.h>
#include <math.h>
#include "complex.h"

Complex add(const Complex a, const Complex b) {
    Complex result;
    result.re = a.re + b.re;
    result.im = a.im + b.im;
    return result;
}

Complex multiply(const Complex a, const Complex b) {
    Complex result;
    result.re = a.re * b.re - a.im * b.im;
    result.im = a.re * b.im + a.im * b.re;
    return result;
}

Complex divide(const Complex a, const Complex b) {
    Complex linked = getLinked(b);
    Complex result = multiply(a, linked);
    result.re /= b.re * b.re + b.im * b.im;
    result.im /= b.re * b.re + b.im * b.im;
    return result;
}

Complex getLinked(const Complex a) {
    Complex result = a;
    result.im *= -1;
    return result;
}

float module(Complex a) {
    return (float) sqrt(pow(a.re, 2) + pow(a.im, 2));
}

float getArgument(Complex a) {
    return atanf(a.im / a.re);
}

void printAlg(Complex a) {
    printf("Complex Alg: %f + %fi\n", a.re, a.im);
}

void printTrig(Complex a) {
    float mod = module(a);
    float arg = getArgument(a);
    printf("Complex Trig: %f(cos(%f) + isin(%f))\n", mod, arg, arg);
}

void printExp(Complex a) {
    float mod = module(a);
    float arg = getArgument(a);
    printf("Complex Trig: %fe^(%fi)\n", mod, arg);
}