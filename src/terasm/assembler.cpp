#include <string>
#include "token.h"
#include "assembler.h"

namespace termite {
    Assembler::Assembler(const std::vector<Token> &tokens)
        : tokens(tokens), pos(0), current(Token(TokenType::EOF_, "")) {
        advance();
    }

    void Assembler::error() const {
        throw std::string("Invalid syntax");
    }

    void Assembler::advance() {
        if (pos < tokens.size()) {
            current = tokens.at(pos++);
        }
        else {
            current = Token(TokenType::EOF_, "");
        }
    }

    void Assembler::assemble_program() {
        while(current.type != TokenType::EOF_) {
            assemble_instr();
            advance();
            if(current.type != TokenType::SEMICOLON) {
                error();
            }
            advance();
        }
    }

    void Assembler::assemble_instr() {
        if(current.type != TokenType::KEYWORD) {
            error();
        }

        int idx = code.size();
        code.push_back(0b00);
        code.push_back(0b00);
        code.push_back(0b00);
        code.push_back(0b00);

        if(current.value == "mov") {
            code[idx + 3] = 0b00000000;
            advance();
            if(current.type != TokenType::REGISTER) {
                error();
            }
            int rd_num = std::stoi(current.value.substr(1));
            advance();
            if(current.type != TokenType::REGISTER) {
                error();
            }            
            int rs_num = std::stoi(current.value.substr(1));
            
        }
    }


} // namespace termite
