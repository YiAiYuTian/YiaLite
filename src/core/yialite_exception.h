#ifndef YIALITE_EXCEPTION_H
#define YIALITE_EXCEPTION_H

#include "../utils/string/yia_string.h"
#include "../utils/utility.h"

#include <stdexcept>

namespace yialite
{

class YiaLite_Exception final : public std::exception
{
public:
    explicit YiaLite_Exception(String msg) : m_msg(yialite::move(msg)) {}
    ~YiaLite_Exception() noexcept override = default;

    const char* what() const noexcept override { return m_msg.cStr(); }
private:
    String m_msg;
};

}

#endif