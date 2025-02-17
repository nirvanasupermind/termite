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
        {"mov [3], [di+2]", "DDB0 A100 0000 0003 0000 0002", "mov"},
        // mov_ternary
        {"mov [3], [di+0tA10]", "DDB0 A100 0000 0003 0000 00A3", "mov_ternary"},
        // mov_nonary
        {"mov [3], [di+0nDA]", "DDB0 A100 0000 0003 0000 00DA", "mov_nonary"},
        // push
        {"push [3]", "DCB0 0000 0000 0003 0000 0000", "push"},
        // pop
        {"pop [di+0]", "DBA1 0000 0000 0000 0000 0000", "pop"},
        // pushf
        {"pushf", "DA00 0000 0000 0000 0000 0000", "pushf"},
        // popf
        {"popf", "D000 0000 0000 0000 0000 0000", "popf"},
        // and
        {"and [3],dx", "D1B0 C300 0000 0003 0000 0000", "and"},
        // or
        {"or [4],[bp+4]", "D2B0 A000 0000 0004 0000 0004", "or"},
        // xor
        {"xor dx,1", "D3C3 D000 0000 0000 0000 0001", "xor"},
        // shl
        {"shl di,2", "D4C1 D000 0000 0000 0000 0002", "shl"},
        // shr
        {"shr bp,dx", "CDC0 C300 0000 0000 0000 0000", "shr"},
        // add
        {"add [1],2", "CCB0 D000 0000 0001 0000 0002", "add"},
        // adc
        {"adc [4],[dx+2]", "CBB0 A300 0000 0004 0000 0002", "adc"},
        // sub
        {"sub [di+1],si", "CAA1 C200 0000 0001 0000 0000", "sub"},
        // sbb
        {"sbb [1],3", "C0B0 D000 0000 0001 0000 0003", "sbb"},
        // mul
        {"mul [2]", "C1B0 0000 0000 0002 0000 0000", "mul"},
        // div
        {"div [bp+0]", "C2A0 0000 0000 0000 0000 0000", "div"},
        // neg
        {"neg [4]", "C3B0 0000 0000 0004 0000 0000", "neg"},
        // cmp
        {"cmp [si+2],[di+2]", "C4A2 A100 0000 0002 0000 0002", "cmp"},
        // call
        {"call 4", "BDD0 0000 0000 0004 0000 0000", "call"},
        // call2
        {"test: mov [3], [di+2]\nret\ncall test", "DDB0 A100 0000 0003 0000 0002 BC00 0000 0000 0000 0000 0000 BDD0 0000 DDDD DDDD 0000 0000", "call2"},
        // call3
        {"call test\ntest: mov [3], [di+2]\nret", "BDD0 0000 DDDD DDD2 0000 0000 DDB0 A100 0000 0003 0000 0002 BC00 0000 0000 0000 0000 0000", "call3"},
        // ret
        {"ret", "BC00 0000 0000 0000 0000 0000", "ret"},
        // jmp
        {"jmp 4", "BBD0 0000 0000 0004 0000 0000", "jmp"},
        // jl
        {"jl 4", "BAD0 0000 0000 0004 0000 0000", "jl"},
        // jle
        {"jle 4", "B0D0 0000 0000 0004 0000 0000", "jle"},
        // jg
        {"jg 4", "B1D0 0000 0000 0004 0000 0000", "jg"},
        // jge
        {"jge 4", "B2D0 0000 0000 0004 0000 0000", "jge"},
        // je
        {"je 4", "B3D0 0000 0000 0004 0000 0000", "je"},
        // jne
        {"jne 4", "B4D0 0000 0000 0004 0000 0000", "jne"},
        // jc
        {"jc 4", "ADD0 0000 0000 0004 0000 0000", "jc"},
        // jnc
        {"jnc 4", "ACD0 0000 0000 0004 0000 0000", "jnc"},
        // int
        {"int 4", "ABD0 0000 0000 0004 0000 0000", "int"}
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