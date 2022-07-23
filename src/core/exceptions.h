//-*- core/exceptions.h -*-/
// Part of the Termite project
// Usage permitted under terms of MIT license

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include <stdexcept>

namespace termite
{
    // Exception class for Termite-related exceptions

    class TermiteException : public std::exception
    {
    protected:
        std::string what_message;
    public:
        TermiteException(const std::string &what_message);
        
        const char *what() const noexcept;
    };
} // namespace termite

#endif
