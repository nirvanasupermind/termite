#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <vector>
#include "token.h"

namespace anthill {
    class Lexer {
    public:
        std::string text{};
        int line;
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