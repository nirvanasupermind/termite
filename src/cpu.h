#ifndef CPU_H
#define CPU_H

#include "word.h"
#include "mem.h"

namespace termite {
    enum Opcode { 
    MOV,
    MOVI,
    MVN,
    MVNI
    };

    class CPU {
    public:
        Word registers[9];
        Word cpsr;
        Mem mem;
        CPU();
        void reset();
        Word fetch_tryte(int& cycles);
        Word fetch_word(int& cycles);
        void execute(int cycles, bool verbose = false);
        void print_state();
        void invalid_opcode(const Word& opcode);
        void set_sign_flag(const Word& result);

    };

} // namespace termite


#endif