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
        global_env->types["print_int"] = anthill::StaticType(anthill::BasicType::VOID);
        global_env->types["print_int"].func_arg_types.push_back(anthill::StaticType(anthill::BasicType::INT));
        global_env->addrs["print_int"] = 0;

        compiler.visit(parser.parse(), global_env);
        std::string boilerplate = 
        "print_int:"
        "movi r-11, -81;"
        "ld r-13, r-11, 0;"
        "movi r-11, 2;"
        "st r-13, r-11, 0;"
        "movi r-11, 2;"
        "ld r-13, r-11, 0;"
        "sys 1;"
        "movi r-13, 0;"
        "mov r13, r-9;";

        std::string full_assembly = boilerplate + '\n' + compiler.assembly;
        int main_start = full_assembly.find("main:");
        int branch_disp = 0;
        for(int i = 0; i < main_start; i++) {
            if(full_assembly.at(i) == ';') {
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