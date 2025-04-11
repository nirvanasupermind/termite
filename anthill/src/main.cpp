#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include "../src/token.h"
#include "../src/lexer.h"
#include "../src/node.h"
#include "../src/parser.h"
#include "../src/symbol_table.h"
#include "../src/generator.h"


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
        std::string str = buffer.str();

        anthill::Lexer lexer(file_path, str);
        std::vector<anthill::Token> tokens = lexer.generate_tokens();
        anthill::Parser parser(file_path, tokens);
        anthill::Generator gen(file_path, std::make_shared<anthill::SymbolTable>(anthill::SymbolTable()));
        gen.visit(parser.parse(), gen.global_scope);
        std::ofstream myfile;
        myfile.open(file_path.substr(0, file_path.size() - 7) + "asm");
        myfile << "call main\n" << gen.asm_stream.str();
} catch(const std::string&e) {
    std::cerr << e << '\n';
    return 1;
}
}