
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
        std::string str() const;
    };
} // namespace termite

#endif
