#include <array>
#include <exception>

#include "tryte.hpp"
#include "word.hpp"
#include "mem.hpp"

namespace termite {
    Tryte Mem::read_tryte(const Word &addr) const {
        try {
            return data.at(addr.to_u32());
        } catch(const std::exception &e) {
            throw std::runtime_error("[termite] memory error");
        }
    }

    Word Mem::read_word(const Word &addr) const {
        u32 u32_addr = addr.to_u32();

        try {
            return Word(data.at(u32_addr), data.at(u32_addr + 1));
        } catch(const std::exception &e) {
            throw std::runtime_error("[termite] memory error");
        }
    }

    void Mem::write_tryte(const Word &addr, const Tryte &val) {
        try {
            data[addr.to_u32()] = val;
        } catch(const std::exception &e) {
            throw std::runtime_error("[termite] memory error");
        }
    }
}