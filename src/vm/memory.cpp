// -*- vm/memory.cpp -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#include <array>

#include "../core/tryte.h"
#include "addr.h"
#include "memory.h"

namespace termite {
    Tryte Memory::load(const Addr &addr) const {
        return data.at(addr.to_uint32());
    }

    Tryte Memory::store(const Addr &addr, const Tryte &val) {
        data[addr.to_uint32()] = val;
    }
}