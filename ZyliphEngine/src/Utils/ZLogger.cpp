#include "ZLogger.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Zyliph
{
    std::shared_ptr<spdlog::logger> ZLogger::z_CoreLogger;
    std::shared_ptr<spdlog::logger> ZLogger::z_ClientLogger;

    void ZLogger::Init()
    {
        spdlog::set_pattern("[%m/%d] [%T] [%n]: %^[%l]%$ %v");
        z_CoreLogger = spdlog::stdout_color_mt("Engine");
        z_CoreLogger->set_level(spdlog::level::trace);
        z_ClientLogger = spdlog::stdout_color_mt("Client");
        z_ClientLogger->set_level(spdlog::level::trace);
    }

}
