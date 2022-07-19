#ifndef OP_H
#define OP_H

namespace termite
{
    enum class Op
    {
        NOP,
        // Memory management
        LDA,
        STA,
        LDX,
        STX,
        LDY,
        STY,
        // I/O
        IN,
        OUT,
        // Numerical operations
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
}

#endif