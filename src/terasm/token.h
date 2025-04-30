#ifndef TOKEN_H
#define TOKEN_H

#include <string>

namespace termite {
    enum class TokenType {
        NUMBER,
        IDENTIFIER,
        INSTR_NAME,
        REG_NAME,
        COLON,
        COMMA,
        LPAREN,
        RPAREN,
        PLUS,
        DOLLAR,
        PERCENT,
        NEWLINE,
        EOF_
    };

    class Token {
    public:
        int line;
        TokenType type;
        std::string value;
        Token(int line, TokenType type, const std::string& value);
    };
} // namespace termite

#endif