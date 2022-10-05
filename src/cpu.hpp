// -*- cpu.hpp -*-
// Part of the Termite project, under the MIT License.

#ifndef CPU_HPP
#define CPU_HPP
#include <array>

#include "typedefs.hpp"
#include "tryte.hpp"
#include "word.hpp"
#include "mem.hpp"
#include "opcodes.hpp"

namespace termite {
    class CPU {
    private:    
        // Sign flag
        u8 s_flag : 2;

        // Overflow flag
        u8 v_flag : 2;  

        // Carry flag
        u8 c_flag : 2;
    public:
        std::array<Word, 27> register_file;

        Mem mem;
        
        // Default constructor
        CPU();

        // void debug();
        void reset();

        // Increments the progmem counter
        void inc_pc();

        // Increments the progmem counter twice
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