#include "pch.h"
#include "log.h"
#include "logger.h"

namespace yialite
{

static spdlog::level::level_enum to_spdlog_level(LogLevel level)
{
    switch (level)
    {
    case LogLevel::Trace:
        return spdlog::level::trace;
    case LogLevel::Info:
        return spdlog::level::info;
    case LogLevel::Warn:
        return spdlog::level::warn;
    case LogLevel::Err:
        return spdlog::level::err;
    case LogLevel::Fatal:
        return spdlog::level::critical;
    default:
        return spdlog::level::trace;
    }
}

void set_log_level(LogLevel level)
{
    Logger::set_log_level(to_spdlog_level(level));
}

void set_logger_enabled(bool enabled)
{
    Logger::set_logger_enabled(enabled);
}

void log_impl(LogLevel level, const char* msg)
{
    if (Logger::instance().m_is_logger_enabled)
        Logger::instance().m_logger->log(to_spdlog_level(level), msg);
}

}