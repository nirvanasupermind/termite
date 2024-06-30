#include <fstream>
#include <sstream>
#include <iterator>
#include <vector>
#include <iostream>
#include <string>
#include "./token.h"
#include "./lexer.h"
#include "./node.h"
#include "./parser.h"
#include "./compiler.h"
#include "./env.h"

int main(int argc, char** argv) {
    std::string filename(argv[1]);
    std::ifstream input(filename, std::ios::binary);
    if (input.fail()) {
        std::cout << "Error: failed to read file '" << argv[1] << "'\n";
        return 1;
    }
    std::stringstream buffer;
    buffer << input.rdbuf();
    std::string stl = "";
// "int _MALLOC_COUNTER = 1000;"
// "int _MALLOC_COUNTER_2 = 0;"
// "void print_int(int c) {"
// "__asm__(\"sys 1;\");"
// "}"
// "void print_char(char c) {"
// "__asm__(\"sys 3;\");"
// "}"
// "char* malloc(int size) {"
// "char* result = _MALLOC_COUNTER;"
// "_MALLOC_COUNTER = _MALLOC_COUNTER + size;"
// "return result;"
// "}"
// "void free(char* ptr) {"
// "_MALLOC_COUNTER_2 = ptr;"
// "}";

    std::string text = stl + buffer.str();
    input.close();


    try {
        anthill::Lexer lexer(filename, text);
        anthill::Parser parser(filename, lexer.generate_tokens());
        anthill::Compiler compiler(filename);
        std::shared_ptr<anthill::Env> global_env(new anthill::Env({}, {}));
        compiler.visit(parser.parse(), global_env);
        std::string full_assembly = compiler.assembly;
        int main_start = full_assembly.find("main:");
        int branch_disp = 0;
        for (int i = 0; i < main_start; i++) {
            if (full_assembly.at(i) == ';') {
                // std::cout << i << ' ' << compiler.assembly.at(i - 1) << '\n';
                branch_disp += 2;
            }
        }
        std::ofstream fout;
        fout.open(std::string(argv[2]));
        fout << "b " << branch_disp << ";\n";
        fout << full_assembly;
        fout.close();
    }
    catch (const std::string& e) {
        std::cout << e << '\n';
        return 1;
    }

    return 0;
}