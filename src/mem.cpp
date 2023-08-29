#include <vector>

#include "tryte.h"
#include "word.h"
#include "mem.h"


namespace termite {
    Mem::Mem() {
        reset();
    }

    void Mem::reset() {
        data = std::vector<Tryte>(MAX_MEM, Tryte());
    }

    Tryte Mem::get_tryte(const Word& addr) const {
        int idx = addr.to_int32()  + (MAX_MEM >> 1);;
        return data.at(idx);
    }

    void Mem::set_tryte(const Word& addr, const Tryte& tryte) {
        int32_t idx = addr.to_int32() + (MAX_MEM >> 1);
        data[idx] = tryte;
    }

    Word Mem::get_word(const Word& addr) const {
        int32_t idx = addr.to_int32() + (MAX_MEM >> 1);
        Tryte lo_tryte = data.at(idx);
        Tryte hi_tryte = data.at(idx + 1);
        return Word(lo_tryte, hi_tryte);
    }
    
    void Mem::set_word(const Word& addr, const Word& word) {
        int32_t idx = addr.to_int32() + (MAX_MEM >> 1);
        data[idx] = word.get_lo_tryte();
        data[idx + 1] = word.get_hi_tryte();
    }
} // namespace termite