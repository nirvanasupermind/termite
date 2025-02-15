#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include "token.h"
#include "lexer.h"
#include "assembler.h"
#include "../core/word.h"

int main(int argc, char** argv) {
    try {
        std::string file_path = argv[1];
        std::ifstream file(file_path);

        if (!file) {
            std::cerr << "Error: Unable to open file " << file_path << std::endl;
            return 1;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string text = buffer.str();

    termite::Lexer lexer(text);
    termite::Assembler assembler(lexer.generate_tokens());
    std::ofstream myfile;
    // myfile.open(file_path.substr(0, file_path.size() - 4));
    // assembler.label_pass();
    // assembler.assemble_program();
    // for(int i = 0; i < assembler.code.size(); i++) {
    //    uint16_t hi = assembler.code.at(i).get_hi_tryte().get_bct();
    //    uint16_t lo = assembler.code.at(i).get_lo_tryte().get_bct();
    //    myfile << (char)(lo & 0xff);
    //    myfile << (char)(lo >> 8);
    //    myfile << (char)(lo & 0xff);
    //    myfile << (char)(lo >> 8);
    // }

    myfile.open(file_path.substr(0, file_path.size() - 4) + ".txt");
    assembler.label_pass();
    assembler.assemble_program();
    for(int i = 0; i < assembler.code.size(); i++) {
       myfile << assembler.code.at(i).get_hi_tryte().to_nonary_str();
       myfile << ' ';
       myfile << assembler.code.at(i).get_lo_tryte().to_nonary_str();
       myfile << ' ';
    }
    return 0;
} catch(const std::string&e) {
    std::cout << e << '\n';
    return 1;
}
}