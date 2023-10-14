#ifndef CPU_H
#define CPU_H

#include "../core/tryte.h"
#include "../core/word.h"
#include "./mem.h"

namespace termite {
    enum Opcode {
        MOV = -40,
        MOVI,
        MOVPS,
        LD,
        ST,
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
        NOTI,
        AND,
        ANDI,
        OR,
        ORI,
        LSH,
        LSHI,
        RSH,
        RSHI,
        CMP,
        CMPI,
        JMP,
        JEQ,
        JNE,
        JLT,
        JLE,
        JGT,
        JGE,
        PUSH,
        POP,
        CALL,
        RET,
        SYS
    };


    enum Regfter {
        SP = 25,
        PC
    };

    enum Flag {
        SF,
        CF
    };

    class CPU {
    public:
        Mem mem;
        Word registers[27];
        Word psr;
        CPU();
        void reset();
        Word fetch_word(int& cycles);
        void set_sign_flag(Word& result);
        void print_state() const;
        void execute(int cycles, bool verbose = false);
    };
} // namespace termite


#endif