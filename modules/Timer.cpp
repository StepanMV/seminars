export module CppMisc:Timer;

import <chrono>;

export class Timer
{
    private:
        std::chrono::steady_clock::time_point startTS;
        std::chrono::steady_clock::time_point endTS;
        long result;

    public:
        Timer() { }
        ~Timer() { }

        void start()
        {
            startTS = std::chrono::steady_clock::now();
        }

        void end()
        {
            endTS = std::chrono::steady_clock::now();
            result = std::chrono::duration_cast<std::chrono::nanoseconds>(endTS - startTS).count();
        }

        long getResult() const
        {
            return result;
        }
};
