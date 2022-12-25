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
        Word psw{};
        std::array<Word, 9> reg{};
        bool running;
    public:
        static const int SP = 7;
        static const int PC = 8;   
        Mem mem{};     
        VM();

        // Sets the sign flag
        void set_sign_flag(const Word& word);

        // Resets the VM
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