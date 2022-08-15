// -*- cpu/op.h -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#ifndef OP_H
#define OP_H

namespace termite {
    // Represents an operation type.
    enum class Op {
        NOP,
        INT,
        LD,
        LDV,
        ST,
        STV,
        ADD,
        SUB,
        MUL,
        MULU,
        DIV,
        DIVU,
        NOT,
        AND,
        OR,
        XOR,
        JMP,
        JEQ,
        JNE,
        JLT,
        JGT,
        JLE,
        JGE
    };
}

#endif // OP_H