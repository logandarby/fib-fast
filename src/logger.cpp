#include "Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> Logger::m_coreLogger;

void Logger::init() {
    spdlog::set_pattern("%^[%T] %n: %v%$");
    m_coreLogger = spdlog::stdout_color_mt("App");
    m_coreLogger->set_level(spdlog::level::trace);
}
