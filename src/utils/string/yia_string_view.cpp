#include "pch.h"
#include "yia_string_view.h"
#include "yia_string.h"

namespace yialite
{

StringView::StringView(const String &str) noexcept
    : m_data(str.c_str()), m_length(str.length())
{
}

}
