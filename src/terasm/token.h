#ifndef TOKEN_H
#define TOKEN_H

#include <string>

namespace termite {
    enum TokenType {
        NUMBER,
        IDENTIFIER,
        KEYWORD,
        REGISTER,
        COLON,
        SEMICOLON,
        COMMA,
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