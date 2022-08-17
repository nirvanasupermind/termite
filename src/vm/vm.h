// -*- vm/vm.h -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#include <cstdint>

#ifndef OP_H
#define OP_H

namespace termite {
    // Represents the operation to be performed in an instruction.
    class Opcode {
    public:
        uint8_t val;
         
        // NOP
        // INT,
        // LD,
        // LDV,
        // ST,
        // STV,
        // ADD,
        // SUB,
        // MUL,
        // MULU,
        // DIV,
        // DIVU,
        // NOT,
        // AND,
        // OR,
        // XOR,
        // JMP,
        // JEQ,
        // JNE,
        // JLT,
        // JGT,
        // JLE,
        // JGE
    };
}

#endif // OP_H