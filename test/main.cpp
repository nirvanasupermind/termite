#include <iostream>
#include "../src/terasm/lexer.h"

int main() {
    termite::Lexer lexer("movps r0 r-5 9\t\nabcde\r:;,");
    std::vector<termite::Token> tokens = lexer.generate_tokens();
    for(int i = 0; i < tokens.size(); i++) {
        std::cout << tokens.at(i).type << ' ' << tokens.at(i).value << '\n';
    }
}