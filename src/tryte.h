#include <cstdint>

namespace termite {
    class Tryte {
    protected:
        uint16_t bct;
    public:
        Tryte();
        Tryte(uint16_t bct);
        uint16_t get_bct() const;
        uint8_t get_trit(int i) const;
        // uint8_t set_trit(int i, uint8_t val) const;
    };

} // namespace termite
