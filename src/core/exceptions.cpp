//-*- core/exceptions.cpp -*-/
// Part of the Termite project
// Usage permitted under terms of MIT license

#include <string>
#include <stdexcept>

#include "exceptions.h"

namespace termite
{
    TermiteException::TermiteException(const std::string &what_message)
        : what_message(what_message)
    {
    }
    
    const char *TermiteException::what() const noexcept 
    {
        return what_message.c_str();
    }
} // namespace termite