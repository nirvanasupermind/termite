// -*- core/addr.h -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#ifndef ADDR_H
#define ADDR_H

#include <string>
#include <cstdint>

#include "util.h"
#include "../core/tryte.h"

namespace termite {
    // An address is 18 trits wide in Termite's CPU architecture.

    class Addr {
    public:
        Tryte hi;

        Tryte mid;

        Tryte lo;

        // Creates a BCT address equal to 0.
        Addr() = default;

        // Convert three BCT trybbles to a BCT address.
        Addr(const Tryte& hi, const Tryte &mid, const Tryte& lo); 
    };
} // namespace termite

#endif // ADDR_H