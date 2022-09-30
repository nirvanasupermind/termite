// -*- trybble.cpp -*-
// Part of the Termite project, under the MIT License.

#include <string>
#include <cinttypes>
#include <exception>
#include <stdexcept>

#include "typedefs.hpp"
#include "tables.hpp"
#include "trybble.hpp"

namespace termite {
    Trybble::Trybble()  
        : bct(0) {
    }

    Trybble::Trybble(u8 bct)
        : bct(bct) {
    }

    Trybble Trybble::from_i8(i8 num) {
        if (num < 0) {
            return Trybble::from_u8(num + 27);
        }

        return Trybble::from_u8(num);
    }

    Trybble Trybble::from_u8(u8 num) {
        try {
            return Trybble(U8_TO_BCT_TRYBBLE.at(num));
        }
        catch (const std::exception& e) {
            throw std::runtime_error("[termite] unhandled number in Trybble::from_u8");
        }
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

    u8 Trybble::get_bct() const {
        return bct;
    }

    i8 Trybble::to_i8() const {
        i8 result = to_u8();

        if (result > 13) {
            return result - 27;
        }

        return result;
    }

    u8 Trybble::to_u8() const {
        try {
            return BCT_TRYBBLE_TO_U8.at(bct);
        }
        catch (const std::exception& e) {
            throw std::runtime_error("[termite] unhandled BCT trybble in Trybble::to_u8");
        }
    }


    std::string Trybble::to_ternary_str() const {
        try {
            return BCT_TRYBBLE_TO_TERNARY_STR.at(bct);
        }
        catch (const std::exception& e) {
            throw std::runtime_error("[termite] unhandled BCT trybble in Trybble::to_ternary_str");
        }
    }

    char Trybble::to_sept_char() const {
        try {
            return BCT_TRYBBLE_TO_SEPT_CHAR.at(bct);
        }
        catch (const std::exception& e) {
            throw std::runtime_error("[termite] unhandled BCT trybble in Trybble::to_sept_char");
        }
    }


} // namespace termite