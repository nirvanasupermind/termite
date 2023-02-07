#include <string>
#include <vector>
#include "token.h"

namespace termite {
    Token::Token(TokenType type, size_t line)
        : type(type), val(""), line(line) {
    }

    Token::Token(TokenType type, const std::string& val, size_t line)
        : type(type), val(val), line(line) {
    }

    std::string Token::str() const {
        std::string result;

        switch (type) {
        case TokenType::IDENTIFIER:
            result += "IDENTIFIER";
            break;
        case TokenType::REGISTER:
            result += "REGISTER";
            break;
        case TokenType::COLON:
            result += "COLON";
            break;
        case TokenType::COMMA:
            result += "COMMA";
            break;
        case TokenType::SEMICOLON:
            result += "SEMICOLON";
            break;
        case TokenType::DEC_LITERAL:
            result += "DEC_LITERAL";
            break;
        case TokenType::TER_LITERAL:
            result += "TER_LITERAL";
            break;
        case TokenType::NON_LITERAL:
            result += "NON_LITERAL";
            break;
        case TokenType::EOF_:
            result += "EOF";
            break;
        }

        if (val != "") {
            result += ":" + val;
        }

        return result;
    }
}