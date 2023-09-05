#pragma once

#include <string>

class Polska {
public:
    explicit Polska(std::string rownanie);

    static bool isDigit(char c);

    static bool isAssociative(char c);

    static int priorityOf(char c);

    std::string toKurwa();

private:
    std::string rownanie;
};