// Class for the Termite emulator CPU
#ifndef CPU_H

#include <iostream>
#include "tryte.h"
#include "word.h"
#include "mem.h"

namespace termite {
    const int LR = 25;
    const int PC = 26;

    const int S = 0;
    const int C = 1;

    enum Opcode {
        MOV,
        MOVI,
        LDR,
        STR,
        NEG,
        ADD,
        ADDI,
        ADDC,
        ADDCI,
        SUB,
        SUBI,
        SUBC,
        SUBCI,
        MUL,
        MULI,
        NOT,
        AND,
        ANDI,
        OR,
        ORI,
        SL,
        LSR,
        ASR,
        B,
        BEQ,
        BNE,
        BLT,
        BLE,
        BGT,
        BGE,
        BL,
        SWI
    };


    class CPU {
    public:
        Word registers[27];
        Word cpsr;
        Mem memory;
        void reset();
        Word fetch_tryte(int& cycles);
        Word fetch_word(int& cycles);
        void execute(int cycles, bool verbose = false);
        void print_state();
        void invalid_opcode(const Word& opcode);
        void set_sign_flag(const Word& result);
    };
} // namespace termite

#endif // CPU_H