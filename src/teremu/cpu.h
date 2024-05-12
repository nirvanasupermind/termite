#ifndef CPU_H
#define CPU_H

#include "../core/tryte.h"
#include "../core/word.h"
#include "./mem.h"

namespace termite {
    // Not an enum class so no explicit casting to int is needing
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
        DIV,
        DIVI,
        MOD,
        MODI,
        NOT,
        NOTI,
        AND,
        ANDI,
        OR,
        ORI,
        XOR,
        XORI,
        LSH,
        LSHI,
        RSH,
        RSHI,
        CMP,
        CMPI,
        B,
        BEQ,
        BNE,
        BLT,
        BLE,
        BGT,
        BGE,
        PUSH,
        POP,
        CALL,
        RET,
        SYS
    };

    enum Register {
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
        static std::string pad(const std::string& s, int length);
    };
} // namespace termite


#endif