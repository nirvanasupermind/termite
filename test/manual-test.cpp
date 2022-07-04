#include <iostream>
#include <array>

#include "../src/tryte.h"
#include "../src/tryte.h"
#include "../src/word.h"
#include "../src/vm.h"

int main() 
{   
    termite::VM vm;

    // program - many instructions
    // instruction size = 1 word
    // word size = 2 trytes
    // tryte size = 6 trits (convention I adopted from "Setun" ternary computer)
    
    std::vector<termite::Word> program {
        // push 13;
        termite::Word(termite::Tryte("000001"), termite::Tryte("000111")), // stack: 13
        // push 14;
        termite::Word(termite::Tryte("000001"), termite::Tryte("001TTT")), // stack: 14 13
        // add;
        termite::Word(termite::Tryte("0001T0"), termite::Tryte("000000")), // stack: 27
        // out;
        termite::Word(termite::Tryte("0001TT"), termite::Tryte("000001")), // stack: (empty)
        // jmp 0;
        termite::Word(termite::Tryte("000111"), termite::Tryte("000000")), // stack: (empty)
    };

    vm.exec_program(program);
}