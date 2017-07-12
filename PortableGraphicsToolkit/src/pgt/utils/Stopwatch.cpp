#include "Stopwatch.h"

namespace pgt {

    Stopwatch::Stopwatch()
    {
        setStart();
    }
    Stopwatch::~Stopwatch()
    {
    }
    void Stopwatch::setStart()
    {
        _start = std::chrono::high_resolution_clock::now();
    }

    void Stopwatch::advanceStartByMillis(double millis)
    {
        _start += std::chrono::duration<double, std::milli>(millis);
    }
    double Stopwatch::getElapsedTimeMicros() const
    {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::micro> elapsed = end - _start;
        return elapsed.count();
    }
    double Stopwatch::getElapsedTimeMillis() const
    {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - _start;
        return elapsed.count();
    }
    double Stopwatch::getElapsedTimeSeconds() const
    {
        return getElapsedTimeMicros() / 1000000.0;
    }
}