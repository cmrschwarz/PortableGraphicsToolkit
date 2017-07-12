#pragma once
#include <chrono>
namespace pgt {

    class Stopwatch {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock,
                                std::chrono::duration<double>>
            _start;

    public:
        Stopwatch();
        ~Stopwatch();
        double getElapsedTimeMicros() const;
        double getElapsedTimeMillis() const;
        double getElapsedTimeSeconds() const;
        void advanceStartByMillis(double millis);
        void setStart();
    };
}