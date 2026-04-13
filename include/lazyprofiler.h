#pragma once
#include <chrono>

#ifndef NDEBUG

#define END_PROFILE(name, message)                                     \
    auto name##_end = std::chrono::steady_clock::now();                \
    auto name = std::chrono::duration_cast<std::chrono::milliseconds>( \
        name##_end - name##_start);                                    \
    std::cout << (message) << ' ' << (name) << std::endl;

#define START_PROFILE(name) \
    auto name##_start = std::chrono::steady_clock::now();

#endif

#ifdef NDEBUG

#define END_PROFILE(name, message) ;
#define START_PROFILE(name) ;

#endif
