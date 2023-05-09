// Class for the main memory
#ifndef MEM_H
#define MEM_H

#include <vector>
#include "tryte.h"
#include "word.h"

namespace termite {
    class Mem {
    public:
        // Using vector instead of array because trying to create 90 MB array gives segfault
        std::vector<Tryte> data;
        Mem();
        Tryte get_tryte(const Word& addr);
        void set_tryte(const Word& addr, const Tryte& tryte);
        Word get_word(const Word& addr);
        void set_word(const Word& addr, const Word& word);
    };
} // namespace termite

#endif // MEM_H