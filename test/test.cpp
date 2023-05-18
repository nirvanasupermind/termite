#include <string>
#include <iostream>
#include <chrono>
#include "../src/trit.h"
#include "../src/word.h"
#include "../src/mem.h"

#include "../src/cpu.h"

int main() {
    termite::CPU cpu;
    cpu.reset();
    cpu.registers[0] = termite::Word::from_int32(2);
    cpu.registers[1] = termite::Word::from_int32(80);
    for(int i = 0; i < 1000; i++) {
    cpu.memory.set_word(termite::Word::from_int32(2 * i), 0b01000101000000000000000000000000);
    }
    // performance timing code
    // auto start = std::chrono::system_clock::now();
    cpu.execute(1000);
    // auto end = std::chrono::system_clock::now();
    // std::chrono::duration<double> elapsed_seconds = end-start;
    // std::cout << '\n' << "[Finished in " << elapsed_seconds.count() << "s]" << '\n';
    // cpu.print_state();    
    return 0;
}