#ifndef YIALITE_STRING_VIEW_H
#define YIALITE_STRING_VIEW_H

#include "../../core/core.h"

namespace yialite
{

class String;

class YIALITE_API StringView
{
public:
    StringView() noexcept = default;
    StringView(const char* str) noexcept;
    StringView(const String& str) noexcept;
    StringView(const char* str, size_t length) noexcept;

    [[nodiscard]] const char* data() const noexcept { return m_data; }
    [[nodiscard]] size_t length() const noexcept { return m_length; }
    [[nodiscard]] bool empty() const noexcept { return m_length == 0; }

    char operator[](size_t i) const noexcept { return m_data[i]; }

    StringView subStr(size_t pos, size_t len = npos) const noexcept;
public:
    static constexpr size_t npos = static_cast<size_t>(-1);
private:
    const char* m_data = nullptr;
    size_t m_length = 0;
};

}

#endif