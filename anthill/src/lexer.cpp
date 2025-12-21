#include <string>
#include <iostream>
#include "token.h"
#include "lexer.h"
#include "error.h"

namespace anthill {
    Lexer::Lexer(const std::string& file, const std::string& text)
        : file(file), text(text), line(1), pos(0), current(0) {
        advance();
    }

    void Lexer::advance() {
        if (pos < text.length()) {
            current = text.at(pos++);
        }
        else {
            current = 0;
        }
        if (current == '\n') {
            line++;
        }
    }

    std::vector<Token> Lexer::generate_tokens() {
        std::vector<Token> tokens;

        while (current) {
            if (std::isspace(current)) {
                advance();
            }
            else if (current == '*') {
                int old_line = line;
                advance();
                if (current == '=') {
                    tokens.push_back(Token(old_line, TokenType::ASMUL, "*="));
                    advance();
                }
                else {
                    tokens.push_back(Token(old_line, TokenType::STAR, "*"));
                }
            }
            else if (current == '.' || std::isdigit(current)) {
                tokens.push_back(generate_number());
            }
            else if (current == '*') {
                int old_line = line;
                advance();
                if (current == '=') {
                    tokens.push_back(Token(old_line, TokenType::ASMUL, "*="));
                    advance();
                }
                else {
                    tokens.push_back(Token(old_line, TokenType::STAR, "*"));
                }
            }
            else if (current == '/') {
                int old_line = line;
                advance();
                if (current == '=') {
                    tokens.push_back(Token(old_line, TokenType::ASDIV, "/="));
                    advance();
                }
                else {
                    tokens.push_back(Token(old_line, TokenType::SLASH, "/"));
                }
            }
            else if (current == '%') {
                int old_line = line;
                advance();
                if (current == '=') {
                    tokens.push_back(Token(old_line, TokenType::ASMOD, "%="));
                    advance();
                }
                else {
                    tokens.push_back(Token(old_line, TokenType::MOD, "%"));
                }
            }
            else if (current == '+') {
                int old_line = line;
                advance();
                if (current == '+') {
                    tokens.push_back(Token(old_line, TokenType::INCR, "++"));
                    advance();
                }
                else if (current == '=') {
                    tokens.push_back(Token(old_line, TokenType::ASPLUS, "+="));
                    advance();
                }
                else {
                    tokens.push_back(Token(old_line, TokenType::PLUS, "+"));
                }
            }
            else if (current == '-') {
                int old_line = line;
                advance();
                if (current == '-') {
                    tokens.push_back(Token(old_line, TokenType::DECR, "--"));
                    advance();
                }
                else if (current == '=') {
                    tokens.push_back(Token(old_line, TokenType::ASMINUS, "-="));
                    advance();
                }
                else {
                    tokens.push_back(Token(old_line, TokenType::MINUS, "-"));
                }
            }
            else if (current == '<') {
                int old_line = line;
                advance();
                if (current == '<') {
                    tokens.push_back(Token(old_line, TokenType::LSHIFT, "<<"));
                    advance();
                }
                else if (current == '=') {
                    tokens.push_back(Token(old_line, TokenType::LTEQ, "<="));
                    advance();
                }
                else {
                    tokens.push_back(Token(old_line, TokenType::LESS, "<"));
                }
            }
            else if (current == '>') {
                int old_line = line;
                advance();
                if (current == '>') {
                    tokens.push_back(Token(old_line, TokenType::RSHIFT, ">>"));
                    advance();
                }
                else if (current == '=') {
                    tokens.push_back(Token(old_line, TokenType::GTEQ, ">="));
                    advance();
                }
                else {
                    tokens.push_back(Token(old_line, TokenType::GREATER, ">"));
                }
            }
            else if (current == '=') {
                int old_line = line;
                advance();
                if (current == '=') {
                    tokens.push_back(Token(old_line, TokenType::EQUAL, "=="));
                    advance();
                }
                else {
                    tokens.push_back(Token(old_line, TokenType::ASSIGN, "="));
                }
            }
            else if (current == '!') {
                int old_line = line;
                advance();
                if (current == '=') {
                    tokens.push_back(Token(old_line, TokenType::NOTEQ, "!="));
                    advance();
                }
                else {
                    tokens.push_back(Token(old_line, TokenType::NOT, "!"));
                }
            }
            else if (current == '&') {
                int old_line = line;
                advance();
                if (current == '&') {
                    tokens.push_back(Token(old_line, TokenType::LOGAND, "&&"));
                    advance();
                }
                else if (current == '=') {
                    tokens.push_back(Token(old_line, TokenType::ASAND, "&="));
                    advance();
                }
                else {
                    tokens.push_back(Token(old_line, TokenType::AMPER, "&"));
                }
            }
            else if (current == '^') {
                int old_line = line;
                advance();
                if (current == '=') {
                    tokens.push_back(Token(old_line, TokenType::ASXOR, "^="));
                    advance();
                }
                else {
                    tokens.push_back(Token(old_line, TokenType::CARET, "^"));
                }
            }
            else if (current == '|') {
                int old_line = line;
                advance();
                if (current == '|') {
                    tokens.push_back(Token(old_line, TokenType::LOGOR, "||"));
                    advance();
                }
                else if (current == '=') {
                    tokens.push_back(Token(old_line, TokenType::ASOR, "|="));
                    advance();
                }
                else {
                    tokens.push_back(Token(old_line, TokenType::PIPE, "|"));
                }
            }
            else if (current == ',') {
                tokens.push_back(Token(line, TokenType::COMMA, ","));
                advance();
            }
            else if (current == ':') {
                tokens.push_back(Token(line, TokenType::COLON, ":"));
                advance();
            }
            else if (current == ';') {
                tokens.push_back(Token(line, TokenType::SEMI, ";"));
                advance();
            }
            else if (current == '(') {
                tokens.push_back(Token(line, TokenType::LPAREN, "("));
                advance();
            }
            else if (current == ')') {
                tokens.push_back(Token(line, TokenType::RPAREN, ")"));
                advance();
            }
            else if (current == '[') {
                tokens.push_back(Token(line, TokenType::LBRACK, "["));
                advance();
            }
            else if (current == ']') {
                tokens.push_back(Token(line, TokenType::RBRACK, "]"));
                advance();
            }
            else if (current == '{') {
                tokens.push_back(Token(line, TokenType::LBRACE, "{"));
                advance();
            }
            else if (current == '}') {
                tokens.push_back(Token(line, TokenType::RBRACE, "}"));
                advance();
            }
            else if (current == '#') {
                advance();
                Token directive = generate_identifier();
                if(directive.type == TokenType::DEFINE) {
                    advance();
                    Token macro_name = generate_identifier();
                    std::string macro_code = "";
                    while(current != '\n') {
                        macro_code += current;
                        advance();
                    }
                    Lexer lexer2("<macro '" + macro_name.val + "'>", macro_code);
                    std::vector<Token> tokens2 = lexer2.generate_tokens();
                    macros[macro_name.val] = tokens2;
                } else if(directive.type == TokenType::INCLUDE) {
                    tokens.push_back(directive);
                    advance();
                } else {
                    error(file, line, std::string("the only accepted preprocessor directives are define and include, got '") + current + "'");
                }
            }
            else if (current == '_' || std::isalpha(current)) {
                Token ident = generate_identifier();
                if(macros.count(ident.val)) {
                    std::vector<Token> tokens2 = macros[ident.val];
                    for(int i = 0; i < tokens2.size() - 1; i++) {
                        tokens.push_back(tokens2[i]);
                    }
                } else {
                tokens.push_back(ident);
                }
            }
            else if (isdigit(current)) {
                tokens.push_back(generate_number());
                advance();
            } 
            else if (current == '\'') {
                advance();
                char ch = generate_ch();
                advance();
                if(current != '\'') {
                    error(file, line, std::string("expected closing apostrophe in character literal, got '") + current + "'");
                }
                tokens.push_back(Token(line, TokenType::CHARLIT, std::string(1, ch)));
                advance();        
            }
            else if (current == '\"') {
                tokens.push_back(generate_str());
                advance();
            }
            else {
                error(file, line, std::string("illegal character '") + current + "'");
                advance();
            }
        }
        tokens.push_back(Token(line, TokenType::XEOF, "<eof>"));


        return tokens;
    }

