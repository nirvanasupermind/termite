#include <cassert>
#include <cinttypes>
#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <chrono>
#include "vm.h"

double timeSinceEpochMillisec() {
  using namespace std::chrono;
  return duration_cast<microseconds>(system_clock::now().time_since_epoch()).count() * 0.001;
}

int main(int argc, char** argv) {
    std::ifstream input(argv[1], std::ios::binary);

    std::vector<uint8_t> bytes(
         (std::istreambuf_iterator<char>(input)),
         (std::istreambuf_iterator<char>()));

    input.close();

    // std::vector<bool> bits;

    // for(uint8_t b : bytes) {
    //     for (int i = 7; i >= 0; i--) {
    //         bits.push_back((b >> i) & 1);
    //     }
    // }
    
    termite::VM vm;

    for (int i = 0; i < (bytes.size() / 3) * 3; i += 3) {
        uint32_t bct = (bytes.at(i) << 16) + (bytes.at(i + 1) << 8) + (bytes.at(i + 2));
        termite::Tryte t1(bct >> 12);
        termite::Tryte t2(bct & 4095);
        vm.mem.data[1458 + ((i * 2)/3)] = t1;
        vm.mem.data[1459 + ((i * 2)/3)] = t2;
    }

    double time1 = timeSinceEpochMillisec();
    vm.run();
    double time2 = timeSinceEpochMillisec();
    std::cout << "[Finished in " << (time2 - time1) << "ms]" << '\n';
    return 0;
}