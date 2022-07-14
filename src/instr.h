#ifndef INSTR_H
#define INSTR_H

#include "tryte.h"

namespace termite
{
    enum class Instr
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
} // namespace termite

#endif