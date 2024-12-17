#pragma once

#include <spdlog/spdlog.h>
#include <memory>

class Logger {
public:
    static void init();
    static const std::shared_ptr<spdlog::logger> getCoreLogger() {
        return m_coreLogger;
    }

private:
    static std::shared_ptr<spdlog::logger> m_coreLogger;
};

// These macros should be used to log-- they can be disabled with release builds

#ifdef _DEBUG
    #define LOG_ERR(...) Logger::getCoreLogger()->error(__VA_ARGS__)
    #define LOG_WARN(...) Logger::getCoreLogger()->warn(__VA_ARGS__)
    #define LOG_INFO(...) Logger::getCoreLogger()->info(__VA_ARGS__)
    #define LOG_TRACE(...) Logger::getCoreLogger()->trace(__VA_ARGS__)
#else
    #define LOG_ERR(...)
    #define LOG_WARN(...)
    #define LOG_INFO(...)
    #define LOG_TRACE(...)
#endif  // _DEBUG
