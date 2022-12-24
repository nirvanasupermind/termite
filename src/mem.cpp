#include "tryte.h"
#include "word.h"
#include "mem.h"

namespace termite {
    Word Mem::read_word(int addr) const {
        return Word::from_trytes(data.at(addr), data.at(addr + 1));
    }
    
    void Mem::write_word(int addr, const Word& val) {
        data[addr] = val.hi_tryte();
        data[addr + 1] = val.lo_tryte();
    }


} // namespace termite
