#ifndef TIMER_H
#define TIMER_H
#include <chrono>

class Timer {
    private:
        std::chrono::steady_clock::time_point startTS;
        std::chrono::steady_clock::time_point endTS;
        long result;
    public:
        void start();
        void end();
        long getResult();
};

#endif
