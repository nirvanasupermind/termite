#include <string>
#include <iostream>
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
            if (current == ' ' || current == '\r' || current == '\t') {
                advance();
            }
            else if (current == '.' || current == '-' || std::isdigit(current)) {
                tokens.push_back(generate_number());
            }
            else if (current == ';') {
                while(current && current != '\n') {
                    advance();
                }
            }
            else if (current == '_' || std::isalpha(current)) {
                tokens.push_back(generate_identifier());
            }
            else if (current == ':') {
                tokens.push_back(Token(TokenType::COLON, ":"));
                advance();
            }
            else if (current == ',') {
                tokens.push_back(Token(TokenType::COMMA, ","));
                advance();
            }
            else if (current == '[') {
                tokens.push_back(Token(TokenType::LSQUARE, "["));
                advance();
            }
            else if (current == ']') {
                tokens.push_back(Token(TokenType::RSQUARE, "]"));
                advance();
            }
            else if (current == '+') {
                tokens.push_back(Token(TokenType::PLUS, "+"));
                advance();
            }
            else if (current == '\n') {
                tokens.push_back(Token(TokenType::NEWLINE, "\n"));
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
        std::string number_str(1, current);
        if (current == '0') {
            advance();

            if(current == 't') {
                number_str += current;
                advance();
                        
                while (current && (current == 'A' || current == 'a' || current == '0' | current == '1')) {
                    number_str += current;
                    advance();
                }
            } else if(current == 'n') {
                number_str += current;
                advance();
                while (current && (current == 'A' || current == 'a'  || current == 'B' || current == 'b'
                    || current == 'C' || current == 'c' || current == 'D' || current == 'd'
                    || current == '0' | current == '1' || current == '2' || current == '3' || current == '4')) {
                    number_str += current;
                    advance();
                }
            }
        }
        else {
            advance();
            while (current && std::isdigit(current)) {
                number_str += current;
                advance();
            }
        }
        return Token(TokenType::NUMBER, number_str);
    }

    Token Lexer::generate_identifier() {
        std::string identifier_str(1, current);
        advance();

        while (current && (current == '_' || current == '-' || std::isalnum(current))) {
            identifier_str += current;
            advance();
        }

        if (std::find(INSTR_NAMES.begin(), INSTR_NAMES.end(), identifier_str) != INSTR_NAMES.end()) {
            return Token(TokenType::INSTR_NAME, identifier_str);
        }
        else if(std::find(REG_NAMES.begin(), REG_NAMES.end(), identifier_str) != REG_NAMES.end()) {
            return Token(TokenType::REG_NAME, identifier_str);   
        }
        else {
            return Token(TokenType::IDENTIFIER, identifier_str);
        }

    }
} // namespace termite