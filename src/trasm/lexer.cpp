#include <string>
#include <vector>
#include "token.h"
#include "lexer.h"

namespace termite {
    Lexer::Lexer(const std::string& text, const std::string& filename)
        : text(text), pos(0), filename(filename), line(1), current(0) {
        advance();
    }

    void Lexer::advance() {
        if (pos < text.length()) {
            current = text.at(pos++);
        }
        else {
            current = '\0';
        }

        if (current == '\n') {
            line++;
        }
    }

    std::vector<Token> Lexer::generate_tokens() {
        std::vector<Token> tokens;

        while (current) {
            if (WHITESPACE.find_first_of(current) != std::string::npos) {
                advance();
            }
            else if (DEC_DIGITS.find_first_of(current) != std::string::npos) {
                tokens.push_back(generate_number());
            }
            else if (current == ':') {
                advance();
                tokens.push_back(Token(TokenType::COLON, line));
            }
            else {
                throw std::string(std::to_string(line) + ": " + "Illegal character '" + std::string(1, current) + "'");
            }
        }

        return tokens;
    }

    Token Lexer::generate_number() {
        std::size_t decimal_point_count = 0;
        std::string number_str(1, current);
        bool leading_zero = current == '0';
        advance();
        if (leading_zero && current == 't') {
            // Ternary literal
            number_str.pop_back();
            advance();

            while (current && (TER_DIGITS.find_first_of(current) != std::string::npos)) {
                number_str += current;
                advance();
            }

            return Token(TokenType::TER_LITERAL, number_str, line);
        } else if (leading_zero && current == 'n') {
            // Nonary literal
            number_str.pop_back();
            advance();

            while (current && (NON_DIGITS.find_first_of(current) != std::string::npos)) {
                number_str += current;
                advance();
            }

            return Token(TokenType::NON_LITERAL, number_str, line);
        } else {
            // Decimal literal
            while (current && (DEC_DIGITS.find_first_of(current) != std::string::npos)) {
                number_str += current;
                advance();
            }

            return Token(TokenType::DEC_LITERAL, number_str, line);
        }
    }

} // namespace termite