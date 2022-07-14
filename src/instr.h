#ifndef INSTR_H
#define INSTR_H

#include "tryte.h"

namespace termite
{
    enum class InstrType
    {
        NOP,
        // Memory management
        MOV,
        LDA,
        STA,
        // I/O
        IN,
        OUT,
        // Numerical operations
        ADD,
        NEG,
        SUB,
        MUL,
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
        JGE,
        JLE,
        JGE
    };

    // Represents a VM instruction.
    class Instr
    {
    public:
        InstrType type;
        Tryte op1;
        Tryte op2;

        Instr(InstrType type, const Tryte &op1, const Tryte &op2);
    };
} // namespace termite

#endif