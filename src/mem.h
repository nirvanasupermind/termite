#ifndef MEM_H
#define MEM_H

#include <vector>

#include "tryte.h"
#include "word.h"

namespace termite {
    const int MAX_MEM = 43046721;
    class Mem {
    protected:
        std::vector<Tryte> data;
    public:
        Mem();
        void reset();
        Tryte get_tryte(const Word& addr) const;
        void set_tryte(const Word& addr, const Tryte& tryte);
        Word get_word(const Word& addr) const;
        void set_word(const Word& addr, const Word& word);
    };
} // namespace termite

#endif
