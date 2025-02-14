#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <string>
#include <vector>
#include <map>
#include <utility>
#include "token.h"
#include "../core/word.h"

namespace termite {
    const std::map<std::string, int> NUM_OPERANDS {
        {"mov", 2},
        {"push", 1},
        {"pop", 1},
        {"pushf", 0},
        {"popf", 0},
        {"and", 2},
        {"or", 2},
        {"xor", 2},
        {"shl", 2},
        {"shr", 2},
        {"add", 2},
        {"adc", 2},
        {"sub", 2},
        {"mul", 2},
        {"div", 2},
        {"neg", 2},
        {"cmp", 2},
        {"call", 1},
        {"ret", 0},
        {"jmp", 1},
        {"jl", 1},
        {"je", 1},
        {"jg", 1},
        {"jge", 1},
        {"je", 1},
        {"jne", 1},
        {"jc", 1},
        {"jnc", 1},
        {"int", 1}
    };
    
    class Assembler {
    public:
        std::vector<Token> tokens{};
        int pos;
        Token current;
        std::vector<Word> code{};
        std::map<std::string, Word> labels{};
        Assembler(const std::vector<Token>& tokens);
        // uint8_t int_to_bct(int val) const;
        void error() const;
        void advance();
        void assemble_program();
        void assemble_label_instr();
        void assemble_instr();
        std::pair<Word, Word> assemble_operand(const std::string& operand_str);
        void assemble_zero_operand_instr(int32_t opcode);
        void assemble_one_operand_instr(int32_t opcode);
        void assemble_two_operand_instr(int32_t opcode);
    };
} // namespace termite

#endif