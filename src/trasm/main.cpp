#include <iostream>
#include <string>
#include <vector>
#include "lexer.h"

int main() {
    termite::Lexer lexer("0n100", "");
    std::vector<termite::Token> tokens = lexer.generate_tokens();
    for (const termite::Token& token : tokens) {
        std::cout << token.str() << '\n';
    }
    return 0;
}