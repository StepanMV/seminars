#include "time_meter.h"
#include <windows.h>
#include <vector>
#include <memory>
#include <stdexcept>

class TimeMeterImpl {
public:

    TimeMeterImpl(unsigned count) : timestamps(count), frequency({0, 0}) {
        if (!QueryPerformanceFrequency(&frequency)) {
            throw std::runtime_error("Failed to get performance frequency");
        }
        QueryPerformanceCounter(&start);
    }

    double setTimeStamp(unsigned num) {
        LARGE_INTEGER counter;
        QueryPerformanceCounter(&counter);
        timestamps[num] = counter.QuadPart;
        return static_cast<double>(counter.QuadPart - start.QuadPart) / frequency.QuadPart;
    }

    double getSTimeStamp(unsigned num) const {
        return static_cast<double>(timestamps[num] - start.QuadPart) / frequency.QuadPart;
    }

    int64_t getMSTimeStamp(unsigned num) const {
        return (timestamps[num] - start.QuadPart) * 1000 / frequency.QuadPart;
    }

    double getSDiff(unsigned first, unsigned second) const {
        return static_cast<double>(timestamps[second] - timestamps[first]) / frequency.QuadPart;
    }

    int64_t getMSDiff(unsigned first, unsigned second) const {
        return (timestamps[second] - timestamps[first]) * 1000 / frequency.QuadPart;
    }

    bool isLess(unsigned first, unsigned second, int64_t expected) const {
        return (timestamps[second] - timestamps[first]) * 1000 <= expected * frequency.QuadPart;
    }

    bool isLess(unsigned num, int64_t expected) const {
        return (timestamps[num] - start.QuadPart) * 1000 <= expected * frequency.QuadPart;
    }

private:
    LARGE_INTEGER start;
    LARGE_INTEGER frequency;
    std::vector<LONGLONG> timestamps;
};

TimeMeter::TimeMeter(unsigned count) : impl(std::make_unique<TimeMeterImpl>(count)) {}

TimeMeter::~TimeMeter() = default;

double TimeMeter::setTimeStamp(unsigned num) {
    return impl->setTimeStamp(num);
}

double TimeMeter::getSTimeStamp(unsigned num) const {
    return impl->getSTimeStamp(num);
}

int64_t TimeMeter::getMSTimeStamp(unsigned num) const {
    return impl->getMSTimeStamp(num);
}

double TimeMeter::getSDiff(unsigned first, unsigned second) const {
    return impl->getSDiff(first, second);
}

int64_t TimeMeter::getMSDiff(unsigned first, unsigned second) const {
    return impl->getMSDiff(first, second);
}

bool TimeMeter::isLess(unsigned first, unsigned second, int64_t expected) const {
    return impl->isLess(first, second, expected);
}

bool TimeMeter::isLess(unsigned num, int64_t expected) const {
    return impl->isLess(num, expected);
}
