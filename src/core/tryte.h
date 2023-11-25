
#ifndef TRYTE_H
#define TRYTE_H

#include <cstdint>
#include <string>

namespace termite {
    const int TRITS_PER_TRYTE = 8;
    class Tryte {
    protected:
        uint16_t bct;
    public:
        Tryte();
        Tryte(uint16_t bct);
        uint16_t get_bct() const;
        uint8_t get_bct_trit(int i) const;
        void set_bct_trit(int i, uint8_t val);
        // NOT is also same as negation
        Tryte operator~() const;
        int16_t to_int16() const;
        std::string to_ternary_str() const;
        wchar_t to_wchar() const;
        static Tryte from_int16(int16_t n);
        static Tryte from_wchar(wchar_t wc);


    };
} // namespace termite

#endif
