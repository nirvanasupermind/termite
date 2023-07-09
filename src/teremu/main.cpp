// Main entry point for "teremu" command line utility
#include <cinttypes>
#include <fstream>
#include <vector>
#include "trit.h"
#include "tryte.h"
#include "word.h"
#include "mem.h"
#include "cpu.h"

// Decode binary-coded ternary into trytes that can be put in VM memory
std::vector<termite::Tryte> decode_bct(const std::vector<uint8_t>& bct_bytes) {
    std::vector<termite::Tryte> result;
    for (int i = 0; i < (bct_bytes.size() / 2) * 2; i += 2) {
        uint8_t hi_bct = bct_bytes.at(i);
        uint8_t lo_bct = bct_bytes.at(i + 1);
        uint16_t tryte_bct = lo_bct + (hi_bct << 8);
        result.push_back(termite::Tryte(tryte_bct));
    }
    return result;
}

int main(int argc, char** argv) {
    std::string filename;
    std::string option;

    if (argc == 3) {
        if (argv[2][0] == '-') {
            filename = std::string(argv[1]);
            option = std::string(argv[2]);
        }
        else if (argv[1][0] == '-') {
            filename = std::string(argv[2]);
            option = std::string(argv[1]);
        }
    }
    else {
        filename = std::string(argv[1]);
        option = "";
    }

    // open the file:
    std::ifstream file(filename, std::ios::binary);

    // Stop eating new lines in binary mode!!!
    file.unsetf(std::ios::skipws);

    // get its size:
    std::streampos fileSize;

    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // reserve capacity
    std::vector<uint8_t> vec;
    vec.reserve(fileSize);

    // read the data:
    vec.insert(vec.begin(),
        std::istream_iterator<uint8_t>(file),
        std::istream_iterator<uint8_t>());

    std::vector<termite::Tryte> trytes = decode_bct(vec);
    termite::CPU cpu;

    for (int i = 0; i < trytes.size(); i++) {
        cpu.memory.data[i] = trytes.at(i);
    }

    if (option == "-v") {
        cpu.execute((trytes.size() / 2), true);
    }
    else {
        cpu.execute((trytes.size() / 2));
    }
    return 0;
}