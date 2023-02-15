#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <cinttypes>
#include <locale>
#include "token.h"
#include "assembler.h"
#include "../core/trit.h"
#include "../core/tryte.h"

namespace termite {
    Assembler::Assembler(const std::vector<Token>& tokens, const std::string& filename)
        : tokens(tokens), filename(filename), pos(-1) {
        advance();
    }

    void Assembler::advance() {
        current = tokens.at(++pos);
    }

    void Assembler::append_num(int num, int trits) {
        Tryte t = Tryte::from_int(num);

        for (int i = 0; i < trits; i++) {
            machine_code.push_back(t.get_trit(i));
        }
    }

    std::string Assembler::to_lower(std::string s) const {
        for (char& c : s)
            c = tolower(c);
        return s;
    }

    void Assembler::imm() {
        int num;

        if (current.type == TokenType::DEC_LITERAL) {
            num = std::stoi(current.val);
        }
        else if (current.type == TokenType::NON_LITERAL) {
            num = std::stoi(current.val.substr(2), 0, 9);
        } else {
            // std::cout << "dbg " << static_cast<int>(current.type) << '\n';
            throw std::string(filename + ":" + std::to_string(current.line) + ": invalid syntax");
        }
        
        append_num(num, 4);
        advance();
    }

    void Assembler::reg() {
        if (current.type == TokenType::REGISTER) {
            int num = std::stoi(current.val.substr(1));
            append_num(num, 2);
            advance();
        } else {
            throw std::string(filename + ":" + std::to_string(current.line) + ": invalid syntax");
        }
    }

    void Assembler::instruction() {
        if (current.type != TokenType::IDENTIFIER) {
            throw std::string(filename + ":" + std::to_string(current.line) + ": invalid syntax");
        }

        std::string instr_name = to_lower(current.val);

        if (instr_name == "nop") {
            append_num(0, 6);
            advance();
        }
        else if (instr_name == "ldt") {
            append_num(1, 6);
            advance();
            reg();
            if (current.type != TokenType::COMMA) {
                throw std::string(filename + ":" + std::to_string(current.line) + ": invalid syntax");
            }
            advance();
            reg();
            append_num(0, 2);
        }
        else if (instr_name == "ldw") {
            append_num(2, 6);
            advance();
            reg();
            if (current.type != TokenType::COMMA) {
                throw std::string(filename + ":" + std::to_string(current.line) + ": invalid syntax");
            }
            advance();
            reg();
            append_num(0, 2);
        }
        else if (instr_name == "ldi") {
            append_num(3, 6);
            advance();
            reg();
            if (current.type != TokenType::COMMA) {
                throw std::string(filename + ":" + std::to_string(current.line) + ": invalid syntax");
            }
            advance();
            imm();
        }
        else if (instr_name == "ldps") {
            append_num(4, 6);
            advance();
            reg();
            if (current.type != TokenType::COMMA) {
                throw std::string(filename + ":" + std::to_string(current.line) + ": invalid syntax");
            }
            advance();
            imm();
        }
        else if (instr_name == "stt") {
            append_num(5, 6);
            advance();
            reg();
            if (current.type != TokenType::COMMA) {
                throw std::string(filename + ":" + std::to_string(current.line) + ": invalid syntax");
            }
            advance();
            reg();
            append_num(0, 2);
        }
        else if (instr_name == "stw") {
            append_num(6, 6);
            advance();
            reg();
            if (current.type != TokenType::COMMA) {
                throw std::string(filename + ":" + std::to_string(current.line) + ": invalid syntax");
            }
            advance();
            reg();
            append_num(0, 2);
        }
        else if (instr_name == "neg") {
            append_num(7, 6);
            advance();
            reg();
            append_num(0, 4);
        }
        else if (instr_name == "add") {
            append_num(8, 6);
            advance();
            reg();
            if (current.type != TokenType::COMMA) {
                throw std::string(filename + ":" + std::to_string(current.line) + ": invalid syntax");
            }
            advance();
            reg();
            append_num(0, 2);
        }
        else if (instr_name == "addi") {
            append_num(9, 6);
            advance();
            reg();
            if (current.type != TokenType::COMMA) {
                throw std::string(filename + ":" + std::to_string(current.line) + ": invalid syntax");
            }
            advance();
            imm();
        }
        else if (instr_name == "addc") {
            append_num(8, 6);
            advance();
            reg();
            if (current.type != TokenType::COMMA) {
                throw std::string(filename + ":" + std::to_string(current.line) + ": invalid syntax");
            }
            advance();
            reg();
            append_num(0, 2);
        }
        else {
            throw std::string(filename + ":" + std::to_string(current.line) + ": unknown instruction: " + current.val);
        }
    }

    std::vector<Trit> Assembler::generate_machine_code() {
        // std::cout << 144 << '\n';
        instruction();
        return machine_code;
    }
} // namespace termite