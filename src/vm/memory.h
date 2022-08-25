// -*- vm/memory.h -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#ifndef MEMORY_H
#define MEMORY_H

#include <array>

#include "../core/tryte.h"
#include "addr.h"

namespace termite {
    // The random-access memory consists of 3^18 = 387420489 1-tryte memory registers.
    class Memory {
    protected:
        // Internal array of trytes.
        std::array<Tryte, 387420489> data;
    public:
        // Initializes the memory with all registers set to 0.
        Memory() = default;

        // Loads the value from memory.
        Tryte load(const Addr &addr) const;

        // Copies a values to memory.
        Tryte store(const Addr &addr, const Tryte &val);
    };
}

#endif // MEMORY_H