#include "ZLogger.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace Zyliph
{
    std::shared_ptr<spdlog::logger> ZLogger::z_CoreLogger;
    std::shared_ptr<spdlog::logger> ZLogger::z_ClientLogger;

    void ZLogger::Init()
    {

        spdlog::set_pattern("[%m/%d] [%T] [%n]: %^[%l]%$ %v");

        z_CoreLogger = std::make_shared<spdlog::logger>("Engine", std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        spdlog::register_logger(z_CoreLogger);
        z_CoreLogger->set_level(spdlog::level::trace);
        z_CoreLogger->flush_on(spdlog::level::trace);
        z_ClientLogger = std::make_shared<spdlog::logger>("Client", std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        spdlog::register_logger(z_ClientLogger);
        z_ClientLogger->set_level(spdlog::level::trace);
        z_ClientLogger->flush_on(spdlog::level::trace);
    }

}
