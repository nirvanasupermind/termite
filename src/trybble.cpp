// -*- trybble.cpp -*-
// Part of the Termite project, under the MIT License.

#include <cinttypes>
#include <string>
#include <stdexcept>

#include "tables.hpp"
#include "trybble.hpp"
#include "util.hpp"

namespace termite {
    const Trybble Trybble::ZERO(native_int, 0);

    const Trybble Trybble::ONE(native_int, 1);

    const Trybble Trybble::TWO(native_int, 2);

    Trybble::Trybble()
        : bct(0) {
    }

    Trybble::Trybble(uint8_t bct)
        : bct(bct) {
    }

    Trybble::Trybble(NativeInt, int num)
        : bct(NATIVE_INT_TO_BCT_TRYBBLE.at(num)) {
    }

    Trybble::Trybble(Sept, const std::string& str)
        : bct(SEPT_STR_TO_BCT_TRYBBLE.at(str)) {
    }

    Trybble Trybble::operator&(const Trybble& other) const {
        try {
            return Trybble(BCT_TRYBBLE_AND.at(bct).at(other.bct));
        }
        catch (const std::exception& e) {
            throw std::runtime_error("[termite] unhandled BCT trybble in Trybble::operator&");
        }
    }

    Trybble Trybble::operator|(const Trybble& other) const {
        try {
            return Trybble(BCT_TRYBBLE_OR.at(bct).at(other.bct));
        }
        catch (const std::exception& e) {
            throw std::runtime_error("[termite] unhandled BCT trybble in Trybble::operator&");
        }
    }

    Trybble Trybble::operator^(const Trybble& other) const {
        try {
            return Trybble(BCT_TRYBBLE_XOR.at(bct).at(other.bct));
        }
        catch (const std::exception& e) {
            throw std::runtime_error("[termite] unhandled BCT trybble in Trybble::operator&");
        }
    }

    Trybble Trybble::operator~() const {
        return Trybble(0b10'10'10 - bct);
    }

    uint8_t Trybble::get_bct() const {
        return bct;
    }

    Trybble::operator int() const {
        try {
            return BCT_TRYBBLE_TO_NATIVE_INT.at(bct);
        }
        catch (const std::exception& e) {
            throw std::runtime_error("[termite] unhandled BCT trybble in Trybble::to_u8");
        }
    }

    Trybble::operator std::string() const {
        try {
            return BCT_TRYBBLE_TO_SEPT_STR.at(bct);
        }
        catch (const std::exception& e) {
            throw std::runtime_error("[termite] unhandled BCT trybble in Trybble::to_ternary_str");
        }
    }

} // namespace termite