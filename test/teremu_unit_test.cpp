
#include <fstream>
#include <iterator>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "../src/core/tryte.h"
#include "../src/core/word.h"
#include "../src/teremu/cpu.h"

int main(int argc, char** argv) {
    termite::Mem memory;
    termite::CPU cpu;
    std::cout << "*** TEREMU UNIT TEST" << '\n';
    std::vector<std::vector<std::string> > tests {
        // push_imm_pop_to_reg
        {"DCD0 0000 0000 001A 0000 0000 DBC3 0000 0000 0000 0000 0000", "8", "push_imm_pop_to_reg"},
        // and_regs
        {"DDC3 D000 0000 0000 0000 001A DDC2 D000 0000 0000 0000 001B D1C3 C200 0000 0000 0000 0000", "5", "and_regs"},
        // or_regs
        {"DDC3 D000 0000 0000 0000 001A DDC2 D000 0000 0000 0000 001B D2C3 C200 0000 0000 0000 0000", "10", "or_regs"},
        // xor_regs
        {"DDC3 D000 0000 0000 0000 001A DDC2 D000 0000 0000 0000 001B D3C3 C200 0000 0000 0000 0000", "-8", "xor_regs"},
        // shl_regs
        {"DDC3 D000 0000 0000 0000 001A DDC2 D000 0000 0000 0000 001B D4C3 C200 0000 0000 0000 0000", "17496", "shl_regs"},
        // shr_regs
        {"DDC3 D000 0000 0000 0000 001A DDC2 D000 0000 0000 0000 0001 CDC3 C200 0000 0000 0000 0000", "3", "shr_regs"},
        // add_regs
        {"DDC3 D000 0000 0000 0000 001A DDC2 D000 0000 0000 0000 001B CCC3 C200 0000 0000 0000 0000", "15", "add_regs"},
        // adc_regs
        {"DDC3 D000 0000 0000 4444 4444 DDC2 D000 0000 0000 0000 0001 CCC3 C200 0000 0000 0000 0000 DDC3 D000 0000 0000 0000 001A DDC2 D000 0000 0000 0000 001B CBC3 C200 0000 0000 0000 0000", "16", "adc_regs"},
        // sub_regs
        {"DDC3 D000 0000 0000 0000 001A DDC2 D000 0000 0000 0000 001B CAC3 C200 0000 0000 0000 0000", "1", "sub_regs"},
        // sbb_regs
        {"DDC3 D000 0000 0000 4444 4444 DDC2 D000 0000 0000 0000 0001 CCC3 C200 0000 0000 0000 0000 DDC3 D000 0000 0000 0000 001A DDC2 D000 0000 0000 0000 001B C0C3 C200 0000 0000 0000 0000", "0", "sbb_regs"},
        // mul_regs_lo
        {"DDCD D000 0000 0000 4444 4444 DDC2 D000 0000 0000 0000 0003 C1C2 0000 0000 0000 0000 0000 DDC3 CD00 0000 0000 0000 0000", "21523359", "mul_regs_lo"},
        // mul_regs_hi
        {"DDCD D000 0000 0000 4444 4444 DDC2 D000 0000 0000 0000 0003 C1C2 0000 0000 0000 0000 0000", "2", "mul_regs_hi"},
        // div_regs_quo
        {"DDCD D000 0000 0000 4444 4444 DDC2 D000 0000 0000 0000 0003 C2C2 0000 0000 0000 0000 0000 DDC3 CD00 0000 0000 0000 0000", "7174453", "div_regs_quo"},
        // div_regs_rem
        {"DDCD D000 0000 0000 4444 4444 DDC2 D000 0000 0000 0000 0003 C2C2 0000 0000 0000 0000 0000", "1", "div_regs_rem"},
        // neg_reg
        {"DDC3 D000 0000 0000 0000 001A C3C3 0000 0000 0000 0000 0000", "-8", "neg_reg"},
        // cmp_regs
        {"DDC3 D000 0000 0000 0000 001A DDC2 D000 0000 0000 0000 001B C4C3 C200 0000 0000 0000 0000 DA00 0000 0000 0000 0000 0000 DBC3 0000 0000 0000 0000 0000", "3", "cmp_regs"}      
    };

    int num_passed = 0;
    for(int i = 0; i < tests.size(); i++) {
        try {
        cpu.exec_text(tests[i][0], memory);
        if(cpu.regs[7].to_int32() == std::stoi(tests[i][1])) {
            std::cout << "test " + tests[i][2] + " passed";
            num_passed++;
        } else {
            std::cout << "test " + tests[i][2] + " failed";
        }
        std::cout << " with DX = " << cpu.regs[7].to_int32() << '\n';
        } catch(const std::string& e) {
            std::cerr << e << '\n';
            return 1;
        }
    }
    if(num_passed == tests.size()) {
        std::cout << "*** ALL TESTS PASSED" << '\n';
    } else {
        std::cout << "*** " << num_passed << '/' << tests.size() << " TESTS PASSED" << '\n';
    }
    return 0;
}
