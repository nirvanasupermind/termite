// -*- cpu/instr.cpp -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#include <array>

#include "../core/tryte.h"
#include "instr.h"

namespace termite {
    Instr::Instr(const std::array<Tryte, 4> &trytes)
        : trytes(trytes) {
    }
} // namespace termite