#ifndef LOG_H
#define LOG_H

#include "../utils/singleton.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace yialite
{

class Log final : public Singleton<Log>
{
    LITE_SINGLETON(Log);
public:
    std::shared_ptr<spdlog::logger> getLogger() const { return m_logger; }
private:
    Log();
    ~Log() = default;
private:
    std::shared_ptr<spdlog::logger> m_logger;
};

}

#if defined(LITE_LOG) || defined(_DEBUG)

#define LOG_TRACE(...) Log::instance().getLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)  Log::instance().getLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)  Log::instance().getLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) Log::instance().getLogger()->error(__VA_ARGS__)
#define LOG_FATAL(...) Log::instance().getLogger()->critical(__VA_ARGS__)

#else

#define LOG_TRACE(...)
#define LOG_INFO(...)
#define LOG_WARN(...)
#define LOG_ERROR(...)
#define LOG_FATAL(...)

#endif

#endif