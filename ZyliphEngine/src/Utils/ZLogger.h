#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include "../Core/Core.h"


namespace Zyliph
{
    class ZLogger
    {
    public:
        static void Init();

        static std::shared_ptr<spdlog::logger> GetCoreLogger() { return z_CoreLogger; }
        static std::shared_ptr<spdlog::logger> GetClientLogger() { return z_ClientLogger; }
    private:
        static  std::shared_ptr<spdlog::logger> z_CoreLogger;
        static std::shared_ptr<spdlog::logger> z_ClientLogger;
    };
}

// Engine logging macros
#define Z_CORE_ERROR(...)           ::Zyliph::ZLogger::GetCoreLogger()->error(__VA_ARGS__)
#define Z_CORE_WARN(...)            ::Zyliph::ZLogger::GetCoreLogger()->warn(__VA_ARGS__)
#define Z_CORE_INFO(...)              ::Zyliph::ZLogger::GetCoreLogger()->info(__VA_ARGS__)
#define Z_CORE_TRACE(...)            ::Zyliph::ZLogger::GetCoreLogger()->trace(__VA_ARGS__)
#define Z_CORE_CRITICAL(...)        ::Zyliph::ZLogger::GetCoreLogger()->critical(__VA_ARGS__)

// Client  logging macros
#define Z_CLIENT_ERROR(...)            ::Zyliph::ZLogger::GetClientLogger()->error(__VA_ARGS__)
#define Z_CLIENT_WARN(...)             ::Zyliph::ZLogger::GetClientLogger()->warn(__VA_ARGS__)
#define Z_CLIENT_INFO(...)               ::Zyliph::ZLogger::GetClientLogger()->info(__VA_ARGS__)
#define Z_CLIENT_TRACE(...)             ::Zyliph::ZLogger::GetClientLogger()->trace(__VA_ARGS__)
#define Z_CLIENT_CRITICAL(...)         ::Zyliph::ZLogger::GetClientLogger()->critical(__VA_ARGS__)