    Token Lexer::generate_identifier() {
        std::string identifier_str(1, current);
        advance();

        while (current && (current == '_' || std::isalnum(current))) {
            identifier_str += current;
            advance();
        }

        TokenType type = TokenType::IDENT;
        if (identifier_str == "break") {
            type = TokenType::BREAK;
        }
        else if (identifier_str == "case") {
            type = TokenType::CASE;
        }
        else if (identifier_str == "char") {
            type = TokenType::CHAR;
        }
        else if (identifier_str == "continue") {
            type = TokenType::CONTINUE;
        }
        else if (identifier_str == "default") {
            type = TokenType::DEFAULT;
        }
        else if (identifier_str == "do") {
            type = TokenType::DO;
        }
        else if (identifier_str == "else") {
            type = TokenType::ELSE;
        }
        else if (identifier_str == "enum") {
            type = TokenType::ENUM;
        }
        else if (identifier_str == "extern") {
            type = TokenType::EXTERN;
        }
        else if (identifier_str == "for") {
            type = TokenType::FOR;
        }
        else if (identifier_str == "if") {
            type = TokenType::IF;
        }
        else if (identifier_str == "return") {
            type = TokenType::RETURN;
        }
        else if (identifier_str == "sizeof") {
            type = TokenType::SIZEOF;
        }
        else if (identifier_str == "static") {
            type = TokenType::STATIC;
        }
        else if (identifier_str == "switch") {
            type = TokenType::SWITCH;
        }
        else if (identifier_str == "void") {
            type = TokenType::VOID;
        }
        else if (identifier_str == "while") {
            type = TokenType::WHILE;
        }
        else if (identifier_str == "int") {
            type = TokenType::INT;
        }
        else if (identifier_str == "char") {
            type = TokenType::CHAR;
        }
        else if (identifier_str == "define") {
            type = TokenType::DEFINE;
        }
        else if (identifier_str == "include") {
            type = TokenType::INCLUDE;
        }
        return Token(line, type, identifier_str);
    }

