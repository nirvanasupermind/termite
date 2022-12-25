#include <cinttypes>
#include <string>
#include "trit.h"
#include "tryte.h"
#include "tables.h"

namespace termite {
    Tryte::Tryte(uint32_t bct)
        : bct(bct) {
    }

    Tryte Tryte::from_int(int val) {
        if (val < 0) {
            return Tryte::from_int(Tryte::MAX + val);
        }
        else {
            Tryte result;
            for (int i = 0; i < 6; i++) {
                result.set_trit(i, Trit(val % 3));
                val /= 3;
            }
            return result;
        }
    }

    Trit Tryte::get_trit(int i) const {
        return Trit((bct >> (i * 2)) & 3);
    }

    void Tryte::set_trit(int i, const Trit& val) {
        uint16_t bitmask = -(3 * (1 << (i * 2)) + 1);
        bct = (bct & bitmask) + (val.to_int() << (i * 2));
    }

    int Tryte::to_int() const {
        int result = 0;

        for (int i = 0; i < 6; i++) {
            result += get_trit(i).to_int() * POW3.at(i);
        }

        return result;
    }

    std::string Tryte::to_ter_string() const {
        std::string result;

        for (int i = 5; i >= 0; i--) {
            result += get_trit(5 - i).to_char();
        }

        return result;
    }

    std::string Tryte::to_non_string() const {
        return std::to_string(to_int() / 81)
            + std::to_string((to_int() % 81) / 9)
            + std::to_string(to_int() / 9);
    }
} // namespace termite