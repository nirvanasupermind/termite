#include <string>
#include <cinttypes>

#include "util.hpp"
#include "trybble.hpp"
#include "tables.hpp"

namespace termite {
    Trybble::Trybble(FromBCT, uint8_t bct)
        : bct(bct) {
    }

    Trybble::Trybble(int8_t num) {
        try {
            bct = INT_TO_BCT_TRYBBLE.at(num);
        }
        catch (const std::exception& e) {
            throw std::runtime_error("[termite] out-of-range number " + std::to_string(num) + " in Trybble:Trybble");
        }
    }

    uint8_t Trybble::get_bct() const {
        return bct;
    }

    int8_t Trybble::to_int() const {
        try {
            return BCT_TRYBBLE_TO_INT.at(bct);
        }
        catch (const std::exception& e) {
            throw std::runtime_error("[termite] invalid BCT encoding in Trybble::to_int");
        }
    }

    std::string Trybble::to_ternary_str() const {
        try {
            return BCT_TRYBBLE_TO_TERNARY_STR.at(bct);
        }
        catch (const std::exception& e) {
            throw std::runtime_error("[termite] invalid BCT encoding in Trybble::to_ternary_str");
        }
    }

    char Trybble::to_sept_digit() const {
        try {
            return BCT_TRYBBLE_TO_SEPT_DIGIT.at(bct);
        } catch (const std::exception& e) {
            throw std::runtime_error("[termite] invalid BCT encoding in Trybble::to_sept_digit");
        }
    }
} // namespace termite