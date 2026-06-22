#include "pch.h"
#include "yia_string_view.h"
#include "yia_string.h"

namespace yialite
{

StringView::StringView(const char *str) noexcept
    : m_data(str), m_length(str ? strlen(str) : 0)
{
}

StringView::StringView(const String &str) noexcept
    : m_data(str.c_str()), m_length(str.length())
{
}

StringView::StringView(const char *str, size_t length) noexcept
    : m_data(str), m_length(length)
{
}

StringView StringView::sub_str(size_t pos, size_t len) const noexcept
{
    if (pos >= m_length) return StringView{};
    size_t new_len = (pos + len > m_length) ? m_length - pos : len;
    return { m_data + pos, new_len };
}

}
