#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <vector>

namespace termite {
    enum class TokenType {
        IDENTIFIER,
        REGISTER,
        COLON,
        COMMA,
        SEMICOLON,
        DEC_LITERAL,
        TER_LITERAL,
        NON_LITERAL,        
        EOF_
    };

    class Token {
    public:
        TokenType type;
        std::string val{};
        size_t line;
        Token() = default;
        Token(TokenType type, size_t line);
        Token(TokenType type, const std::string& val, size_t line);
        std::string str() const;
    };
} // namespace termite

#endif // TOKEN_H