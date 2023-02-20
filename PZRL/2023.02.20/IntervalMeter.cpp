#include "IntervalMeter.h"
#include <chrono>

class IntervalMeter {
    std::chrono::steady_clock::time_point getTS() {
        return std::chrono::steady_clock::now();
    }

    std::chrono::nanoseconds getDiff(std::chrono::steady_clock::time_point ts1, std::chrono::steady_clock::time_point ts2) {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(ts2 - is1).count();
    }   
}
