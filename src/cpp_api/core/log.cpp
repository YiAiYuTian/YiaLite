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

void log(LogLevel level, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    std::string msg = spdlog::fmt_lib::vformat(
        format,
        spdlog::fmt_lib::make_format_args(args)
    );
    va_end(args);

    switch (level)
    {
    case LogLevel::Trace:
        Logger::instance().m_logger->trace(msg);
        break;
    case LogLevel::Info:
        Logger::instance().m_logger->info(msg);
        break;
    case LogLevel::Warn:
        Logger::instance().m_logger->warn(msg);
        break;
    case LogLevel::Err:
        Logger::instance().m_logger->error(msg);
        break;
    case LogLevel::Fatal:
        Logger::instance().m_logger->critical(msg);
        break;
    default:
        break;
    }
}

}