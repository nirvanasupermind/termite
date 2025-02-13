#ifndef TOKEN_H
#define TOKEN_H

#include <string>

namespace termite {
    enum class TokenType {
        NUMBER,
        IDENTIFIER,
        INSTR_NAME,
        REGISTER,
        COLON,
        COMMA,
        LSQUARE,
        RSQUARE,
        PLUS,
        NEWLINE,
        EOF_  
    };

    class Token {
    public:
        TokenType type;
        std::string value;
        Token(TokenType type, const std::string& value);
    };
} // namespace termite

#endif