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
    if(input.fail()) {
        std::cout << "Error: failed to read file '" << argv[1] << "'\n";
        return 1;
    }
    std::stringstream buffer;
    buffer << input.rdbuf();
    std::string text = buffer.str();
    input.close();
    
    try {
        anthill::Lexer lexer(filename, text);
        anthill::Parser parser(filename, lexer.generate_tokens());
        anthill::Compiler compiler(filename);
        std::shared_ptr<anthill::Env> global_env(new anthill::Env({}, {}));
        compiler.visit(parser.parse(), global_env);
        int main_start = compiler.assembly.find("_funcmain:");
        int branch_disp = 0;
        for(int i = 0; i < main_start; i++) {
            if(compiler.assembly.at(i) == ';') {
                branch_disp++;
            }
        }
        std::ofstream fout;
        fout.open(std::string(argv[2]));
        if(branch_disp != 0) {
            fout << "b " << branch_disp << ";\n";
        }
        fout << compiler.assembly;
        fout.close();
    }
    catch (const std::string& e) {
        std::cout << e << '\n';
        return 1;
    }

    return 0;
}