#ifndef YIALITE_STRING_VIEW_H
#define YIALITE_STRING_VIEW_H

#include "../../core/core.h"

namespace yialite
{

namespace detail
{
    constexpr size_t strlen(const char* str) noexcept
    {
        if (!str) return 0;
        size_t len = 0;
        while (str[len] != '\0') ++len;
        return len;
    }
}

class String;

class StringView
{
public:
    constexpr StringView() noexcept = default;
    constexpr StringView(const char* str) noexcept;
    YIALITE_API StringView(const String& str) noexcept;
    constexpr StringView(const char* str, size_t length) noexcept;

    [[nodiscard]] constexpr const char* data() const noexcept { return m_data; }
    [[nodiscard]] constexpr size_t length() const noexcept { return m_length; }
    [[nodiscard]] constexpr bool empty() const noexcept { return m_length == 0; }

    constexpr char operator[](size_t i) const noexcept { return m_data[i]; }

    constexpr StringView sub_str(size_t pos, size_t len = npos) const noexcept;
public:
    static constexpr size_t npos = static_cast<size_t>(-1);
private:
    const char* m_data = nullptr;
    size_t m_length = 0;
};

constexpr StringView::StringView(const char *str) noexcept
    : m_data(str), m_length(detail::strlen(str))
{
}

constexpr StringView::StringView(const char *str, size_t length) noexcept
    : m_data(str), m_length(length)
{
}

constexpr StringView StringView::sub_str(size_t pos, size_t len) const noexcept
{
    if (pos >= m_length) return StringView{};
    size_t new_len = (pos + len > m_length) ? m_length - pos : len;
    return StringView{ m_data + pos, new_len };
}

}

#endif