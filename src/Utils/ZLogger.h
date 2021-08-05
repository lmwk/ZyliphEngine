#pragma once

#include <spdlog/spdlog.h>
#include "../Core/Core.h"


namespace Zyliph
{
    class Z_API ZLogger
    {
    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return z_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return z_ClientLogger; }
    private:
        static  std::shared_ptr<spdlog::logger> z_CoreLogger;
        static std::shared_ptr<spdlog::logger> z_ClientLogger;
    };
} 