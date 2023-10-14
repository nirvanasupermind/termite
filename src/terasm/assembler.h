#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <string>
#include "token.h"

namespace termite {
    class Assembler {
    public:
        std::vector<Token> tokens{};
        int pos;
        Token current;
        std::vector<uint8_t> code{};
        Assembler(const std::vector<Token>& tokens);
        void error() const;
        void advance();
        void assemble_program();
        void assemble_instr();
    };
} // namespace termite

#endif