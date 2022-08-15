// -*- cpu/addr.cpp -*-
// Part of the Termite project
// Usage permitted under terms of MIT license

#include <string>
#include <cstdint>

#include "../core/tryte.h"
#include "addr.h"

namespace termite {
    Addr::Addr(const Tryte& hi, const Tryte& lo)
        : hi(hi), lo(lo) {
    }

    uint32_t Addr::to_uint32() const {
        return hi.to_uint16() * 729 + lo.to_uint16();
    }    

    std::string Addr::to_ternary_str() const {
        return hi.to_ternary_str() + lo.to_ternary_str();
    }
} // namespace termite