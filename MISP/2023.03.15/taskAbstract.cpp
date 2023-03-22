#include <vector>
#include <cmath>

class Shape
{
    public:
        virtual double area() const = 0;
        virtual double perimeter() const = 0;
        virtual void print() const = 0;
        static void printVec(std::vector<Shape*> vec);
};

Triangle::Triangle(double a, double b, double c): a(a), b(b), c(c) { }

double Triangle::area() const
{
    double p = (a + b + c) / 2;
    return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

double Triangle::perimeter() const
{
    return a + b + c;
}

void Triangle::print() const
{
    std::cout << "Triangle: a = " << a << ", b = " << b << ", c = " << c;
    std::cout << ", area = " << this->area() << ", perimeter = " << this ->perimeter() << std::endl;
}

double Rect::area() const
{
    return a * b;
}

double Triangle::perimeter() const
{
    return a + a + b + b;
}

void Triangle::print() const
{
    std::cout << "Rect: a = " << a << ", b = " << b;
    std::cout << ", area = " << this->area() << ", perimeter = " << this ->perimeter() << std::endl;
}

Rect::Rect(double a, double b): a(a), b(b) { }

Circle::Circle(double r): r(r) { }



class Triangle : public Shape
{
    Triangle() = default;
    ~Triangle() = default;

    Triangle();

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


