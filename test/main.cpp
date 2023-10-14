#include <iostream>
#include "../src/core/word.h"
#include "../src/terasm/lexer.h"
#include "../src/terasm/assembler.h"

int main() {
    try {
        termite::Lexer lexer("mov r3, rrofvigjm;");
        std::vector<termite::Token> tokens = lexer.generate_tokens();
        termite::Assembler assembler(tokens);
        assembler.assemble_program();
        for (int i = 0; i < assembler.code.size(); i++) {
            std::cout << assembler.code.at(i).str() << '\n';
        }
    }
    catch (const std::string& e) {
        std::cout << e << '\n';
    }
}