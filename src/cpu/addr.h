// -*- cpu/addr.h -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#ifndef ADDR_H
#define ADDR_H

#include <cstdint>

#include "../core/tryte.h"

namespace termite {
    // A memory address is 2 trytes wide in Termite's CPU architecture.

    class Addr {
    public:
        Tryte hi;

        Tryte lo;
        
        // Convert two BCT trytes to a BCT address.
        Addr(const Tryte& hi, const Tryte& lo);
    
        // Converts the BCT address to a native uint32.
        uint32_t to_uint32() const;

        // Converts the BCT address to a ternary string.
        std::string to_ternary_str() const;
    };
}

#endif // ADDR_H