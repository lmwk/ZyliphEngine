#pragma once
#include "Core.h"
#include "../Utils/ZLogger.h"
#include <filesystem>

#ifndef Z_ENABLE_ASSERTS

    #define Z_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { Z##type##ERROR(msg, __VA_ARGS__); Z_DEBUGBREAK(); } }
    #define Z_INTERNAL_ASSERT_WITH_MSG(type, check, ...) Z_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
    #define Z_INTERNAL_ASSERT_NO_MSG(type, check) Z_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", Z_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)

    #define Z_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
    #define Z_INTERNAL_ASSERT_GET_MACRO(...) Z_EXPAND_MACRO( Z_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, Z_INTERNAL_ASSERT_WITH_MSG, Z_INTERNAL_ASSERT_NO_MSG) )

    #define Z_ASSERT(...) Z_EXPAND_MACRO( Z_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_, __VA_ARGS__) )
    #define Z_CORE_ASSERT(...) Z_EXPAND_MACRO( Z_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )

#else
    #define Z_ASSERT(...)
    #define Z_CORE_ASSERT(...)
#endif