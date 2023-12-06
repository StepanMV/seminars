#include <iostream>
#include <cmath>
#include <variant>
#include <optional>

std::optional<int> parseCMD(std::string arg2) {
    try {
        return std::stoi(arg2);
    }
    catch (const std::invalid_argument& ex) {
        return {};
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " a b c" << std::endl;
        return 1;
    }
    double a = parseCMD(argv[1]).value_or(0);
    double b = parseCMD(argv[2]).value_or(0);
    double c = parseCMD(argv[3]).value_or(0);
    double d = b * b - 4 * a * c;
    std::variant<std::monostate, double> x1, x2;
    x1 = x2 = std::monostate();
    if (d == 0) {
        x1 = -b / (2 * a);
        x2 = -b / (2 * a);
    } else if (d > 0) {
        x1 = (-b + std::sqrt(d)) / (2 * a);
        x2 = (-b - std::sqrt(d)) / (2 * a);
    }

    try {
        std::cout << "x1 = " << std::get<double>(x1) << std::endl;
        std::cout << "x2 = " << std::get<double>(x2) << std::endl;
    }
    catch (const std::bad_variant_access& ex) {
    std::cout << "x2 = Complex" << std::endl;
    }

    return 0;
}