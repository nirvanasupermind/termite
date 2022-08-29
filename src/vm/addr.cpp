// -*- core/addr.cpp -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#include <string>

#include "util.h"
#include "../core/tryte.h"
#include "addr.h"

namespace termite {
    Addr::Addr(const Tryte& hi, const Tryte &mid, const Tryte& lo)
        : hi(hi), mid(mid), lo(lo) {
        // assert(valid());
    }
} // namespace termite
