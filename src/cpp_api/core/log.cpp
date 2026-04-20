#include "log.h"
#include "logger.h"

namespace yialite
{

static spdlog::level::level_enum toSpdlogLevel(LogLevel level)
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

void setLogLevel(LogLevel level)
{
    Logger::setLogLevel(toSpdlogLevel(level));
}

void setLoggerEnabled(bool enabled)
{
    Logger::setLoggerEnabled(enabled);
}

void logImpl(LogLevel level, const std::string& msg)
{
    if (Logger::instance().m_is_logger_enabled)
        Logger::instance().m_logger->log(toSpdlogLevel(level), msg);
}

}