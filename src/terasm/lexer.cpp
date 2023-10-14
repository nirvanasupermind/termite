#include <string>
#include "token.h"
#include "lexer.h"

namespace termite {
    Lexer::Lexer(const std::string& text)
        : text(text), pos(0), current(0) {
        advance();
    }

    void Lexer::advance() {
        if (pos < text.length()) {
            current = text.at(pos++);
        }
        else {
            current = 0;
        }
    }

    std::vector<Token> Lexer::generate_tokens() {
        std::vector<Token> tokens;

        while (current) {
            if (std::isspace(current)) {
                advance();
            }
            else if (current == '.' || std::isdigit(current)) {
                tokens.push_back(generate_number());
            }
            else if (current == '_'  || current == '-' || std::isalpha(current)) {
                tokens.push_back(generate_identifier());
            }
            else if (current == ':') {
                tokens.push_back(Token(TokenType::COLON, ":"));
                advance();
            }
            else if (current == ';') {
                tokens.push_back(Token(TokenType::SEMICOLON, ";"));
                advance();
            }
            else if (current == ',') {
                tokens.push_back(Token(TokenType::COMMA, ","));
                advance();
            }
            else {
                throw std::string("Error: illegal character '") + current + "'";
                break;
            }
        }
        
        // tokens.push_back(Token(TokenType::EOF_, ""));

        return tokens;
    }

    Token Lexer::generate_number() {
        int decimal_point_count = 0;
        std::string number_str(1, current);
        advance();

        while (current && (current == '.' || std::isdigit(current))) {
            if (current == '.') {
                if (++decimal_point_count > 1) {
                    break;
                }
            }

            number_str += current;
            advance();
        }

        if (number_str.at(0) == '.') {
            number_str = '0' + number_str;
        }

        if (number_str.at(number_str.length() - 1) == '.') {
            number_str += '0';
        }

        return Token(TokenType::NUMBER, number_str);
    }

    Token Lexer::generate_identifier() {
        std::string identifier_str(1, current);
        bool is_register = current == 'r';
        advance();

        while (current && (current == '_'  || current == '-' || std::isalnum(current))) {
            if(!(current == '-' || isdigit(current))) {
                is_register = false;
            }
            identifier_str += current;
            advance();
        }

        if (is_register) {
            return Token(TokenType::REGISTER, identifier_str);
        } else if(std::find(KEYWORDS.begin(), KEYWORDS.end(), identifier_str) != KEYWORDS.end()) {
            return Token(TokenType::KEYWORD, identifier_str);
        } else {
            return Token(TokenType::IDENTIFIER, identifier_str);
        }

    }
} // namespace termite