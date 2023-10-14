#include <iostream>
#include <string>
#include "token.h"
#include "assembler.h"
#include "../core/word.h"

namespace termite {
    Assembler::Assembler(const std::vector<Token>& tokens)
        : tokens(tokens), pos(0), current(Token(TokenType::EOF_, "")) {
        advance();
    }

    void Assembler::error() const {
        throw std::string("Error: invalid syntax near '" + current.value + "'");
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
        while (current.type != TokenType::EOF_) {
            assemble_instr();
            advance();
            if (current.type != TokenType::SEMICOLON) {
                error();
            }
            advance();
        }
    }


    void Assembler::assemble_instr() {
        if (current.type != TokenType::KEYWORD) {
            error();
        }


        int idx = code.size();
        code.push_back(Word());
        if (current.value == "mov") {
            code[idx].set_bct_trit(12, 0b00);
            code[idx].set_bct_trit(13, 0b00);
            code[idx].set_bct_trit(14, 0b00);
            code[idx].set_bct_trit(15, 0b00);
            advance();
            if (current.type != TokenType::REGISTER) {
                error();
            }
            Word rd = Word::from_int32(std::stoi(current.value.substr(1)));
            for (int i = 9; i <= 11; i++) {
                code[idx].set_bct_trit(i, rd.get_bct_trit(i - 9));
            }
            advance();
            if (current.type != TokenType::COMMA) {
                error();
            }
            advance();  
            if (current.type != TokenType::REGISTER) {
                error();
            }
            Word rs = Word::from_int32(std::stoi(current.value.substr(1)));
            for (int i = 6; i <= 8; i++) {
                code[idx].set_bct_trit(i, rs.get_bct_trit(i - 6));
            }
        }
        else if (current.value == "movi") {
            code[idx].set_bct_trit(12, 0b01);
            code[idx].set_bct_trit(13, 0b00);
            code[idx].set_bct_trit(14, 0b00);
            code[idx].set_bct_trit(15, 0b00);
            advance();
            if (current.type != TokenType::REGISTER) {
                error();
            }
            Word rd = Word::from_int32(std::stoi(current.value.substr(1))) + Word::from_int32(13);
            for (int i = 9; i <= 11; i++) {
                code[idx].set_bct_trit(i, rd.get_bct_trit(i - 9));
            }
            advance();
            if (current.type != TokenType::COMMA) {
                error();
            }
            advance();
            if (current.type != TokenType::NUMBER) {
                error();
            }
            Word imm = Word::from_int32(std::stoi(current.value));
            for (int i = 0; i <= 8; i++) {
                code[idx].set_bct_trit(i, imm.get_bct_trit(i));
            }
        }
    }


} // namespace termite