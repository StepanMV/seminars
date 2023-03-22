#include "Timer.h"
#include <chrono>

void Timer::start()
{
     startTS = std::chrono::steady_clock::now();
}

void Timer::end()
{
    endTS = std::chrono::steady_clock::now();
    result = std::chrono::duration_cast<std::chrono::nanoseconds>(endTS - startTS).count();
}

long Timer::getResult()
{
    return result;
}
