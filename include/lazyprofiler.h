#pragma once
#include <chrono>

#ifndef NDEBUG
#endif

#define END_PROFILE(name)                                              \
    auto name##_end = std::chrono::steady_clock::now();                \
    auto name = std::chrono::duration_cast<std::chrono::milliseconds>( \
        name##_end - name##_start)

#define START_PROFILE(name) auto name##_start = std::chrono::steady_clock::now()

#if 0

#ifdef NDEBUG

#define END_PROFILE(name) (void)name
#define START_PROFILE(name) (void)name

#endif

#endif
