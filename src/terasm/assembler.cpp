#include <iostream>
#include <string>
#include <vector>
#include <map>
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
            assemble_label_instr();
            advance();
        }
    }

    void Assembler::assemble_label_instr() {
        if (current.type == TokenType::IDENTIFIER) {
            labels[current.value] = Word::from_int32((code.size() << 1) - 21523360);
            advance();
            if (current.type != TokenType::COLON) {
                error();
            }
        }
        else {
            assemble_instr();
        }
    }

    void Assembler::assemble_instr() {
        if (current.type != TokenType::KEYWORD) {
            error();
        }

        int idx = code.size();
        code.push_back(Word());

        if (current.value == "mov") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b00);
            code[idx].set_bct_trit(13, 0b00);
            code[idx].set_bct_trit(12, 0b00);
            advance();
            if (current.type != TokenType::REGISTER) {
                error();
            }
            Word rd = Word::from_int32(std::stoi(current.value.substr(1)));
            for (int i = 11; i >= 9; i--) {
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
            for (int i = 8; i >= 6; i--) {
                code[idx].set_bct_trit(i, rs.get_bct_trit(i - 6));
            }
        }
        else if (current.value == "movi") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b00);
            code[idx].set_bct_trit(13, 0b00);
            code[idx].set_bct_trit(12, 0b01);
            advance();
            if (current.type != TokenType::REGISTER) {
                error();
            }
            Word rd = Word::from_int32(std::stoi(current.value.substr(1)));
            for (int i = 11; i >= 9; i--) {
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
            Word imm;
            if (current.value.at(0) == '%') {
                imm = Word::from_ternary_str(current.value.substr(1));
            }
            else {
                imm = Word::from_int32(std::stoi(current.value));
            }
            for (int i = 8; i >= 0; i--) {
                code[idx].set_bct_trit(i, imm.get_bct_trit(i));
            }
        }
        else if (current.value == "movps") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b00);
            code[idx].set_bct_trit(13, 0b00);
            code[idx].set_bct_trit(12, 0b10);
            advance();
            if (current.type != TokenType::REGISTER) {
                error();
            }
            Word rd = Word::from_int32(std::stoi(current.value.substr(1)));
            for (int i = 11; i >= 9; i--) {
                code[idx].set_bct_trit(i, rd.get_bct_trit(i - 9));
            }
            advance();
        }
        else if (current.value == "ld") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b00);
            code[idx].set_bct_trit(13, 0b01);
            code[idx].set_bct_trit(12, 0b00);
            advance();
            if (current.type != TokenType::REGISTER) {
                error();
            }
            Word rd = Word::from_int32(std::stoi(current.value.substr(1)));
            for (int i = 11; i >= 9; i--) {
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
            for (int i = 8; i >= 6; i--) {
                code[idx].set_bct_trit(i, rs.get_bct_trit(i - 6));
            }
            advance();
            if (current.type != TokenType::COMMA) {
                error();
            }
            advance();
            if (current.type != TokenType::NUMBER) {
                error();
            }
            Word imm;
            if (current.value.at(0) == '%') {
                imm = Word::from_ternary_str(current.value.substr(1));
            }
            else {
                imm = Word::from_int32(std::stoi(current.value));
            }
            for (int i = 5; i >= 0; i--) {
                code[idx].set_bct_trit(i, imm.get_bct_trit(i));
            }
        }
        else if (current.value == "st") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b00);
            code[idx].set_bct_trit(13, 0b01);
            code[idx].set_bct_trit(12, 0b01);
            advance();
            if (current.type != TokenType::REGISTER) {
                error();
            }
            Word rd = Word::from_int32(std::stoi(current.value.substr(1)));
            for (int i = 11; i >= 9; i--) {
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
            for (int i = 8; i >= 6; i--) {
                code[idx].set_bct_trit(i, rs.get_bct_trit(i - 6));
            }
            advance();
            if (current.type != TokenType::COMMA) {
                error();
            }
            advance();
            if (current.type != TokenType::NUMBER) {
                error();
            }
            Word imm;
            if (current.value.at(0) == '%') {
                imm = Word::from_ternary_str(current.value.substr(1));
            }
            else {
                imm = Word::from_int32(std::stoi(current.value));
            }
            for (int i = 5; i >= 0; i--) {
                code[idx].set_bct_trit(i, imm.get_bct_trit(i));
            }
        }
        else if (current.value == "add") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b00);
            code[idx].set_bct_trit(13, 0b01);
            code[idx].set_bct_trit(12, 0b10);
            assemble_rrr_instr(idx);
        }
        else if (current.value == "addi") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b00);
            code[idx].set_bct_trit(13, 0b10);
            code[idx].set_bct_trit(12, 0b00);
            assemble_rri_instr(idx);
        }
        else if (current.value == "addc") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b00);
            code[idx].set_bct_trit(13, 0b10);
            code[idx].set_bct_trit(12, 0b01);
            assemble_rrr_instr(idx);
        }
        else if (current.value == "addci") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b00);
            code[idx].set_bct_trit(13, 0b10);
            code[idx].set_bct_trit(12, 0b10);
            assemble_rri_instr(idx);
        }
        else if (current.value == "sub") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b01);
            code[idx].set_bct_trit(13, 0b00);
            code[idx].set_bct_trit(12, 0b00);
            assemble_rrr_instr(idx);
        }
        else if (current.value == "subi") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b01);
            code[idx].set_bct_trit(13, 0b00);
            code[idx].set_bct_trit(12, 0b01);
            assemble_rri_instr(idx);
        }
        else if (current.value == "subc") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b01);
            code[idx].set_bct_trit(13, 0b00);
            code[idx].set_bct_trit(12, 0b10);
            assemble_rrr_instr(idx);
        }
        else if (current.value == "subci") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b01);
            code[idx].set_bct_trit(13, 0b01);
            code[idx].set_bct_trit(12, 0b00);
            assemble_rri_instr(idx);
        }
        else if (current.value == "mul") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b01);
            code[idx].set_bct_trit(13, 0b01);
            code[idx].set_bct_trit(12, 0b01);
            assemble_rrr_instr(idx);
        }
        else if (current.value == "muli") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b01);
            code[idx].set_bct_trit(13, 0b01);
            code[idx].set_bct_trit(12, 0b10);
            assemble_rri_instr(idx);
        }
        else if (current.value == "not") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b01);
            code[idx].set_bct_trit(13, 0b10);
            code[idx].set_bct_trit(12, 0b00);
            advance();
            if (current.type != TokenType::REGISTER) {
                error();
            }
            Word rd = Word::from_int32(std::stoi(current.value.substr(1)));
            for (int i = 11; i >= 9; i--) {
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
            for (int i = 8; i >= 6; i--) {
                code[idx].set_bct_trit(i, rs.get_bct_trit(i - 6));
            }
        }
        else if (current.value == "noti") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b01);
            code[idx].set_bct_trit(13, 0b10);
            code[idx].set_bct_trit(12, 0b01);
            advance();
            if (current.type != TokenType::REGISTER) {
                error();
            }
            Word rd = Word::from_int32(std::stoi(current.value.substr(1)));
            for (int i = 11; i >= 9; i--) {
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
            Word imm;
            if (current.value.at(0) == '%') {
                imm = Word::from_ternary_str(current.value.substr(1));
            }
            else {
                imm = Word::from_int32(std::stoi(current.value));
            }
            for (int i = 8; i >= 0; i--) {
                code[idx].set_bct_trit(i, imm.get_bct_trit(i));
            }
        }
        else if (current.value == "and") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b01);
            code[idx].set_bct_trit(13, 0b10);
            code[idx].set_bct_trit(12, 0b10);
            assemble_rrr_instr(idx);
        }
        else if (current.value == "andi") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b10);
            code[idx].set_bct_trit(13, 0b00);
            code[idx].set_bct_trit(12, 0b00);
            assemble_rri_instr(idx);
        }
        else if (current.value == "or") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b10);
            code[idx].set_bct_trit(13, 0b00);
            code[idx].set_bct_trit(12, 0b01);
            assemble_rrr_instr(idx);
        }
        else if (current.value == "ori") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b10);
            code[idx].set_bct_trit(13, 0b00);
            code[idx].set_bct_trit(12, 0b10);
            assemble_rri_instr(idx);
        }
        else if (current.value == "xor") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b10);
            code[idx].set_bct_trit(13, 0b01);
            code[idx].set_bct_trit(12, 0b00);
            assemble_rrr_instr(idx);
        }
        else if (current.value == "xori") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b10);
            code[idx].set_bct_trit(13, 0b01);
            code[idx].set_bct_trit(12, 0b01);
            assemble_rri_instr(idx);
        }
        else if (current.value == "lsh") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b10);
            code[idx].set_bct_trit(13, 0b01);
            code[idx].set_bct_trit(12, 0b10);
            assemble_rrr_instr(idx);
        }
        else if (current.value == "lshi") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b10);
            code[idx].set_bct_trit(13, 0b10);
            code[idx].set_bct_trit(12, 0b00);
            assemble_rri_instr(idx);
        }
        else if (current.value == "rsh") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b10);
            code[idx].set_bct_trit(13, 0b10);
            code[idx].set_bct_trit(12, 0b01);
            assemble_rrr_instr(idx);
        }
        else if (current.value == "rshi") {
            code[idx].set_bct_trit(15, 0b00);
            code[idx].set_bct_trit(14, 0b10);
            code[idx].set_bct_trit(13, 0b10);
            code[idx].set_bct_trit(12, 0b10);
            assemble_rri_instr(idx);
        }
        else if (current.value == "cmp") {
            code[idx].set_bct_trit(15, 0b01);
            code[idx].set_bct_trit(14, 0b00);
            code[idx].set_bct_trit(13, 0b00);
            code[idx].set_bct_trit(12, 0b00);
            advance();
            if (current.type != TokenType::REGISTER) {
                error();
            }
            Word rd = Word::from_int32(std::stoi(current.value.substr(1)));
            for (int i = 11; i >= 9; i--) {
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
            for (int i = 8; i >= 6; i--) {
                code[idx].set_bct_trit(i, rs.get_bct_trit(i - 6));
            }
        }
        else if (current.value == "cmpi") {
            code[idx].set_bct_trit(15, 0b01);
            code[idx].set_bct_trit(14, 0b00);
            code[idx].set_bct_trit(13, 0b00);
            code[idx].set_bct_trit(12, 0b01);
            advance();
            if (current.type != TokenType::REGISTER) {
                error();
            }
            Word rd = Word::from_int32(std::stoi(current.value.substr(1)));
            for (int i = 11; i >= 9; i--) {
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
            Word imm;
            if (current.value.at(0) == '%') {
                imm = Word::from_ternary_str(current.value.substr(1));
            }
            else {
                imm = Word::from_int32(std::stoi(current.value));
            }
            for (int i = 8; i >= 0; i--) {
                code[idx].set_bct_trit(i, imm.get_bct_trit(i));
            }
        }
        else if (current.value == "b") {
            code[idx].set_bct_trit(15, 0b01);
            code[idx].set_bct_trit(14, 0b00);
            code[idx].set_bct_trit(13, 0b00);
            code[idx].set_bct_trit(12, 0b10);
            assemble_i_instr(idx);
        }
        else if (current.value == "beq") {
            code[idx].set_bct_trit(15, 0b01);
            code[idx].set_bct_trit(14, 0b00);
            code[idx].set_bct_trit(13, 0b01);
            code[idx].set_bct_trit(12, 0b00);
            assemble_i_instr(idx);
        }
        else if (current.value == "bne") {
            code[idx].set_bct_trit(15, 0b01);
            code[idx].set_bct_trit(14, 0b00);
            code[idx].set_bct_trit(13, 0b01);
            code[idx].set_bct_trit(12, 0b01);
            assemble_i_instr(idx);
        }
        else if (current.value == "blt") {
            code[idx].set_bct_trit(15, 0b01);
            code[idx].set_bct_trit(14, 0b00);
            code[idx].set_bct_trit(13, 0b01);
            code[idx].set_bct_trit(12, 0b10);
            assemble_i_instr(idx);
        }
        else if (current.value == "ble") {
            code[idx].set_bct_trit(15, 0b01);
            code[idx].set_bct_trit(14, 0b00);
            code[idx].set_bct_trit(13, 0b10);
            code[idx].set_bct_trit(12, 0b00);
            assemble_i_instr(idx);
        }
        else if (current.value == "bgt") {
            code[idx].set_bct_trit(15, 0b01);
            code[idx].set_bct_trit(14, 0b00);
            code[idx].set_bct_trit(13, 0b10);
            code[idx].set_bct_trit(12, 0b01);
            assemble_i_instr(idx);
        }
        else if (current.value == "bge") {
            code[idx].set_bct_trit(15, 0b01);
            code[idx].set_bct_trit(14, 0b00);
            code[idx].set_bct_trit(13, 0b10);
            code[idx].set_bct_trit(12, 0b10);
            assemble_i_instr(idx);
        }
        else if (current.value == "push") {
            code[idx].set_bct_trit(15, 0b01);
            code[idx].set_bct_trit(14, 0b01);
            code[idx].set_bct_trit(13, 0b00);
            code[idx].set_bct_trit(12, 0b00);
            assemble_i_instr(idx);
        }
        else if (current.value == "pop") {
            code[idx].set_bct_trit(15, 0b01);
            code[idx].set_bct_trit(14, 0b01);
            code[idx].set_bct_trit(13, 0b00);
            code[idx].set_bct_trit(12, 0b01);
            advance();
            if (current.type != TokenType::REGISTER) {
                error();
            }
            Word rd = Word::from_int32(std::stoi(current.value.substr(1)));
            for (int i = 11; i >= 9; i--) {
                code[idx].set_bct_trit(i, rd.get_bct_trit(i - 9));
            }
            advance();
        }
        else if (current.value == "call") {
            code[idx].set_bct_trit(15, 0b01);
            code[idx].set_bct_trit(14, 0b01);
            code[idx].set_bct_trit(13, 0b00);
            code[idx].set_bct_trit(12, 0b10);
            assemble_i_instr(idx);
        }
        else if (current.value == "ret") {
            code[idx].set_bct_trit(15, 0b01);
            code[idx].set_bct_trit(14, 0b01);
            code[idx].set_bct_trit(13, 0b01);
            code[idx].set_bct_trit(12, 0b00);
        }
        else if (current.value == "sys") {
            code[idx].set_bct_trit(15, 0b01);
            code[idx].set_bct_trit(14, 0b01);
            code[idx].set_bct_trit(13, 0b01);
            code[idx].set_bct_trit(12, 0b01);
            assemble_i_instr(idx);
        }
        else {
            error();
        }
        advance();
        if (current.type != TokenType::SEMICOLON) {
            error();
        }
    }

    void Assembler::assemble_rrr_instr(int idx) {
        advance();
        if (current.type != TokenType::REGISTER) {
            error();
        }
        Word rd = Word::from_int32(std::stoi(current.value.substr(1)));
        for (int i = 11; i >= 9; i--) {
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
        for (int i = 8; i >= 6; i--) {
            code[idx].set_bct_trit(i, rs.get_bct_trit(i - 6));
        }
        advance();
        if (current.type != TokenType::COMMA) {
            error();
        }
        advance();
        if (current.type != TokenType::REGISTER) {
            error();
        }
        Word rt = Word::from_int32(std::stoi(current.value.substr(1)));
        for (int i = 5; i >= 3; i--) {
            code[idx].set_bct_trit(i, rt.get_bct_trit(i - 3));
        }
    }

    void Assembler::assemble_rri_instr(int idx) {
        advance();
        if (current.type != TokenType::REGISTER) {
            error();
        }
        Word rd = Word::from_int32(std::stoi(current.value.substr(1)));
        for (int i = 11; i >= 9; i--) {
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
        for (int i = 8; i >= 6; i--) {
            code[idx].set_bct_trit(i, rs.get_bct_trit(i - 6));
        }
        advance();
        if (current.type != TokenType::COMMA) {
            error();
        }
        advance();
        if (current.type != TokenType::NUMBER) {
            error();
        }
        Word imm;
        if (current.value.at(0) == '%') {
            imm = Word::from_ternary_str(current.value.substr(1));
        } else {
            imm = Word::from_int32(std::stoi(current.value));
        }
        for (int i = 5; i >= 0; i--) {
            code[idx].set_bct_trit(i, imm.get_bct_trit(i));
        }
    }

    void Assembler::assemble_i_instr(int idx) {
        advance();
        if (current.type == TokenType::IDENTIFIER) {
            Word label_addr;
            try {
                label_addr = labels.at(current.value);
            }
            catch (const std::out_of_range& e) {
                throw std::string("Error: undefined label '" + current.value + "'");
            }
            Word relative_addr = label_addr - Word::from_int32(((idx + 1) << 1) - 21523360);
            for (int i = 11; i >= 0; i--) {
                code[idx].set_bct_trit(i, relative_addr.get_bct_trit(i));
            }
        }
        else {
            if (current.type != TokenType::NUMBER) {
                error();
            }
            Word imm;
            if (current.value.at(0) == '%') {
                imm = Word::from_ternary_str(current.value.substr(1));
            }
            else {
                imm = Word::from_int32(std::stoi(current.value));
            }
            for (int i = 11; i >= 0; i--) {
                code[idx].set_bct_trit(i, imm.get_bct_trit(i));
            }
        }
    }

} // namespace termite