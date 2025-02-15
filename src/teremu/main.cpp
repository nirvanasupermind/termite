#include <fstream>
#include <iterator>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "../core/tryte.h"
#include "../core/word.h"
// #include "./mem.h"
#include "./cpu.h"

int main(int argc, char** argv) {
    termite::Mem memory;
    termite::CPU cpu;
    cpu.reset(memory);

    bool verbose = false;
    if(argc == 4) {
        verbose = std::string(argv[2]) == "-t" || std::string(argv[3]) == "-t";
    }
    
    bool text = false;
    if(argc == 3) {
        text = std::string(argv[2]) == "-t";
    } else if(argc == 4) {
        text = std::string(argv[2]) == "-t" || std::string(argv[3]) == "-t";
    }

    if (text) {
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
            cpu.exec_text(text, memory, verbose);
        }
        catch (const std::string& e) {
            std::cerr << e << '\n';
            return 1;
        }
    }
    else {
        std::ifstream input(std::string(argv[1]), std::ios::binary);
    try {
        std::vector<char> bytes(
            (std::istreambuf_iterator<char>(input)),
            (std::istreambuf_iterator<char>()));

        input.close();

        for (int i = 0; i < bytes.size(); i += 2) {
            uint8_t lo_4_trits_bct = (uint8_t)bytes.at(i);
            uint8_t hi_4_trits_bct = (uint8_t)bytes.at(i + 1);
            memory.set_tryte(termite::Word::from_int32((i >> 1) - (termite::Mem::MAX_MEM >> 1)), termite::Tryte(lo_4_trits_bct + (hi_4_trits_bct << 8)));
        }

        termite::Word cycles = termite::Word::from_int32(bytes.size() << 1);
        cpu.execute(cycles, memory, verbose);
    }
    catch (const std::string& e) {
        std::cerr << e << '\n';
        return 1;
    }
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