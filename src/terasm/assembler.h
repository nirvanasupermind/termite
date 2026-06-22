#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <string>
#include <vector>
#include <map>
#include <utility>
#include "token.h"
#include "../core/word.h"

namespace termite {
    const std::map<std::string, int> NUM_OPERANDS_TABLE {
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
        {"sbb", 2},
        {"mul", 1},
        {"div", 1},
        {"neg", 1},
        {"cmp", 2},
        {"call", 1},
        {"ret", 0},
        {"jmp", 1},
        {"jl", 1},
        {"jle", 1},
        {"jg", 1},
        {"jge", 1},
        {"je", 1},
        {"jne", 1},
        {"jc", 1},
        {"jnc", 1},
        {"int", 1},
        {"xchg", 2},
        {"fld", 1},
        {"fst", 1},
        {"fstp", 1},
        {"fadd", 0},
        {"fsub", 0},
        {"fmul", 0},
        {"fdiv", 0},
        {"fsqrt", 0},
        {"fsin", 0},
        {"fcos", 0},
        {"ftan", 0},
        {"fatan", 0},
        {"fexp", 0},
        {"flog", 0},
        {"fabs", 0},
        {"ffloor", 0},
        {"fcmp", 0},
        {'ldt', 1},
        {'stt', 1}
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
        void label_pass();
        void error() const;
        void advance();
        void assemble_program();
        void assemble_label_instr();
        void assemble_instr();
        std::vector<Word> assemble_operand();
        void assemble_zero_operand_instr(int32_t opcode);
        void assemble_one_operand_instr(int32_t opcode);
        void assemble_two_operand_instr(int32_t opcode);
    };
} // namespace termite

#endif