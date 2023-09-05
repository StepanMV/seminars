#include "kurwa.h"

#include <utility>
#include <stack>
#include <stdexcept>

Polska::Polska(std::string rownanie) : rownanie(std::move(rownanie)) {}

bool Polska::isDigit(char c) {
    return c >= '0' && c <= '9';
}

bool Polska::isAssociative(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int Polska::priorityOf(char c) {
    if (c == '+' || c == '-') {
        return 1;
    } else if (c == '*' || c == '/') {
        return 2;
    } else if (c == '^') {
        return 3;
    } else {
        return -1;
    }
}

std::string Polska::toKurwa() {
    auto stack = new std::stack<char>();
    std::string output;

    for (char c: rownanie) {
        if (isDigit(c)) {
            output += c;
        } else if (c == '(') {
            stack->push(c);
        } else if (c == ')') {
            while (!stack->empty() && stack->top() != '(') {
                output += stack->top();
                stack->pop();
            }
            stack->pop();
        } else {
            while (!stack->empty() && priorityOf(c) <= priorityOf(stack->top()) && isAssociative(c)) {
                output += stack->top();
                stack->pop();
            }
            stack->push(c);
        }
    }

    while (!stack->empty()) {
        if (stack->top() == '(') {
            throw std::runtime_error("Kurwa, ja pierdole");
        }
        output += stack->top();
        stack->pop();
    }

    return output;
}
