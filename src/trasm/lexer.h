#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

#include "token.h"

namespace termite {

    const std::string WHITESPACE(" \n\t");
    const std::string TER_DIGITS("012");
    const std::string NON_DIGITS("012345678");

    class Lexer {
    public:
        std::string text{};
        std::size_t pos;
        std::string filename{};
        std::size_t line;
        char current;

        Lexer(const std::string& text, const std::string& filename);

        void advance();
        std::vector<Token> generate_tokens();
        Token generate_number();
        Token generate_identifier();        
    };

} // namespace termite

#endif // LEXER_H