// -*- opcodes.hpp -*-
// Part of the Termite project, under the MIT License.

#ifndef OPCODES_HPP
#define OPCODES_HPP

#include "typedefs.hpp"

namespace termite {
    enum class Opcode : u16 {
        ADD,
        SUB,
        MUL,
        MULU,
        DIV,
        DIVU,
        MOD,
        MODU,
        SL,
        SR,
        SRU,
        AND,
        OR,
        XOR,
        NOT,
        CMP,
        LD,
        LI,
        LIU,
        ST,
        JMP,
        BR,
        BEQ,
        BNE,
        BLT,
        BGT,
        BLE,
        BGE,
        PUSH,
        POP,
        INT
    };
} // namespace termite

#endif // TRYTE_HPP