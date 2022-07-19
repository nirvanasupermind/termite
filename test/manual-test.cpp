#include <iostream>
#include <array>

#include "../src/core/tryte.h"

int main() 
{   
    termite::Tryte tryte1("040");
    termite::Tryte tryte2("02Y");

    std::cout << (tryte1 + tryte2).to_str() << '\n'; // 1XY

    // termite::VM vm;

    // // program - many instructions
    // // instruction size = 1 word
    // // word size = 2 trytes
    // // tryte size = 6 trits (convention I adopted from "Setun" ternary computer)
    
    // std::vector<termite::Word> program {
    //     // push 13;
    //     termite::Word(termite::Tryte("000001"), termite::Tryte("000111")), // stack: 13
    //     // push 14;
    //     termite::Word(termite::Tryte("000001"), termite::Tryte("000111")), // stack: 13
    //     // add;
    //     termite::Word(termite::Tryte("0001T0"), termite::Tryte("000000")), // stack: 26
    //     // out;
    //     termite::Word(termite::Tryte("0001TT"), termite::Tryte("000001")), // stack: (empty)
    //     // jmp 0;
    //     termite::Word(termite::Tryte("001TT1"), termite::Tryte("000000")), // stack: (empty)
    // };

    // vm.exec_program(program);
}