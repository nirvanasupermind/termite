// -*- vm/instr.h -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#ifndef INSTR_H
#define INSTR_H

#include <array>

#include "../core/tryte.h"

namespace termite {
    // All CPU instructions have a fixed width of 24 trits or 4 trytes in Termite's CPU architecture.
    class Instr {
    public:
        std::array<Tryte, 4> trytes;
        
        // Convert four BCT trytes to an instruction.
        Instr(const std::array<Tryte, 4> &trytes);
    };
}

#endif // INSTR_H