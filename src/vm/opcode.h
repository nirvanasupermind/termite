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
        SYSCALL,
        ADD,
        SUB,
        ADDI,
        MUL,
        MULU,
        DIV,
        MOD,
        AND,
        OR,
        ANDI,
        ORI,
        LUI,
        LT,
        LH,
        LW,
        LTU,
        LHU,
        ST,
        SH,
        SW
    };
}

#endif // OPCODE_H