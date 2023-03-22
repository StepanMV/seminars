#include <iostream>
#include <cmath>

struct Complex
{
    double r = 0;
    double phi = 0;
};

Complex enterComp(double newR, double newPhi)
{
    Complex comp;
    comp.r = newR;
    comp.phi = newPhi;
    return comp;
}

void printComp(Complex comp)
{
    std::cout << "Модуль = " << comp.r << "\t";
    std::cout << "Аргумент = " << comp.phi << std::endl;
    std::cout << "Число\t";
    if (comp.r == 1)
    {
        std::cout << std::cos(comp.phi);
        if (sin(comp.phi) >= 0)
            std::cout << "+" << std::sin(comp.phi) << "i\n";
        else
            std::cout << std::sin(comp.phi) << "i\n"; 
    }
    else
    {
        std::cout << comp.r << "(" << std::cos(comp.phi);
        if (sin(comp.phi) >= 0)
            std::cout << "+" << std::sin(comp.phi) << "i)\n";
        else
            std::cout << std::sin(comp.phi) << "i)\n"; 
    }
}

Complex compPow(Complex comp, int n)
{
    double newR = std::pow(comp.r, n);
    double newPhi = n * comp.phi;
    return enterComp(newR, newPhi);
}

int main()
{
    double r, phi;
    int n;

    std::cout << "Введите модуль числа: ";
    std::cin >> r;

    std::cout << "Введите аргумент числа: ";
    std::cin >> phi;

    std::cout << "Введите степень: ";
    std::cin >> n;
    std::cout << std::endl;

    Complex comp = enterComp(r, phi);
    Complex newComp = compPow(comp, n);

    std::cout << "Число: \n";
    printComp(comp);

    std::cout << "\nЧисло в степени: \n";
    printComp(newComp);
}
