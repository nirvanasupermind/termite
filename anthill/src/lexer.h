#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "token.h"

namespace anthill {
    const std::vector<std::string> KEYWORDS = {
        "void",
        "char",
        "int",
        "if",
        "else",
        "while",
        "for",
        "return",
        "print"
    };
    
    class Lexer {
    public:
        std::string filename;
        std::string text;
        int line;
        int pos;
        char current;
        Lexer(const std::string& filename, const std::string& text);
        void advance();
        std::vector<Token> generate_tokens();
        Token generate_int();
        Token generate_string();
        Token generate_identifier();
    };
} // namespace anthill

#endif // LEXER_H