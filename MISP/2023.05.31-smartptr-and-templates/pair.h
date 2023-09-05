#pragma once

template<typename T, typename N>
class Pair {
public:
    Pair(T f, N s) : first(f), second(s) {}
    T first;
    N second;
};