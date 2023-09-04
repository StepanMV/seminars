#include <iostream>
#include <stdexcept>

class Fraction {
private:
    int a, b;
public:
    Fraction() = default;
    Fraction(int a, int b) : a(a), b(b) {}
    [[nodiscard]] double result() const {
        if (b == 0) {
            throw std::runtime_error("Division by zero");
        }
        return (double)a / b;
    }
};

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " <numerator> <denominator>" << std::endl;
        return 1;
    }
    try {
        int a = std::stoi(argv[1]);
        int b = std::stoi(argv[2]);
        double res = Fraction(a, b).result();
        std::cout << "Result: " << res << std::endl;
    }
    catch (std::invalid_argument& e) {
        std::cout << "Invalid argument: " << e.what() << std::endl;
    }
    catch (std::runtime_error& e) {
        std::cout << "Runtime error: " << e.what() << std::endl;
    }
    catch (...) {}
    return 0;

}