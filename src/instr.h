#ifndef INSTR_H
#define INSTR_H

#include "tryte.h"

namespace termite
{
    enum class InstrType
    {
        NOP,
        // Stack operations
        PUSH,
        POP,
        SWAP,
        // I/O
        IN,
        OUT,
        // Arithmetical operations
        ADD,
        NEG,
        SUB,
        MUL,
        AND,
        OR,
        XOR,
        SHL,
        SHR,
        CMP,
        // Control flow
        JMP,
        JE,
        JNE,
        JL,
        JG,
        JLE,
        JGE
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