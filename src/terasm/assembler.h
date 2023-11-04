#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <string>
#include <map>
#include "token.h"
#include "../core/word.h"

namespace termite {
    class Assembler {
    public:
        std::vector<Token> tokens{};
        int pos;
        Token current;
        std::vector<Word> code{};
        std::map<std::string, Word> labels{};
        Assembler(const std::vector<Token>& tokens);
        uint8_t int_to_bct(int val) const;
        void error() const;
        void advance();
        void assemble_program();
        void assemble_label_instr();
        void assemble_instr();
        void assemble_rrr_instr(int idx);
        void assemble_rri_instr(int idx);        
    };
} // namespace termite

#endif