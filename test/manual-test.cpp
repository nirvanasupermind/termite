#include <iostream>

#include "../src/core/tryte.h"
#include "../src/vm/vm.h"

int main() 
{   
    // termite::VM vm;

    // // Assembly: lda #$020;
    // // 02102000 011000000 000000000 000000000 000000000 000000000 000000000 ...
    // // Instruction - 18 trits / 3 trytes (4-trit opcode, 2-trit addressing mode, 12-trit addressable)

    // // 021020000
    // // 02 1 020000
 
    // vm.mem.store(termite::Word("000000"), termite::Tryte("021")); 
    // vm.mem.store(termite::Word("000001"), termite::Tryte("020")); 
    // vm.mem.store(termite::Word("000002"), termite::Tryte("000"));

    // // Assembly: ret #$000;
    // vm.mem.store(termite::Word("000003"), termite::Tryte("011")); 
    // vm.mem.store(termite::Word("000004"), termite::Tryte("000")); 
    // vm.mem.store(termite::Word("00001W"), termite::Tryte("000"));

    // vm.exec_program();
}