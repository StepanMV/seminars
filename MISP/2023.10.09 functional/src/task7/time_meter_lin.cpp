#include "time_meter.h"
#include <ctime>
#include <vector>
#include <memory>
#include <stdexcept>

class TimeMeterImpl {
public:
    TimeMeterImpl(unsigned count) : timestamps(count) {
        clock_gettime(CLOCK_MONOTONIC, &start);
    }

    double setTimeStamp(unsigned num) {
        struct timespec counter;
        clock_gettime(CLOCK_MONOTONIC, &counter);
        timestamps[num] = counter.tv_sec * 1000000000 + counter.tv_nsec;
        return static_cast<double>(counter.tv_sec - start.tv_sec) + static_cast<double>(counter.tv_nsec - start.tv_nsec) / 1000000000;
    }

    double getSTimeStamp(unsigned num) const {
        return static_cast<double>(timestamps[num] - start.tv_sec * 1000000000 - start.tv_nsec) / 1000000000;
    }

    int64_t getMSTimeStamp(unsigned num) const {
        return (timestamps[num] - start.tv_sec * 1000000000 - start.tv_nsec) / 1000000;
    }

    double getSDiff(unsigned first, unsigned second) const {
        return static_cast<double>(timestamps[second] - timestamps[first]) / 1000000000;
    }

    int64_t getMSDiff(unsigned first, unsigned second) const {
        return (timestamps[second] - timestamps[first]) / 1000000;
    }

    bool isLess(unsigned first, unsigned second, int64_t expected) const {
        return (timestamps[second] - timestamps[first]) / 1000000 <= expected;
    }

    bool isLess(unsigned num, int64_t expected) const {
        struct timespec counter;
        clock_gettime(CLOCK_MONOTONIC, &counter);
        return (counter.tv_sec * 1000000000 + counter.tv_nsec - timestamps[num]) / 1000000 <= expected;
    }

private:
    struct timespec start;
    std::vector<int64_t> timestamps;
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