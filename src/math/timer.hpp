#pragma once

#include <chrono>
#include <iostream>

namespace timer {
    std::chrono::steady_clock::time_point start(const char *name) {
        std::cout << name << std::endl;
        return std::chrono::steady_clock::now();
    }

    void end(std::chrono::steady_clock::time_point start) {
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() << std::endl;
    }
}
