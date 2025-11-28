
#include "lexer.h"
#include "token.h"
#include <cctype>
#include <iostream>
#include <algorithm>

namespace termite {

    Lexer::Lexer()
        : text(""), line(1), pos(0), current(0) {
    }

    Lexer::Lexer(const std::string& text)
        : text(text), line(1), pos(0), current(0) {
        if (!this->text.empty()) {
            current = this->text[0];
        } else {
            current = 0; // EOF
        }
    }

    void Lexer::advance() {
        if (current == '\n') {
            ++line;
        }

        ++pos;
        if (pos < static_cast<int>(text.size())) {
            current = text[pos];
        } else {
            current = 0; // EOF
        }
    }

    Token Lexer::generate_identifier() {
        std::string ident;

        // current already holds the first character
        while (current &&
               (std::isalnum(static_cast<unsigned char>(current)) ||
                current == '_' || current == '-')) {
            ident += current;
            advance();
        }

        // classify identifier
        if (std::find(INSTR_NAMES.begin(), INSTR_NAMES.end(), ident) != INSTR_NAMES.end()) {
            return Token(line, TokenType::INSTR_NAME, ident);
        }
        if (std::find(REG_NAMES.begin(), REG_NAMES.end(), ident) != REG_NAMES.end()) {
            return Token(line, TokenType::REG_NAME, ident);
        }
        return Token(line, TokenType::IDENTIFIER, ident);
    }

    Token Lexer::generate_number() {
        std::string number_str;

        // optional leading '.' or '-'
        if (current == '.' || current == '-') {
            number_str += current;
            advance();
        }

        if (current == '0') {
            number_str += current;
            advance();

            if (current == 't') {
                number_str += current;
                advance();

                while (current &&
                       (current == 'A' || current == 'a' ||
                        current == '0' || current == '1')) {
                    number_str += current;
                    advance();
                }
            }
            else if (current == 'n') {
                number_str += current;
                advance();

                while (current &&
                       (current == 'A' || current == 'a' ||
                        current == 'B' || current == 'b' ||
                        current == 'C' || current == 'c' ||
                        current == 'D' || current == 'd' ||
                        current == '0' || current == '1' ||
                        current == '2' || current == '3' ||
                        current == '4')) {
                    number_str += current;
                    advance();
                }
            }
            else {
                // plain 0, or 0 followed by more digits
                while (current && std::isdigit(static_cast<unsigned char>(current))) {
                    number_str += current;
                    advance();
                }
            }
        }
        else {
            // decimal integer (after optional sign/dot)
            while (current && std::isdigit(static_cast<unsigned char>(current))) {
                number_str += current;
                advance();
            }
        }

        std::cout << "dbg120 " << number_str << '\n';
        return Token(line, TokenType::NUMBER, number_str);
    }

