// -*- cpu.hpp -*-
// Part of the Termite project, under the MIT License.

#ifndef CPU_HPP
#define CPU_HPP
#include <array>

#include "tryte.hpp"
#include "word.hpp"
#include "mem.hpp"
#include "opcodes.hpp"

namespace termite {
    class CPU {
    private:    
        // Sign flag
        unsigned int s_flag : 2;

        // Overflow flag
        unsigned int v_flag : 2;  

        // Carry flag
        unsigned int c_flag : 2;
    public:
        // An array of general-purpose registers, including the stack pointer and program counter
        std::array<Word, 27> register_file;

        Mem mem;
        
        // Default constructor
        CPU();

        // Debugs the state of the CPU
        void debug();

        // Resets the state of the CPU
        void reset();

        // Increments the program counter
        void inc_pc();

        // Increments the program counter twice
        void inc2_pc();

        // Fetches a tryte from memory
        Tryte fetch_tryte();

        // Fetches a word from memory
        Word fetch_word();

        // Decodes an opcode
        Opcode decode_opcode(const Tryte &tryte) const;

        // Executes a stream of instructions from memory
        void execute();
    };
} // namespace termite

#endif // CPU_HPP