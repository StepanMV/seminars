#include "time_meter.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
#include <memory>

void sleep(int seconds) {
    std::this_thread::sleep_for(std::chrono::seconds(seconds));
}

double runNCalc(std::function<void()> func) {
    TimeMeter timer(1);
    func();
    timer.setTimeStamp(0);
    return timer.getSTimeStamp(0);
}



int main() {

    auto arg = []() {std::this_thread::sleep_for(std::chrono::seconds(1));};
    std::cout << "Test 1: " << runNCalc(arg) << " seconds\n";

    auto arg2 = std::bind(sleep, 1);
    std::cout << "Test 2: " << runNCalc(arg2) << " seconds\n";

    std::vector<int> vec = {0, 1, 2, 3, 4};

    auto a = std::multiplies<int>();

    auto myPow = std::bind(std::multiplies<int>(), std::placeholders::_1, std::placeholders::_1);
    std::transform(vec.cbegin(), vec.cend(), vec.begin(), myPow);

    for (auto& it : vec) std::cout << it << " ";
    std::cout << std::endl;

    return 0;
}
