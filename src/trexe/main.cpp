#include <array>
#include <cassert>
#include <fstream>
#include <iostream>
#include "vm.h"

int main(int argc, char** argv) {
    assert(argc >= 2);

    std::array<char, 200> buffer;

    //open file
    std::ifstream infile(argv[1]);

    //get length of file
    infile.seekg(0, std::ios::end);
    size_t length = infile.tellg();
    infile.seekg(0, std::ios::beg);

    // don't overflow the buffer!
    if (length > sizeof(buffer)) {
        length = sizeof(buffer);
    }

    //read file
    infile.read(&buffer[0], length);

    termite::VM vm;

    for (int i = 0; i < buffer.size(); i += 2) {
        termite::Tryte t((buffer.at(i) << 6) + buffer.at(i + 1));
        vm.mem.data[511758 + (i / 2)] = t;
    }

    vm.run();
    return 0;
}