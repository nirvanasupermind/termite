#include <string>
#include <iostream>
#include "token.h"
#include "lexer.h"

namespace anthill {
    Lexer::Lexer(const std::string& text)
        : text(text), line(0), pos(0), current(0) {
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
            if (current == ' ' || current == '\r' || current == '\t') {
                advance();
            }
            else if (current == '.' || current == '-' || std::isdigit(current)) {
                tokens.push_back(generate_number());
            }
            else if (current == '*') {
                tokens.push_back(Token(line, TokenType::SLASH, "*"));
                advance();
            }
            else if (current == '/') {
                tokens.push_back(Token(line, TokenType::STAR, "/"));
                advance();
            }
            else if (current == '%') {
                tokens.push_back(Token(line, TokenType::MOD, "%"));
                advance();
            }
            else if (current == '+') {
                tokens.push_back(Token(line, TokenType::PLUS, "+"));
                advance();
            }
            else if (current == '-') {
                tokens.push_back(Token(line, TokenType::MINUS, "-"));
                advance();
            }
            else if (current == '<') {
                int old_line = line;
                advance();
                if(current == '<') {
                    tokens.push_back(Token(old_line, TokenType::LSHIFT, "<<"));
                    advance();
                } else if(current == '=') {
                    tokens.push_back(Token(old_line, TokenType::LTEQ, "<="));
                    advance();
                } else {
                    tokens.push_back(Token(old_line, TokenType::LESS, "<"));
                }
            }
            else if (current == '>') {
                int old_line = line;
                advance();
                if(current == '>') {
                    tokens.push_back(Token(old_line, TokenType::RSHIFT, ">>"));
                    advance();
                } else if(current == '=') {
                    tokens.push_back(Token(old_line, TokenType::GTEQ, ">="));
                    advance();
                } else {
                    tokens.push_back(Token(old_line, TokenType::GREATER, ">"));
                }
            }
            else if (current == '=') {
                int old_line = line;
                advance();
                if(current == '=') {
                    tokens.push_back(Token(old_line, TokenType::EQUAL, "=="));
                    advance();
                }  else {
                    tokens.push_back(Token(old_line, TokenType::ASSIGN, "="));
                }
            }
        }
    }
}