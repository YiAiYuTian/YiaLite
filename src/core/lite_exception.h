#ifndef LITE_EXCEPTION_H
#define LITE_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace lite
{

class Lite_Exception final : public std::exception
{

public:
    explicit Lite_Exception(std::string msg) : m_msg(std::move(msg)) {}
    ~Lite_Exception() noexcept override = default;

    const char* what() const noexcept override { return m_msg.c_str(); }
private:
    std::string m_msg;
};

}

#endif