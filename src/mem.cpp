#include <fstream>
#include <iterator>
#include <vector>
#include <iostream>

#include "tryte.h"
#include "word.h"
#include "mem.h"


namespace termite {
    Mem::Mem() {
        initialize();
    }

    void Mem::initialize() {
        data = std::vector<Tryte>(Mem::MAX_MEM, Tryte());
    }

    Tryte Mem::get_tryte(const Word& addr) const {
        int idx = addr.to_int32() + (Mem::MAX_MEM >> 1);;
        return data.at(idx);
    }

    void Mem::set_tryte(const Word& addr, const Tryte& tryte) {
        int32_t idx = addr.to_int32() + (Mem::MAX_MEM >> 1);
        data[idx] = tryte;
    }

    Word Mem::get_word(const Word& addr) const {
        int32_t idx = addr.to_int32() + (Mem::MAX_MEM >> 1);
        Tryte lo_tryte = data.at(idx);
        Tryte hi_tryte = data.at(idx + 1);
        return Word(lo_tryte, hi_tryte);
    }

    void Mem::set_word(const Word& addr, const Word& word) {
        int32_t idx = addr.to_int32() + (Mem::MAX_MEM >> 1);
        data[idx] = word.get_lo_tryte();
        data[idx + 1] = word.get_hi_tryte();
    }

    void Mem::load_bct_file(const std::string& filename) {
        std::ifstream input(filename, std::ios::binary);

        std::vector<char> bytes(
            (std::istreambuf_iterator<char>(input)),
            (std::istreambuf_iterator<char>()));

        input.close();

        for(int i = 0; i < bytes.size(); i += 2) {
            uint8_t lo_4_trits_bct = (uint8_t)bytes.at(i);
            uint8_t hi_4_trits_bct = (uint8_t)bytes.at(i + 1);
            set_tryte(Word::from_int32((i >> 1) - (Mem::MAX_MEM >> 1)), Tryte(lo_4_trits_bct + (hi_4_trits_bct << 8)));
        }
    }
} // namespace termite