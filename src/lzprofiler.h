#pragma once
#include <chrono>

#define START_PROFILE(name) auto name##_start = std::chrono::steady_clock::now()

#define END_PROFILE(name)                                              \
    auto name##_end = std::chrono::steady_clock::now();                \
    auto name = std::chrono::duration_cast<std::chrono::milliseconds>( \
        name##_end - name##_start)