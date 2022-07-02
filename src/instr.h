#ifndef INSTR_H
#define INSTR_H

#include "tryte.h"

namespace termite
{
    enum class InstrType
    {
        NOP,    
        // MOV,
        POP,
        IN,
        OUT,
        LOAD,
        STOR,
        ADD,
        NEG,
        SUB,
        MUL,
        NOT,
        AND,
        OR,
        XOR,
        LS,
        RS,
        CMP,
        JMP,
        CJMP
    };

    // Represents a VM instruction.
    class Instr
    {
    public:
        InstrType type;
        Tryte val;

        Instr(InstrType type, const Tryte &val);
    };
} // namespace termite

#endif