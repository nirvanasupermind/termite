#include <array>
#include <exception>
#include <iostream>

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
        u32 u32_addr = addr.to_u32();

        if(u32_addr >= MAX_MEM) {
            throw std::runtime_error("[termite] memory address out of bounds: " + addr.to_sept_str());
        }

        return data.at(u32_addr);
    }

    Word Mem::read_word(const Word &addr) const {
        u32 u32_addr = addr.to_u32();

        if(u32_addr >= MAX_MEM - 1) {
            throw std::runtime_error("[termite] memory address out of bounds: " + addr.to_sept_str());
        }
        
        return Word(data[u32_addr], data[u32_addr + 1]);
    }

    void Mem::write_tryte(const Word &addr, const Tryte &val) {
        try {
            data[addr.to_u32()] = val;
        } catch(const std::exception &e) {
            throw std::runtime_error("[termite] memory error");
        }
    }

    void Mem::write_word(const Word &addr, const Word &val) {
        u32 u32_addr = addr.to_u32();

        try {
            data[u32_addr] = val.get_hi();
            data[u32_addr + 1] = val.get_lo();
        } catch(const std::exception &e) {
            throw std::runtime_error("[termite] memory error");
        }
    }
}