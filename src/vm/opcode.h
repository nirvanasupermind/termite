// -*- vm/opcode.h -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#ifndef OPCODE_H
#define OPCODE_H

#include <cstdint>

#include "../core/tryte.h"


namespace termite {
    // Specifies the operation to be performed in a CPU instruction.
    enum class Opcode {
        NOP,
        LT,
        LTV,
        ST,
        B,
        BEQ,
        BNE,
        BLT,
        BGT,
        BLE,
        BGE,
        CMP,
        SYS,
        ADD,
        SUB,
        MUL,
        UMUL,
        DIV,
        UDIV,
        NEG,
        AND,
        OR,
        XOR,
        NOT,
        LS,
        RS
    };
}

#endif // OPCODE_H