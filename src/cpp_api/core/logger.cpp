#include "logger.h"
#include "../utils/string/yia_string.h"

#include <iostream>

namespace yialite
{

Logger::Logger()
{
    try
    {
        m_logger = spdlog::stdout_color_mt("Lite");
        m_logger->set_pattern("%^[%H:%M:%S][%n(%l)]:%v%$");
        m_logger->set_level(spdlog::level::trace);
    }
    catch(const spdlog::spdlog_ex& e)
    {
        std::cerr << e.what() << '\n';
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

}

template<>
struct fmt::formatter<yialite::String>
{
    constexpr auto parse(format_parse_context& ctx)
    {
        return ctx.begin();
    }

    template<typename FormatContext>
    auto format(const yialite::String& str, FormatContext& ctx) const
    {
        return fmt::format_to(ctx.out(), "{}", str.cStr());
    }
};