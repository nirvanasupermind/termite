#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "lexer.h"


int main(int argc, char** argv) {
    assert(argc >= 2);

    std::array<char, 20000> buffer;

    //open file
    std::ifstream infile(argv[1]);

    //get length of file
    infile.seekg(0, std::ios::end);
    size_t length = infile.tellg();
    infile.seekg(0, std::ios::beg);

    // don't overflow the buffer!
    if (length > sizeof(buffer)) {
        length = sizeof(buffer);
    }

    //read file
    infile.read(&buffer[0], length);

    try {
        std::string text(&buffer[0]);
        std::string filename(argv[1]);
        termite::Lexer lexer(text, filename);

        std::vector<termite::Token> tokens = lexer.generate_tokens();
        for (const termite::Token& token : tokens) {
            std::cout << token.str() << '\n';
        }
    } catch (const std::string& e) {
        std::cerr << e << '\n';
    }
    return 0;
}