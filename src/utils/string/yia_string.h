#ifndef YIALITE_STRING_H
#define YIALITE_STRING_H

#include "../../core/core.h"
#include "yia_string_view.h"

namespace yialite
{

class YIALITE_API String
{
public:
    String(const char* str = nullptr);
    String(size_t capacity);
    String(const char* str, size_t len);
    String(StringView str);
    String(const String& str);
    String(String&& str) noexcept;
    ~String() noexcept;

    [[nodiscard]] const char* c_str() const noexcept;
    [[nodiscard]] char* data() noexcept;
    [[nodiscard]] const char* data() const noexcept;

    [[nodiscard]] size_t length() const noexcept;
    [[nodiscard]] size_t capacity() const noexcept;
    char* begin() noexcept;
    char* end() noexcept;
    const char* begin() const noexcept;
    const char* end() const noexcept;

    //operators
    friend String operator+(const char* str1, const String& str2);
    String operator+(const String& str) const;
    String operator+(const char* str) const;
    String& operator+=(const char* str);
    String& operator+=(const String& str);
    String& operator=(const String& str);
    String& operator=(String&& str) noexcept;
    String& operator=(const char* str);
    char& operator[](size_t pos) noexcept;
    const char& operator[](size_t pos) const noexcept;
    bool operator==(const char* str) const;
    bool operator==(const String& str) const;
    bool operator!=(const char* str) const;
    bool operator!=(const String& str) const;

    //tools
    void append(const char* str);
    void append(const char* str, size_t count);
    void append(const String& str);
    void append(const String& str, size_t pos, size_t count = npos);
    void clear();
    String& erase(size_t pos, size_t count = npos);
    [[nodiscard]] String sub_str(size_t pos, size_t count = npos) const;
    [[nodiscard]] bool   empty() const noexcept;
    [[nodiscard]] size_t find(const char* str, size_t pos = 0) const;
    [[nodiscard]] size_t find(const String& str, size_t pos = 0) const;
    [[nodiscard]] size_t find_first_of(const char* str, size_t pos = 0) const;
    [[nodiscard]] size_t find_first_of(const String& str, size_t pos = 0) const;
    [[nodiscard]] size_t find_first_not_of(const char* str, size_t pos = 0) const;
    [[nodiscard]] size_t find_first_not_of(const String& str, size_t pos = 0) const;
    [[nodiscard]] size_t find_last_of(const char* str, size_t pos = npos) const;
    [[nodiscard]] size_t find_last_of(const String& str, size_t pos = npos) const;
    [[nodiscard]] size_t find_last_not_of(const char* str, size_t pos = npos) const;
    [[nodiscard]] size_t find_last_not_of(const String& str, size_t pos = npos) const;
public:
    static constexpr size_t npos = static_cast<size_t>(-1);
private:
    size_t calculate_capacity(size_t length) const;
private:
    char* m_data = nullptr;
    size_t m_length = 0;
    size_t m_capacity = 0;
};

}

#endif

