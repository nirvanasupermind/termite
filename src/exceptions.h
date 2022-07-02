#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include <stdexcept>

namespace termite
{
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
