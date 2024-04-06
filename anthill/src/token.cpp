#include <string>
#include "token.h"

namespace anthill {
    Token::Token(int line, TokenType type, const std::string& val)
        : line(line), type(type), val(val) {
    }


    std::string Token::type_str() const {
        switch (type) {
        case TokenType::INT:
            return "INT";
        case TokenType::CHAR:
            return "CHAR";
        case TokenType::STRING:
            return "STRING";
        case TokenType::IDENTIFIER:
            return "IDENTIFIER";
        case TokenType::KEYWORD:
            return "KEYWORD";
        case TokenType::PLUS:
            return "PLUS";
        case TokenType::MINUS:
            return "MINUS";
        case TokenType::MUL:
            return "MUL";
        case TokenType::DIV:
            return "DIV";
        case TokenType::MOD:
            return "MOD";
        case TokenType::AND:
            return "AND";
        case TokenType::OR:
            return "OR";
        case TokenType::XOR:
            return "OR";
        case TokenType::EQ:
            return "EQ";
        case TokenType::EE:
            return "EE";
        case TokenType::NE:
            return "NE";
        case TokenType::LT:
            return "LT";
        case TokenType::LE:
            return "LE";
        case TokenType::GT:
            return "GT";
        case TokenType::GE:
            return "GE";
        case TokenType::LPAREN:
            return "LPAREN";
        case TokenType::RPAREN:
            return "RPAREN";
        case TokenType::LCURLY:
            return "LCURLY";
        case TokenType::RCURLY:
            return "RCURLY";
        case TokenType::COMMA:
            return "COMMA";
        case TokenType::SEMICOLON:
            return "SEMICOLON";
        case TokenType::EOF_:
            return "EOF";
        default:
            return "UNKNOWN";
        }
    }

    std::string Token::str() const {
        return std::to_string(line) + ':' + type_str() + ':' + val;
    }

}; // namespace anthill