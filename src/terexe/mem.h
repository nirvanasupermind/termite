#ifndef MEM_H
#define MEM_H

#include <array>
#include "../core/tryte.h"
#include "../core/word.h"

namespace termite
{
    // 531,441 trytes of random-access memory used by the VM
    class Mem {
    public:
        static const int MAX_MEM = 531441;
        std::array<Tryte, MAX_MEM> data{};
        Mem() = default;

        // Reads a word from memory
        Word read_word(int addr) const;

        // Writes a word to memory
        void write_word(int addr, const Word& val);        
    };
} // namespace termite

#endif // MEM_H