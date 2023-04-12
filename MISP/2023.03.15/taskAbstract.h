#pragma once
#include <vector>

class Shape
{
    public:
        virtual double area() const = 0;
        virtual double perimeter() const = 0;
        virtual void print() const = 0;
        static void printVec(std::vector<Shape*> vec);
};

class Triangle : public Shape
{
    Triangle() = default;
    ~Triangle() = default;

    Triangle(double a, double b, double c);

    private:
        double a, b, c;
};

class Rect : public Shape
{
    Rect() = default;
    ~Rect() = default;

    Rect(double a, double b);

    private:
        double a, b;
};


class Circle : public Shape
{
    Circ() = default;
    ~Circ() = default;

    Circ(double r);

    private:
        double r;
};


