#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <random>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> timeRNG(1, 200);
std::uniform_int_distribution<> computeRNG(33, 174);

void heavyComputation(std::atomic<bool>& done, std::atomic<int>& progress, int total) {
    for (int i = 0; i < total; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(timeRNG(gen)));
        progress = (i + 1) * 100 / total;
        if (progress > 95) std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (progress == 99) std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
    done = true;
    std::cout << "\nComputation done!" << std::endl;
}

int main(int argc, char* argv[]) {
    std::atomic<bool> done(false);
    std::atomic<int> progress(0);

    std::thread t(heavyComputation, std::ref(done), std::ref(progress), computeRNG(gen));

    while (!done) {
        std::cout << "\rProgress: " << progress << "%";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    t.join();
    return 0;
}