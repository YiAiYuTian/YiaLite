#ifndef YIALITE_ERROR_H
#define YIALITE_ERROR_H

#include "../utils/utility.h"
#include "../utils/memory/allocator.h"
#include "../utils/string/yia_string.h"

#include <cstring>

namespace yialite
{

enum class ErrorCode : int
{
    Ok = 0,
    None,

    // General
    InvalidArg,
    OutOfMemory,
    NotImplemented,
    InternalError,

    // Initialization
    InitFailed,
    AlreadyInitialized,

    // Window
    WindowCreateFailed,

    // Renderer
    RendererCreateFailed,

    // Texture
    TextureLoadFailed,
    TextureCreateFailed,
    UnsupportedFormat,

    // Audio
    AudioEngineInitFailed,
    SoundLoadFailed,
    SoundNotFound,
    SoundPlayFailed,

    // I/O
    FileNotFound,
    FileReadFailed,
    FileWriteFailed,

    // Math
    SingularMatrix,
};

class YIALITE_API Error
{
public:
    static constexpr size_t INLINE_CAPACITY = 256;

    constexpr Error() noexcept : m_code(ErrorCode::Ok), m_length(0), m_msg{} {}
    constexpr Error(ErrorCode code) noexcept : m_code(code), m_length(0), m_msg{} {}
    Error(ErrorCode code, const char* message) noexcept : m_code(code), m_length(0), m_msg{} { set_message(message); }
    Error(const Error& e)
    {
        m_code = e.m_code;
        m_length = e.m_length;
        std::memcpy(m_msg, e.m_msg, m_length + 1);
    }
    Error(Error&& e) noexcept
    {
        m_code = e.m_code;
        m_length = e.m_length;
        std::memcpy(m_msg, e.m_msg, m_length + 1);

        e.m_code = ErrorCode::None;
        e.m_length = 0;
    }
    ~Error() noexcept = default;

    constexpr ErrorCode code() const noexcept { return m_code; }
    constexpr const char* message() const noexcept
    {
        if (m_length == 0) return "No error message. You can use ErrorCode to find this error";
        else return m_msg;
    }

    constexpr explicit operator bool() const noexcept { return m_code != ErrorCode::Ok; }
    constexpr bool operator!() const noexcept { return m_code == ErrorCode::Ok; }

    constexpr bool operator==(const Error& other) const noexcept { return m_code == other.m_code; }
    constexpr bool operator!=(const Error& other) const noexcept { return m_code != other.m_code; }
    constexpr bool operator==(ErrorCode code) const noexcept { return m_code == code; }
    constexpr bool operator!=(ErrorCode code) const noexcept { return m_code != code; }

    //operator
    Error& operator=(const Error& e)
    {
        if (this == &e) return *this;

        m_code = e.m_code;
        m_length = e.m_length;
        std::memcpy(m_msg, e.m_msg, m_length + 1);
        return *this;
    }

    Error& operator=(Error&& e) noexcept
    {
        if (this == &e) return *this;

        m_code = e.m_code;
        m_length = e.m_length;
        std::memcpy(m_msg, e.m_msg, m_length + 1);

        e.m_code = ErrorCode::None;
        e.m_length = 0;
        return *this;
    }
private:
    void set_message(const char* msg)
    {
        m_length = std::strlen(msg);
        std::memcpy(m_msg, msg, m_length + 1);
    }
private:
    ErrorCode m_code;
    
    size_t  m_length;
    char    m_msg[INLINE_CAPACITY + 1];
};

} // namespace yialite

#endif
