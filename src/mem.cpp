#include <array>
#include <exception>

#include "tryte.hpp"
#include "word.hpp"
#include "mem.hpp"

namespace termite {
    Mem::Mem() {
        reset();
    }

    void Mem::reset() {
        std::fill(std::begin(data), std::end(data), Tryte::ZERO);
    }

    Tryte Mem::read_tryte(const Word &addr) const {
        int idx = static_cast<int>(addr);

        if(idx >= MAX_MEM) {
            throw std::runtime_error("[termite] memory address out of bounds: " + static_cast<std::string>(addr));
        }

        return data[idx];
    }

    Word Mem::read_word(const Word &addr) const {
        int idx = static_cast<int>(addr);

        if(idx >= MAX_MEM) {
            throw std::runtime_error("[termite] memory address out of bounds: " + static_cast<std::string>(addr));
        }
        
        return Word(data[idx], data[idx + 1]);
    }

    void Mem::write_tryte(const Word &addr, const Tryte &val) {
        int idx = static_cast<int>(addr);

        if(idx >= MAX_MEM) {
            throw std::runtime_error("[termite] memory address out of bounds: " + static_cast<std::string>(addr));
        }

        data[idx] = val;
    }

    void Mem::write_word(const Word &addr, const Word &val) {
        int idx = static_cast<int>(addr);

        if(idx >= MAX_MEM - 1) {
            throw std::runtime_error("[termite] memory address out of bounds: " + static_cast<std::string>(addr));
        }

        data[idx] = val.get_hi();
        data[idx + 1] = val.get_lo();
    }
}