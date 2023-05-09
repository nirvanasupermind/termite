#include <string>
#include <iostream>
#include "../src/trit.h"
#include "../src/word.h"
#include "../src/mem.h"

#include "../src/cpu.h"

int main() {
    // termite::Word x = termite::Word::from_int(6661);
    // termite::Word y = termite::Word::from_int(30);

    // std::cout << x.hi_tryte().to_int() << '\n';
    termite::CPU cpu;
    cpu.reset();
    cpu.registers[0] = termite::Word::from_int(5);
    cpu.registers[1] = termite::Word::from_int(7);
    cpu.memory.set_word(termite::Word::from_int(0), 0b00000110000000000000000001000000);
    // add r0,r0,r1
    // cpu.memory.set_word(termite::Word::from_int(5), termite::Word::from_int(6661));
    cpu.execute(1);
    cpu.print_state();    
    return 0;
}