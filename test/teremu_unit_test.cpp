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
        {"push_pop", "DCD0 0000 0000 001A 0000 0000 DBC3 0000 0000 0000 0000 0000 DDCD D000 0000 0000 0000 00DC", "7"},
        {"and_regs", "DDC3 D000 0000 0000 0000 001A DDC2 D000 0000 0000 0000 001B D1C3 C200 0000 0000 0000 0000 DDCD D000 0000 0000 0000 00DC", "5"},
        {"or_regs", "DDC3 D000 0000 0000 0000 001A DDC2 D000 0000 0000 0000 001B D2C3 C200 0000 0000 0000 0000 DDCD D000 0000 0000 0000 00DC", "10"},
        {"xor_regs", "DDC3 D000 0000 0000 0000 001A DDC2 D000 0000 0000 0000 001B D3C3 C200 0000 0000 0000 0000 DDCD D000 0000 0000 0000 00DC", "-8"}  
    };

    int num_passed = 0;
    for(int i = 0; i < tests.size(); i++) {
        try {
        cpu.exec_text(tests[i][1], memory);
        if(cpu.regs[7].to_int32() == std::stoi(tests[i][2])) {
            std::cout << "test " + tests[i][0] + " passed";
            num_passed++;
        } else {
            std::cout << "test " + tests[i][0] + " FAILED";
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
