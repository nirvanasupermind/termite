// -*- mem.hpp -*-
// Part of the Termite project, under the MIT License.

#ifndef MEM_HPP
#define MEM_HPP

#include <array>

#include "tryte.hpp"
#include "word.hpp"

namespace termite {
    // Represents the main memory of the VM
    class Mem {
    private:
        std::array<Tryte, 531441> data;
    public:
        // Default constructor
        Mem() = default;

        // Reads a tryte from memory
        Tryte read_tryte(const Word &addr) const;

        // Reads a word from memory
        Word read_word(const Word &addr) const;
        
        // Writes a tryte to memory
        void write_tryte(const Word &addr, const Tryte &val);
    };
} // namespace termite

#endif // MEM_HPP