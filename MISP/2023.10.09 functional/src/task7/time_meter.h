#pragma once

#include <memory>
#include <cstdint>


class TimeMeterImpl;

class TimeMeter {
public:
    TimeMeter(unsigned count);
    ~TimeMeter();

    double setTimeStamp(unsigned num);
    double getSTimeStamp(unsigned num) const;
    int64_t getMSTimeStamp(unsigned num) const;

    double getSDiff(unsigned first, unsigned second) const;
    int64_t getMSDiff(unsigned first, unsigned second) const;

    bool isLess(unsigned first, unsigned second, int64_t expected) const;
    bool isLess(unsigned num, int64_t expected) const;

private:
    std::unique_ptr<TimeMeterImpl> impl;
};
