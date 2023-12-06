#include "time_meter.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>

int main() {
    TimeMeter meter(4);

    std::vector<int> vec;
    for (int i = 0; i < 1000000; ++i) vec.push_back(i);
    
    meter.setTimeStamp(0);

    for (auto& it : vec) {
        continue;
    }

    meter.setTimeStamp(1);

    for (int i = 0; i < 1000000; ++i) {
        continue;
    }

    meter.setTimeStamp(2);

    for (int i = 0; i < 100; ++i) {
        continue;
    }

    meter.setTimeStamp(3);

    // std::cout << "Time 1: " << meter.getSTimeStamp(1) << " seconds" << std::endl;
    // std::cout << "Time 2: " << meter.getMSTimeStamp(2) << " milliseconds" << std::endl;

    std::cout << "Time difference between 0 and 1: " << meter.getSDiff(0, 1) << " seconds" << std::endl;
    std::cout << "Time difference between 1 and 2: " << meter.getSDiff(1, 2) << " seconds" << std::endl;
    std::cout << "Time difference between 2 and 3: " << meter.getSDiff(2, 3) << " seconds" << std::endl;

    // bool isLess = meter.isLess(0, 2, 5000);
    // std::cout << "Is time difference between 0 and 2 less than 5 seconds? " << (isLess ? "Yes" : "No") << std::endl;

    return 0;
}
