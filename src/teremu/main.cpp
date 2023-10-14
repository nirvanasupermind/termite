#include <fstream>
#include <iterator>
#include <vector>
#include <iostream>
#include "../core/tryte.h"
#include "../core/word.h"
#include "./mem.h"
#include "./cpu.h"

int main(int argc, char** argv) {
    termite::CPU cpu;

    std::ifstream input(std::string(argv[1]), std::ios::binary);
    if(input.fail()) {
        std::cout << "Error: failed to read file '" << argv[1] << "'\n";
        return 1;
    }

    std::vector<char> bytes(
        (std::istreambuf_iterator<char>(input)),
        (std::istreambuf_iterator<char>()));

    input.close();

    for (int i = 0; i < bytes.size(); i += 2) {
        uint8_t lo_4_trits_bct = (uint8_t)bytes.at(i);
        uint8_t hi_4_trits_bct = (uint8_t)bytes.at(i + 1);
        cpu.mem.set_tryte(termite::Word::from_int32((i >> 1) - (termite::Mem::MAX_MEM >> 1)), termite::Tryte(lo_4_trits_bct + (hi_4_trits_bct << 8)));
    }
    
    bool verbose = false;
    if(argc >= 3) {
        verbose = (std::string(argv[2]) == "-v");
    }

    cpu.execute(bytes.size() >> 2, verbose);
}