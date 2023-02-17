#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "../core/trit.h"
#include "../core/tryte.h"
#include "token.h"
#include "lexer.h"
#include "assembler.h"


void assemble(const std::string& in_filename, const std::string& out_filename, const std::string& text) {
    termite::Lexer lexer(text, in_filename);
    std::vector<termite::Token> tokens = lexer.generate_tokens();
    termite::Assembler assembler(tokens, in_filename);
    std::vector<termite::Trit> machine_code = assembler.generate_machine_code();
    std::ofstream out_file;
    out_file.open(out_filename);
    for(int i = 0; i < machine_code.size(); i += 4) {
        termite::Tryte t;
        t.set_trit(0, 0);
        t.set_trit(1, 0);
        t.set_trit(2, machine_code.at(i));
        t.set_trit(3, machine_code.at(i + 1));
        t.set_trit(4, machine_code.at(i + 2));
        t.set_trit(5, machine_code.at(i + 3));
        out_file << (char)(t.to_bct());
    }
    out_file.close();
}

int main(int argc, char** argv) {
    if ((argc < 4)) {
        std::cerr << "Usage: terasm [infile] -o [outfile]" << '\n';
        return 1;
    }
    else {
        std::string in_filename(argv[1]);
        std::ifstream in_file;

        in_file.open(in_filename);

        std::stringstream strStream;
        strStream << in_file.rdbuf();

        std::string text = strStream.str();

        if (text == "") {
            std::cerr << "File \"" + in_filename + "\" is empty or does not exist" << '\n';
            return 1;
        }

        std::string out_filename(argv[3]);

        try {
            assemble(in_filename, out_filename, text);
            in_file.close();
        }
        catch (const std::string& e) {
            std::cerr << e << '\n';
            return 0;
        }
    }

    return 0;
}

