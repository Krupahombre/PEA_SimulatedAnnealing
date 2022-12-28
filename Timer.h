#pragma once

#include <chrono>

class Timer {

public:

    Timer() {
        start = std::chrono::high_resolution_clock::now();
    }

    void stop() {
        result = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start);
    }

    long getMicro() {
        return std::chrono::duration_cast<std::chrono::microseconds>(result).count();
    }

    long getNanos() {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(result).count();
    }

    long getMilis() {
        return std::chrono::duration_cast<std::chrono::milliseconds>(result).count();
    }

private:
    std::chrono::high_resolution_clock::time_point start {};
    std::chrono::nanoseconds result {};

};
