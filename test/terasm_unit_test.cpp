#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include "../src/terasm/token.h"
#include "../src/terasm/lexer.h"
#include "../src/terasm/assembler.h"
#include "../src/core/word.h"


int main(int argc, char** argv) {
    std::cout << "*** TERASM UNIT TEST" << '\n';
    std::vector<std::vector<std::string> > tests{
        // mov
        {"mov [1], [di+1]", "DDB0 A100 0000 0001 0000 0001", "mov"}
    };

    int num_passed = 0;
    for (int i = 0; i < tests.size(); i++) {
        try {
            termite::Lexer lexer(tests[i][0]);
            termite::Assembler assembler(lexer.generate_tokens());
            assembler.label_pass();
            assembler.assemble_program();
            std::string output;
            for (int i = 0; i < assembler.code.size(); i++) {
                output = output + assembler.code.at(i).get_hi_tryte().to_nonary_str();
                output = output + ' ';
                output = output + assembler.code.at(i).get_lo_tryte().to_nonary_str();
                output = output + ' ';
            }

            if (output.substr(0, output.size() - 1) == tests[i][1]) {
                std::cout << "test " + tests[i][2] + " passed";
                num_passed++;
            }
            else {
                std::cout << "test " + tests[i][2] + " failed";
            }
            std::cout << " with output = " << output << '\n';
        }
        catch (const std::string& e) {
            std::cerr << "error: " << e << '\n';
            return 1;
        }
    }
    if (num_passed == tests.size()) {
        std::cout << "*** ALL TESTS PASSED" << '\n';
    }
    else {
        std::cout << "*** " << num_passed << '/' << tests.size() << " TESTS PASSED" << '\n';
    }
    return 0;
}