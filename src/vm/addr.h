// -*- vm/addr.h -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#ifndef ADDR_H
#define ADDR_H

#include <cstdint>

#include "../core/trybble.h"

namespace termite {
    // A memory address is 9 trits wide in Termite's architecture.

    class Addr {
    public:
        Trybble hi;

        Trybble mid;

        Trybble lo;
        
        // Convert two BCT trytes to a BCT address.
        Addr(const Trybble& hi, const Trybble& mid, const Trybble& lo);
    
        // Converts the memory address to a native uint16.
        uint16_t to_uint16() const;

        // Converts the memory address to a ternary string.
        std::string to_ternary_str() const;
    };
}

#endif // ADDR_H