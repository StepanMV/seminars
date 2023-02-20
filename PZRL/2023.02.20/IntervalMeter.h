#ifndef INTERVAL_METER_H
#define INTERVAL_METER_H
#include <chrono>

class IntervalMeter {
    public:
        std::chrono::steady_clock::time_point getTS();
        std::chrono::nanoseconds getDiff(std::chrono::steady_clock::time_point ts1, std::chrono::steady_clock::time_point ts2);
};

#endif
