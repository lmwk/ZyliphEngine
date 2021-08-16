#pragma once

#include <memory>

#include "PlatformDetection.h"

#ifdef Z_DEBUG
    #if defined(Z_PLATFORM_WINDOWS)
        #define Z_DEBUGBREAK() __debugbreak()
    #elif defined(Z_PLATFORM_LINUX)
        #include <signal.h>
        #define Z_DEBUGBREAK() raise(SIGTRAP)
    #else
        #error "Platform doesn't support debugbreak yet!"
    #endif
    #define Z_ENABLE_ASSERTS
#else
    #define Z_DEBUGBREAK()
#endif

#ifdef Z_PLATFORM_WINDOWS
    #ifdef Z_BUILD_DLL
        #define Z_API __declspec(dllexport)
    #else
        #define Z_API __declspec(dllimport)
    #endif
#else
    #error Zyliph Engine doesn't support this platform yet
#endif

#define Z_EXPAND_MACRO(x) x
#define Z_STRINGIFY_MACRO(x) #x

#define BIT(x) (1 << x)

#define Z_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Zyliph
{
    template<typename T>
    using Scope = std::unique_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Scope<T> CreateScope(Args&& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    using Ref = std::shared_ptr<T>;
    template<typename T, typename ... Args>
    constexpr Ref<T> CreateRef(Args&& ... args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}