#include <iostream>
#include <cassert>
#include "../src/core/trybble.h"
#include "../src/core/tryte.h"

int main() 
{   
    termite::Tryte tryte1((int8_t)0, (int8_t)13);
    termite::Tryte tryte2((int8_t)0, (int8_t)5); 

    std::cout << (-tryte2).to_ternary_str() << '\n';

    return 0;

    // termite::Tryte tryte3((int8_t)0, (int8_t)3);
    // termite::Tryte tryte4((int8_t)0, (int8_t)1);

    // assert((tryte3 + tryte4).to_int16() == 4);
    

    // termite::Tryte tryte1((int8_t)0, (int8_t)10);
    // termite::Tryte tryte2((int8_t)0, (int8_t)1);

    // std::cout << (int)((tryte1 + tryte2).lo_bct().get_bits()) << '\n';

    // // termite::VM vm;

    // // // Assembly: lda #$020;
    // // // 02102000 011000000 000000000 000000000 000000000 000000000 000000000 ...
    // // // Instruction - 18 trits / 3 trytes (4-trit opcode, 2-trit addressing mode, 12-trit addressable)

    // // // 021020000
    // // // 02 1 020000
 
    // // vm.mem.store(termite::Word("000000"), termite::Tryte("021")); 
    // // vm.mem.store(termite::Word("000001"), termite::Tryte("020")); 
    // // vm.mem.store(termite::Word("000002"), termite::Tryte("000"));

    // // // Assembly: ret #$000;
    // // vm.mem.store(termite::Word("000003"), termite::Tryte("011")); 
    // // vm.mem.store(termite::Word("000004"), termite::Tryte("000")); 
    // // vm.mem.store(termite::Word("00001W"), termite::Tryte("000"));

    // // vm.exec_program();
}