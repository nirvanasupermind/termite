#ifndef TOKEN_H
#define TOKEN_H

#include <string>

namespace anthill {
    enum class TokenType {
        INT,
        CHAR,
        STRING,
        IDENTIFIER,
        KEYWORD,
        PLUS,
        MINUS,
        MUL,
        DIV,
        MOD,
        AND,
        OR,
        XOR,
        EQ,
        EE,
        NE,
        LT,
        LE,
        GT,
        GE,
        LPAREN,
        RPAREN,
        LCURLY,
        RCURLY,
        COMMA,
        SEMICOLON,
        EOF_
    };

    class Token {
    public:
        int line;
        TokenType type;
        std::string val;
        Token(int line, TokenType type, const std::string& val);
        std::string type_str() const;
        std::string str() const;
    };

} // namespace anthill

#endif // TOKEN_H