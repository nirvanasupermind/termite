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
            // std::cout << current.value << ' ' << labels[current.value].to_ternary_str() << '\n';
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
            if (current.type == TokenType::IDENTIFIER) {
                // Label
                std::string label = current.value;
                try {
                    Word label_addr = labels.at(label);
                    for (int i = 15; i >= 7; i--) {
                        code[idx].set_bct_trit(i - 8, label_addr.get_bct_trit(i));
                    }
                    idx++;
                    // lshi rd,8;
                    code.push_back(Word());
                    code[idx].set_bct_trit(15, 0b00);
                    code[idx].set_bct_trit(14, 0b10);
                    code[idx].set_bct_trit(13, 0b10);
                    code[idx].set_bct_trit(12, 0b00);
                    for (int i = 11; i >= 9; i--) {
                        code[idx].set_bct_trit(i, rd.get_bct_trit(i - 9));
                    }
                    code[idx].set_bct_trit(8, 0b01);
                    code[idx].set_bct_trit(7, 0b01);
                    code[idx].set_bct_trit(6, 0b01);
                    code[idx].set_bct_trit(5, 0b01);
                    code[idx].set_bct_trit(4, 0b01);
                    code[idx].set_bct_trit(3, 0b01);
                    code[idx].set_bct_trit(2, 0b10);
                    code[idx].set_bct_trit(1, 0b01);
                    code[idx].set_bct_trit(0, 0b00);
                    idx++;
                    code.push_back(Word());
                    // addi rd,rd, (trits 6-1 of label_addr);
                    code[idx].set_bct_trit(15, 0b00);
                    code[idx].set_bct_trit(14, 0b00);
                    code[idx].set_bct_trit(13, 0b10);
                    code[idx].set_bct_trit(12, 0b00);
                    for (int i = 11; i >= 9; i--) {
                        code[idx].set_bct_trit(i, rd.get_bct_trit(i - 9));
                    }
                    for (int i = 8; i >= 6; i--) {
                        code[idx].set_bct_trit(i, rd.get_bct_trit(i - 6));
                    }

                    for (int i = 6; i >= 1; i--) {
                        code[idx].set_bct_trit(i - 1, label_addr.get_bct_trit(i));
                    }

                    idx++;
                    // lshi rd,1;
                    code.push_back(Word());
                    code[idx].set_bct_trit(15, 0b00);
                    code[idx].set_bct_trit(14, 0b10);
                    code[idx].set_bct_trit(13, 0b10);
                    code[idx].set_bct_trit(12, 0b00);

                    for (int i = 11; i >= 9; i--) {
                        code[idx].set_bct_trit(i, rd.get_bct_trit(i - 9));
                    }
                    code[idx].set_bct_trit(8, 0b01);
                    code[idx].set_bct_trit(7, 0b01);
                    code[idx].set_bct_trit(6, 0b01);
                    code[idx].set_bct_trit(5, 0b01);
                    code[idx].set_bct_trit(4, 0b01);
                    code[idx].set_bct_trit(3, 0b01);
                    code[idx].set_bct_trit(2, 0b01);
                    code[idx].set_bct_trit(1, 0b01);
                    code[idx].set_bct_trit(0, 0b10);  
                    idx++; 
                    // addi rd,rd, (trit 0 of label_addr);
                    code.push_back(Word());
                    code[idx].set_bct_trit(15, 0b00);
                    code[idx].set_bct_trit(14, 0b00);
                    code[idx].set_bct_trit(13, 0b10);
                    code[idx].set_bct_trit(12, 0b00);
                    for (int i = 11; i >= 9; i--) {
                        code[idx].set_bct_trit(i, rd.get_bct_trit(i - 9));
                    }
                    for (int i = 8; i >= 6; i--) {
                        code[idx].set_bct_trit(i, rd.get_bct_trit(i - 6));
                    }
                    code[idx].set_bct_trit(5, 0b01);      
                    code[idx].set_bct_trit(4, 0b01);
                    code[idx].set_bct_trit(3, 0b01);
                    code[idx].set_bct_trit(2, 0b01);
                    code[idx].set_bct_trit(1, 0b01);
                    code[idx].set_bct_trit(0, label_addr.get_bct_trit(0));
                }
                catch (const std::exception& e) {
                    throw std::string("Error: undefined label '" + label + "'");
                }
            }
            else {
                // Normal number immediate
                if (current.type != TokenType::NUMBER) {
                    error();
                }
                Word imm = Word::from_int32(std::stoi(current.value));
                for (int i = 8; i >= 0; i--) {
                    code[idx].set_bct_trit(i, imm.get_bct_trit(i));
                }
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
            Word imm = Word::from_int32(std::stoi(current.value));
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
            Word imm = Word::from_int32(std::stoi(current.value));
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
            Word imm = Word::from_int32(std::stoi(current.value));
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
            Word imm = Word::from_int32(std::stoi(current.value));
            for (int i = 8; i >= 0; i--) {
                code[idx].set_bct_trit(i, imm.get_bct_trit(i - 6));
            }
        }
        else if (current.value == "jmp") {
            code[idx].set_bct_trit(15, 0b01);
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
            code[idx].set_bct_trit(i, rt.get_bct_trit(i));
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
        Word imm = Word::from_int32(std::stoi(current.value.substr(1)));
        for (int i = 5; i >= 0; i--) {
            code[idx].set_bct_trit(i, imm.get_bct_trit(i));
        }
    }

} // namespace termite