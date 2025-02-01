#include <fstream>
#include <iterator>
#include <vector>
#include <iostream>
#include <sstream>

#include "../core/tryte.h"
#include "../core/word.h"
// #include "./mem.h"
#include "./cpu.h"

int main(int argc, char** argv) {
    termite::Mem memory;

    if (std::string(argv[2]) == "-t") {
        std::string file_path = argv[1];
        std::ifstream file(file_path);

        if (!file) {
            std::cerr << "Error: Unable to open file " << file_path << std::endl;
            return 1;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string text = buffer.str();

        try {
            for (int i = 0; i < text.size(); i += 8) {
                std::string word;
                for (int j = 0; j < 8; j++) {
                    word += text.at(i + j);
                }
                // std::cout << termite::Word::from_int32(i >> 3) -.to_nonary_str() << '\n';
                memory.set_word(termite::Word::from_int32((i >> 3) - 21523360), termite::Word::from_nonary_str(word));
                // std::cout << memory.get_word(i >> 3).to_nonary_str() << '\n';
            }
            std::cout << (text.size() >> 2) << '\n';
            termite::Word cycles = termite::Word::from_int32(text.size() >> 2);
            std::cout << cycles.to_int32() << '\n';
            termite::CPU cpu;
            cpu.execute(cycles, memory);
        }
        catch (const std::string& e) {
            std::cerr << e << '\n';
            return 1;
        }
    }
    else {
    }
    return 0;
}

// int main(int argc, char** argv) {
//     termite::CPU cpu;

//     std::ifstream input(std::string(argv[1]), std::ios::binary);
//     if (input.fail()) {
//         std::cerr << "Error: failed to read file '" << argv[1] << "'\n";
//         return 1;
//     }


//     try {
//         std::vector<char> bytes(
//             (std::istreambuf_iterator<char>(input)),
//             (std::istreambuf_iterator<char>()));

//         input.close();

//         for (int i = 0; i < bytes.size(); i += 2) {
//             uint8_t lo_4_trits_bct = (uint8_t)bytes.at(i);
//             uint8_t hi_4_trits_bct = (uint8_t)bytes.at(i + 1);
//             cpu.mem.set_tryte(termite::Word::from_int32((i >> 1) - (termite::Mem::MAX_MEM >> 1)), termite::Tryte(lo_4_trits_bct + (hi_4_trits_bct << 8)));
//         }

//         bool verbose = false;
//         if (argc >= 3) {
//             verbose = (std::string(argv[2]) == "-v");
//         }

//         cpu.execute(bytes.size() >> 2, verbose);
//     }
//     catch (const std::string& e) {
//         std::cerr << e << '\n';
//         return 1;
//     }
//     return 0;
// }