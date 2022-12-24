#ifndef VM_H
#define VM_H

#include <array>
#include "tryte.h"
#include "word.h"
#include "mem.h"

namespace termite
{
    // Termite virtual machine
    class VM {
    private:
    public:
        Mem mem{};
        Word psw{};
        std::array<Word, 9> reg{};
        static const int SP = 7;
        static const int PC = 8;        
        VM();
        void reset();

        // Fetches a tryte from memory
        Tryte fetch_tryte();
        
        // Fetches a word from memory
        Word fetch_word();

        // Executes an instruction
        void step();

        // Calls step() in a loop
        void run();
    };
} // namespace termite

#endif // MEM_H