// -*- vm.hpp -*-
// Part of the Termite project, under the MIT License.

#ifndef VM_HPP
#define VM_HPP

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
    public:
        // Stack pointer r25
        static const size_t sp_idx = 25;

        // Program counter r26
        static const size_t pc_idx = 26;

        // Assert the value of a register, only used for testing
        void assert_register_val(size_t idx, unsigned int expected_val) const;

        // Fetches a tryte
        Tryte fetch_tryte();

        // Fetches a word
        Word fetch_word();

        // Executes an instruction
        void cycle();

    };
} // namespace termite

#endif // VM_HPP