    std::vector<Token> Lexer::generate_tokens() {
        std::vector<Token> tokens;

        while (current) {
            if (current == ' ' || current == '\r' || current == '\t') {
                advance();
            }
            else if (current == '.' || current == '-' ||
                     std::isdigit(static_cast<unsigned char>(current))) {
                tokens.push_back(generate_number());
            }
            else if (current == ';') {
                // comment: consume until newline
                while (current && current != '\n') {
                    advance();
                }
                if (current == '\n') {
                    tokens.push_back(Token(line, TokenType::NEWLINE, "\n"));
                    advance();
                }
            }
            else if (current == '_' ||
                     std::isalpha(static_cast<unsigned char>(current))) {
                tokens.push_back(generate_identifier());
            }
            else if (current == ':') {
                tokens.push_back(Token(line, TokenType::COLON, ":"));
                advance();
            }
            else if (current == ',') {
                tokens.push_back(Token(line, TokenType::COMMA, ","));
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
            else if (current == '+') {
                tokens.push_back(Token(line, TokenType::PLUS, "+"));
                advance();
            }
            else if (current == '$') {
                tokens.push_back(Token(line, TokenType::DOLLAR, "$"));
                advance();
            }
            else if (current == '%') {
                tokens.push_back(Token(line, TokenType::PERCENT, "%"));
                advance();
            }
            else if (current == '\n') {
                tokens.push_back(Token(line, TokenType::NEWLINE, "\n"));
                advance();
            }
            else {
                std::string msg = "line " + std::to_string(line) +
                                  ": error: illegal character '";
                msg.push_back(current);
                msg.push_back('\'');
                throw msg;
            }
        }

        // Assembler::advance() synthesizes EOF tokens, so no explicit EOF here.
        return tokens;
    }

} // namespace termite


// #include <string>
// #include <iostream>
// #include "token.h"
// #include "lexer.h"

// namespace termite {
//     Lexer::Lexer(const std::string& text)
//         : text(text), pos(0), line(1), current(0) {
//         advance();
//     }

//     void Lexer::advance() {
//     if (pos < text.length() && text[pos] == '\n') {
//         line++;
//     }
//     if (++pos < text.length()) {
//         current = text[pos];
//     } else {
//         current = 0;
//     }
// }

//     // void Lexer::advance() {
//     //     if(text[pos] == '\n') {
//     //         line++;
//     //     }

//     //     if (pos < text.length()) {
//     //         current = text.at(pos++);
//     //     }
//     //     else {
//     //         current = 0;
//     //     }
//     // }

//     std::vector<Token> Lexer::generate_tokens() {
//         std::vector<Token> tokens;

//         while (current) {
//             if (current == ' ' || current == '\r' || current == '\t') {
//                 advance();
//             }
//             else if (current == '.' || current == '-' || std::isdigit(current)) {
//                 tokens.push_back(generate_number());
//             }
//             else if (current == ';') {
//                 while(current != '\n') {
//                     advance();
//                 }
//                 tokens.push_back(Token(line, TokenType::NEWLINE, "\n"));
//                 advance();
//             }
//             else if (current == '_' || std::isalpha(current)) {
//                 tokens.push_back(generate_identifier());
//             }
//             else if (current == ':') {
//                 tokens.push_back(Token(line, TokenType::COLON, ":"));
//                 advance();
//             }
//             else if (current == ',') {
//                 tokens.push_back(Token(line, TokenType::COMMA, ","));
//                 advance();
//             }
//             else if (current == '(') {
//                 tokens.push_back(Token(line, TokenType::LPAREN, "("));
//                 advance();
//             }
//             else if (current == ')') {
//                 tokens.push_back(Token(line, TokenType::RPAREN, ")"));
//                 advance();
//             }
//             else if (current == '+') {
//                 tokens.push_back(Token(line, TokenType::PLUS, "+"));
//                 advance();
//             }
//             else if (current == '$') {
//                 tokens.push_back(Token(line, TokenType::DOLLAR, "$"));
//                 advance();
//             }
//             else if (current == '%') {
//                 tokens.push_back(Token(line, TokenType::PERCENT, "%"));
//                 advance();
//             }
//             else if (current == '\n') {
//                 tokens.push_back(Token(line, TokenType::NEWLINE, "\n"));
//                 advance();
//             }
//             else {
//                 throw std::string("line " + std::to_string(line) + ": " + "error: illegal character '") + current + "'";
//                 break;
//             }
//         }

//         // tokens.push_back(Token(TokenType::EOF_, ""));

//         return tokens;
//     }


//     Token Lexer::generate_number() {
//         std::string number_str(1, current);
//         if (current == '0') {
//             advance();

//             if(current == 't') {
//                 number_str += current;
//                 advance();
                        
//                 while (current && (current == 'A' || current == 'a' || current == '0' || current == '1')) {
//                     number_str += current;
//                     advance();
//                 }
//             } else if(current == 'n') {
//                 number_str += current;
//                 advance();
//                 while (current && (current == 'A' || current == 'a'  || current == 'B' || current == 'b'
//                     || current == 'C' || current == 'c' || current == 'D' || current == 'd'
//                     || current == '0' || current == '1' || current == '2' || current == '3' || current == '4')) {
//                     number_str += current;
//                     advance();
//                 }
//             }
//         }
//         else {
//             advance();
//             while (current && std::isdigit(current)) {
//                 number_str += current;
//                 advance();
//             }
//         }
//         std::cout << "dbg120 " << number_str << '\n';
//         return Token(line, TokenType::NUMBER, number_str);
//     }

//     Token Lexer::generate_identifier() {
//     std::string ident;

//     // DO NOT advance() here. current already holds the first character.

//     while (current &&
//            (std::isalnum(static_cast<unsigned char>(current)) ||
//             current == '_' || current == '-')) {
//         ident += current;
//         advance();  // move to next character
//     }

//     // classify the identifier
//     if (std::find(INSTR_NAMES.begin(), INSTR_NAMES.end(), ident) != INSTR_NAMES.end()) {
//         return Token(line, TokenType::INSTR_NAME, ident);
//     }
//     if (std::find(REG_NAMES.begin(), REG_NAMES.end(), ident) != REG_NAMES.end()) {
//         return Token(line, TokenType::REG_NAME, ident);
//     }
//     return Token(line, TokenType::IDENTIFIER, ident);
// }

//     // Token Lexer::generate_identifier() {
//     //     std::string identifier_str(1, current);
//     //     advance();

//     //     while (current && (current == '_' || current == '-' || std::isalnum(current))) {
//     //         identifier_str += current;
//     //         advance();
//     //     }

//     //     if (std::find(INSTR_NAMES.begin(), INSTR_NAMES.end(), identifier_str) != INSTR_NAMES.end()) {
//     //         return Token(line, TokenType::INSTR_NAME, identifier_str);
//     //     }
//     //     else if(std::find(REG_NAMES.begin(), REG_NAMES.end(), identifier_str) != REG_NAMES.end()) {
//     //         return Token(line, TokenType::REG_NAME, identifier_str);   
//     //     }
//     //     else {
//     //         return Token(line, TokenType::IDENTIFIER, identifier_str);
//     //     }

//     // }
// } // namespace termite