// #include <iostream>
#include <vector>
#include "tryte.h"
#include "word.h"
#include "mem.h"


namespace termite {
    Mem::Mem()
        : data(std::vector<Word>(WORD_MAX)) {
    }

    Word Mem::get_tryte(const Word& addr) {
        int idx = addr.to_int32();
        return data.at(idx);
    }

    void Mem::set_tryte(const Word& addr, const Word& tryte) {
        int idx = addr.to_int32();
        data[idx] = tryte;
    }

    Word Mem::get_word(const Word& addr) {
        int idx = addr.to_int32();
        Word lo_tryte = data.at(idx);
        Word hi_tryte = data.at(idx + 1);
        return Word((hi_tryte.bct << 16) + lo_tryte.bct);
    }
    
    void Mem::set_word(const Word& addr, const Word& word) {
        int idx = addr.to_int32();
        data[idx] = word.lo_tryte();
        data[idx + 1] = word.hi_tryte();
    }
} // namespace termite