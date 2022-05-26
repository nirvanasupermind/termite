#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "tryte.h"

namespace termite
{
    // Represents the type of an instruction executed by the virtual CPU
    enum class InstrOp
    {
        NOP,
        // Stack
        PUSH,
        POP,
        SWAP,
        SYSCALL,
        // Arithmetic
        ADD,
        SUB,
        MUL,
        NEG,
        // Logical
        AND,
        OR,
        XOR,
        NOT
    }; 

    // An instruction (executed by the virtual CPU) contain two trytes, one for the opcode being performed,
    // and one for any extra information (such as the tryte to be pushed to stack in a "PUSH" operation).


    class Instr
    {
    public:
        InstrOp op;
        Tryte val;

        Instr(InstrOp op);

        Instr(InstrOp op, Tryte val);
    };
}

#endif