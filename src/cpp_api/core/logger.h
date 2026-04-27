#ifndef YIALITE_LOGGER_H
#define YIALITE_LOGGER_H

#include "../core/core.h"
#include "../utils/singleton.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/fmt.h>

namespace yialite
{

enum class LogLevel;

class Logger final : public Singleton<Logger>
{
    YIALITE_SINGLETON(Logger);
    friend YIALITE_API void logImpl(LogLevel, const char*);
public:
    static void setLoggerEnabled(bool enabled)
    {
        instance().m_is_logger_enabled = enabled;
    }

    static void setLogLevel(spdlog::level::level_enum level)
    {
        instance().m_logger->set_level(level);
    }

    template<typename... Args>
    static void trace(fmt::v12::format_string<Args...> fmt, Args&&... args)
    {
        if(!instance().m_is_logger_enabled) return;
        instance().m_logger->trace(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void info(fmt::v12::format_string<Args...> fmt, Args&&... args)
    {
        if(!instance().m_is_logger_enabled) return;
        instance().m_logger->info(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void warn(fmt::v12::format_string<Args...> fmt, Args&&... args)
    {
        if(!instance().m_is_logger_enabled) return;
        instance().m_logger->warn(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void error(fmt::v12::format_string<Args...> fmt, Args&&... args)
    {
        if(!instance().m_is_logger_enabled) return;
        instance().m_logger->error(fmt, std::forward<Args>(args)...);
    }

    template<typename... Args>
    static void fatal(fmt::v12::format_string<Args...> fmt, Args&&... args)
    {
        if(!instance().m_is_logger_enabled) return;
        instance().m_logger->critical(fmt, std::forward<Args>(args)...);
    }
private:
    Logger();
    ~Logger() = default;
private:
    bool m_is_logger_enabled = true;
    std::shared_ptr<spdlog::logger> m_logger;
};

}

#endif