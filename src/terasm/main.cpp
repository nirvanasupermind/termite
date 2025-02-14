#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "token.h"
#include "lexer.h"
#include "assembler.h"
#include "../core/word.h"

int main() {
    try {
    std::string text = "push 5\nmov dx, 0nDC\nand dx, 5";
    termite::Lexer lexer(text);
    termite::Assembler assembler(lexer.generate_tokens());
    assembler.assemble_program();
    for(int i = 0; i < assembler.code.size(); i++) {
        std::cout << assembler.code.at(i).to_nonary_str() << '\n';
    }
    return 0;
} catch(const std::string&e) {
    std::cout << e << '\n';
    return 1;
}
}