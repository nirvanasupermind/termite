// -*- vm.hpp -*-
// Part of the Termite project, under the MIT License.

#ifndef VM_HPP
#define VM_HPP

#include <string>
#include <array>

#include "opcodes.hpp"
#include "trybble.hpp"
#include "word.hpp"

namespace termite {
    // Represents an instance of the Termite virtual machine
    class VM {
    private:
        std::array<Word, 27> registers;
        std::array<Tryte, 531441> mem;
        std::array<char, 3> flags;
    public:
        // Carry flag
        static const size_t S = 0;

        // Overflow flag
        static const size_t V = 2;

        // Carry flag
        static const size_t C = 2;

        // Stack pointer r25
        static const size_t SP = 25;

        // Program counter r26
        static const size_t PC = 26;

        // Assert the value of a register, only used for testing
        void assert_register_val(size_t idx, int expected_val) const;

        // Reads a word from memory
        Word read_word(const Word &addr);

        // Writes a word to memory
        void write_word(const Word &addr, const Word &val);

        // Fetches a tryte
        Tryte fetch_tryte();

        // Fetches a word
        Word fetch_word();

        // Executes an instruction
        void step();

        void run();

    };
} // namespace termite

#endif // VM_HPP