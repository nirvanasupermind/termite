// -*- vm/addr.cpp -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#include <string>
#include <cstdint>

#include "../core/trybble.h"
#include "addr.h"

namespace termite {
    Addr::Addr(const Trybble& hi, const Trybble& mid, const Trybble& lo)
        : hi(hi), mid(mid), lo(lo) {
    }

    uint16_t Addr::to_uint16() const {
        return hi.to_uint8() * 729 + mid.to_uint8() * 27 + lo.to_uint8();
    }    

    std::string Addr::to_ternary_str() const {
        return hi.to_ternary_str() + mid.to_ternary_str() + lo.to_ternary_str();
    }
} // namespace termite