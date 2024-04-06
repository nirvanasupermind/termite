#ifndef LEXER_H
#define LEXER_H
#include <string>
#include "token.h"

namespace termite {
    const std::string WHITESPACE = " \n\t";
    const std::vector<std::string> KEYWORDS = {
        "mov",
        "movi",
        "movps",
        "ld",
        "st",
        "add",
        "addi",
        "addc",
        "addci",
        "sub",
        "subi",
        "subc",
        "subci",
        "mul",
        "muli",
        "div",
        "divi",
        "mod",
        "modi",
        "not",
        "noti",
        "and",
        "andi",
        "or",
        "ori",
        "xor",
        "xori",
        "lsh",
        "lshi",
        "rsh",
        "rshi",
        "cmp",
        "cmpi",
        "b",
        "beq",
        "bne",
        "blt",
        "ble",
        "bgt",
        "bge",
        "push",
        "pop",
        "call",
        "ret",
        "sys"
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