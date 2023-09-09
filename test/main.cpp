#include <iostream>
#include "../src/tryte.h"
#include "../src/word.h"
#include "../src/mem.h"
#include "../src/cpu.h"

int main() {
    termite::CPU cpu;
    cpu.mem.load_bct_file("test/bctfile");
    cpu.execute(1);
    std::cout << cpu.registers[0].to_int32() << '\n';
}