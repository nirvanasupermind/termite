#include <array>
#include <exception>

#include "typedefs.hpp"
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
        u32 idx = addr.to_u32();

        if(idx >= MAX_MEM) {
            throw std::runtime_error("[termite] memory address out of bounds: " + addr.to_sept_str());
        }

        return data[idx];
    }

    Word Mem::read_word(const Word &addr) const {
        u32 idx = addr.to_u32();

        if(idx >= MAX_MEM) {
            throw std::runtime_error("[termite] memory address out of bounds: " + addr.to_sept_str());
        }
        
        return Word(data[idx], data[idx + 1]);
    }

    void Mem::write_tryte(const Word &addr, const Tryte &val) {
        try {
            data[addr.to_u32()] = val;
        } catch(const std::exception &e) {
            throw std::runtime_error("[termite] memory error");
        }
    }

    void Mem::write_word(const Word &addr, const Word &val) {
        u32 idx = addr.to_u32();


        try {
            data[idx] = val.get_hi();
            data[idx + 1] = val.get_lo();
        } catch(const std::exception &e) {
            throw std::runtime_error("[termite] memory error");
        }
    }
}