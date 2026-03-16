#ifndef YIALITE_EXCEPTION_H
#define YIALITE_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace yialite
{

class YiaLite_Exception final : public std::exception
{

public:
    explicit YiaLite_Exception(std::string msg) : m_msg(std::move(msg)) {}
    ~YiaLite_Exception() noexcept override = default;

    const char* what() const noexcept override { return m_msg.c_str(); }
private:
    std::string m_msg;
};

}

#endif