    Token Lexer::generate_number() {
        std::string number_str(1, current);
        if (current == '0') {
            advance();

            if (current == 't') {
                number_str += current;
                advance();

                while (current && (current == 'A' || current == 'a' || current == '0' | current == '1')) {
                    number_str += current;
                    advance();
                }
            }
            else if (current == 'n') {
                number_str += current;
                advance();
                while (current && (current == 'A' || current == 'a' || current == 'B' || current == 'b'
                    || current == 'C' || current == 'c' || current == 'D' || current == 'd'
                    || current == '0' | current == '1' || current == '2' || current == '3' || current == '4')) {
                    number_str += current;
                    advance();
                }
            }
        }
        else {
            advance();
            int decimal_point_count = 0;
            while (current && (std::isdigit(current) || current == '.')) {
                if(current == '.') {
                    decimal_point_count++;
                    if(decimal_point_count > 1) {
                        error(file, line, std::string("multiple decimal points in a numeric literal"));
                    }
                }
                number_str += current;
                advance();
            }
        }
        return Token(line, TokenType::NUMLIT, number_str);
    }

    char Lexer::generate_ch() {
        if ('\\' == current) {
            advance();
        switch (current) {
        case 'a': return '\a';
        case 'b': return '\b';
        case 'f': return '\f';
        case 'n': return '\n';
        case 'r': return '\r';
        case 't': return '\t';
        case 'v': return '\v';
        case '\\': return '\\';
        case '"': return '"' | 256;
        case '\'': return '\'';
        }
    } else {
        return current;
        }
    }

    Token Lexer::generate_str() {
        advance();
        std::string str;
        while (current != '"') {
            char x = generate_ch();     
            str += x;
            advance();
        }
        return Token(line, TokenType::STRLIT, str);
    }
}