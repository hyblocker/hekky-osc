#pragma once

#include "hekky/osc/debug.hpp"

#if defined(HEKKYOSC_DOASSERTS)
#include <iostream>
#define HEKKYOSC_ASSERT(condition, message) \
{ \
    if (!(condition)) \
    { \
        std::cerr << "Assert failed:\t" << (message) << "\n" << "Expected:\t" << (#condition) << "\n" << "Source:\t\t" << (__FILE__) << ", line " << (__LINE__) << "\n"; \
        DEBUGBREAK(); \
    } \
}
#else
#define HEKKYOSC_ASSERT(condition, message) ;
#endif