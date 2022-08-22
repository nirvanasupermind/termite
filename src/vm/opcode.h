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

    };
}

#endif // OPCODE_H