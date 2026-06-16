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
        std::string output_code = gen.asm_stream.str();

        size_t colon_pos = output_code.find(':');

        if (colon_pos != std::string::npos) {
            size_t newline_pos = output_code.find_last_of("\n\r", colon_pos);

            std::string startup =
                "call main\n"
                "mov $0,%dx\n"
                "mov $0nDD,%ax\n"
                "int $0\n";

            if (newline_pos == std::string::npos) {
                output_code = startup + output_code;
            }
            else {
                output_code =
                    output_code.substr(0, newline_pos + 1) +
                    startup +
                    output_code.substr(newline_pos + 1);
            }
        }

        // size_t colon_pos = output_code.find(':');

        // if (colon_pos != std::string::npos) {
        //     size_t newline_pos = output_code.find_last_of("\n\r", colon_pos);

        //     if (newline_pos != std::string::npos) {
        //         std::string temp = output_code.substr(0,newline_pos+1) + "call main\n" + "mov $0,%dx\n" + "mov $0nDD,%ax\n" + "int $0\n"
        //         + output_code.substr(newline_pos);
        //         output_code = temp;
        //     }
        // }

        std::ofstream myfile;

        myfile.open(file_path.substr(0, file_path.size() - 7) + "asm");

        myfile << output_code;
        return 0;
    }
    catch (const std::string& e) {
        std::cerr << e << '\n';
        return 1;
    }
}