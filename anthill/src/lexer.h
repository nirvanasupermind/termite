#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <vector>
#include <map>
#include "token.h"

namespace anthill {
    class Lexer {
    public:
        std::string file;
        std::string text;
        int line;
        int pos;
        char current;
        std::map<std::string, std::vector<Token> > macros;
        Lexer();
        Lexer(const std::string& file, const std::string& text);
        void advance();
        std::vector<Token> generate_tokens();
        Token generate_identifier();    
        Token generate_number();   
        char generate_ch();
        Token generate_str();    
    };
}

#endif