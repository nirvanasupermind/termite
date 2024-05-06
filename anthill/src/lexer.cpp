#include <iostream>
#include <string>
#include <vector>
#include "token.h"
#include "lexer.h"

namespace anthill {
    Lexer::Lexer(const std::string& filename, const std::string& text)
        : filename(filename), text(text), line(1), pos(0), current(0) {
        advance();
    }

    void Lexer::advance() {
        if (pos < text.length()) {
            current = text.at(pos++);
        }
        else {
            current = 0;
        }
        
        if(current == '\n') {
            line++;
        }
    }

    std::vector<Token> Lexer::generate_tokens() {
        std::vector<Token> tokens;

        while (current) {
            if (std::isspace(current)) {
                advance();
            }
            else if (std::isdigit(current)) {
                tokens.push_back(generate_int());
            }
            else if (current == '\'') {
                int old_line = line;
                advance();
                char ch = current;
                advance();
                if (current != '\'') {
                    throw std::string(filename + ':' + std::to_string(line) + ": illegal character '" + current + "'");
                }
                tokens.push_back(Token(old_line, TokenType::CHAR, std::string(1, ch)));
                advance();
            }
            else if (current == '"') {
                tokens.push_back(generate_string());
            }
            else if (current == '_' || std::isalpha(current)) {
                tokens.push_back(generate_identifier());
            }
            else if (current == '+') {
                tokens.push_back(Token(line, TokenType::PLUS, "+"));
                advance();
            }
            else if (current == '-') {
                tokens.push_back(Token(line, TokenType::MINUS, "-"));
                advance();
            }
            else if (current == '*') {
                tokens.push_back(Token(line, TokenType::MUL, "*"));
                advance();
            }
            else if (current == '/') {
                tokens.push_back(Token(line, TokenType::DIV, "/"));
                advance();
            }
            else if (current == '%') {
                tokens.push_back(Token(line, TokenType::MOD, "%"));
                advance();
            }
            else if (current == '&') {
                tokens.push_back(Token(line, TokenType::AND, "&"));
                advance();
            }
            else if (current == '|') {
                tokens.push_back(Token(line, TokenType::OR, "|"));
                advance();
            }
            else if (current == '^') {
                tokens.push_back(Token(line, TokenType::XOR, "^"));
                advance();
            }
            else if (current == '=') {
                int old_line = line;
                advance();
                if(current == '=') {
                    tokens.push_back(Token(old_line, TokenType::EE, "=="));
                    advance();
                } else {
                    tokens.push_back(Token(old_line, TokenType::EQ, "="));
                }
            }
            else if (current == '!') {
                advance();
                if(current == '=') {
                    tokens.push_back(Token(line, TokenType::NE, "=="));
                } else {
                    throw std::string(filename + ':' + std::to_string(line) + ": illegal character '" + current + "'");
                }
            }
            else if (current == '<') {
                int old_line = line;
                advance();
                if(current == '=') {
                    tokens.push_back(Token(old_line, TokenType::LE, "<="));
                    advance();
                } else {
                    tokens.push_back(Token(old_line, TokenType::LT, "<"));
                }
            }
            else if (current == '>') {
                int old_line = line;
                advance();
                if(current == '=') {
                    tokens.push_back(Token(old_line, TokenType::GE, ">="));
                    advance();
                } else {
                    tokens.push_back(Token(old_line, TokenType::GT, ">"));
                }
            }
            else if (current == '(') {
                tokens.push_back(Token(line, TokenType::LPAREN, "("));
                advance();
            }
            else if (current == ')') {
                tokens.push_back(Token(line, TokenType::RPAREN, ")"));
                advance();
            }
            else if (current == '{') {
                tokens.push_back(Token(line, TokenType::LCURLY, "{"));
                advance();
            }
            else if (current == '}') {
                tokens.push_back(Token(line, TokenType::RCURLY, "}"));
                advance();
            }
            else if (current == ',') {
                tokens.push_back(Token(line, TokenType::COMMA, ","));
                advance();
            }
            else if (current == ';') {
                tokens.push_back(Token(line, TokenType::SEMICOLON, ";"));
                advance();
            }
            else {
                throw std::string(filename + ':' + std::to_string(line) + ": illegal character '" + current + "'");
                break;
            }
        }

        tokens.push_back(Token(line, TokenType::EOF_, "<eof>"));

        return tokens;
    }

    Token Lexer::generate_int() {
        std::string int_str(1, current);
        advance();
        if (current == 'r' && int_str == "0") {
            int_str += current;
            advance();
            while (current && (current == 'T' || current == 't' || current == '0' | current == '1')) {
                int_str += current;
                advance();
            }
        } else {
            while (current && std::isdigit(current)) {
                int_str += current;
                advance();
            }
        }

        return Token(line, TokenType::INT, int_str);
    }

    Token Lexer::generate_string() {
        int old_line = line;
        std::string str(1, current);
        advance();
        while (current && current != '"') {
            str += current;
            advance();
        }
        str += current;
        advance();
        return Token(old_line, TokenType::STRING, str);
    }

    Token Lexer::generate_identifier() {
        std::string identifier_str(1, current);
        advance();

        while (current && (current == '_' || std::isalnum(current))) {
            identifier_str += current;
            advance();
        }

        if (std::find(KEYWORDS.begin(), KEYWORDS.end(), identifier_str) != KEYWORDS.end()) {
            return Token(line, TokenType::KEYWORD, identifier_str);
        }
        else {
            return Token(line, TokenType::IDENTIFIER, identifier_str);
        }
    }
};