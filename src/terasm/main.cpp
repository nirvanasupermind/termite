#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <iostream>
#include "../core/word.h"
#include "./lexer.h"
#include "./assembler.h"

int main(int argc, char** argv) {
    std::ifstream input(std::string(argv[1]), std::ios::binary);
    if(input.fail()) {
        std::cout << "Error: failed to read file '" << argv[1] << "'\n";
        return 1;
    }
    std::stringstream buffer;
    buffer << input.rdbuf();
    std::string text = buffer.str();
    input.close();
    
    try {
        termite::Lexer lexer(text);
        std::vector<termite::Token> tokens = lexer.generate_tokens();
        termite::Assembler assembler(tokens);
        assembler.assemble_program();
        std::ofstream fout;
        fout.open(std::string(argv[2]), std::ios::binary);
        uint8_t bytes[assembler.code.size() * 4];
        for (int i = 0; i < assembler.code.size(); i++) {
            bytes[i * 4] = assembler.code.at(i).get_trit_range(0, 3).get_bct();
            bytes[i * 4 + 1] = assembler.code.at(i).get_trit_range(4, 7).get_bct();
            bytes[i * 4 + 2] = assembler.code.at(i).get_trit_range(8, 11).get_bct();
            bytes[i * 4 + 3] = assembler.code.at(i).get_trit_range(12, 15).get_bct();
        }
        fout.write((char*) &bytes, sizeof(bytes));
        fout.close();
    }
    catch (const std::string& e) {
        std::cout << e << '\n';
        return 1;
    }
    return 0;
}