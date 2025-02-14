#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <vector>
#include "token.h"

namespace termite {
    const std::string WHITESPACE = " \t";
    const std::vector<std::string> INSTR_NAMES = {
        "mov",
        "push",
        "pop",
        "pushf",
        "popf",
        "and",
        "or",
        "xor",
        "shl",
        "shr",
        "add",
        "adc",
        "sbb",
        "mul",
        "div",
        "neg",
        "cmp",
        "call",
        "ret",
        "jmp",
        "jl",
        "jle",
        "jg",
        "jge",
        "je",
        "jne",
        "jc",
        "jnc",
        "int"
    };

    const std::vector<std::string> REG_NAMES = {
        "ax",
        "bx",
        "cx",
        "sp",
        "di",
        "si",
        "dx",
        "ip"  
    };

    class Lexer {
    public:
        std::string text{};
        int pos;
        char current;
        Lexer();
        Lexer(const std::string& text);
        void advance();
        std::vector<Token> generate_tokens();
        Token generate_identifier();    
        Token generate_number();    
    };
} // namespace termite

#endif