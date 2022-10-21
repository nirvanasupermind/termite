// -*- vm.cpp -*-
// Part of the Termite project, under the MIT License.

#include <cassert>

#include "opcodes.hpp"
#include "trybble.hpp"
#include "tryte.hpp"
#include "word.hpp"
#include "vm.hpp"

namespace termite {
    void VM::assert_register_val(size_t idx, int expected_val) const {
        assert(static_cast<int>(registers[idx]) == expected_val);
    }

    Tryte VM::fetch_tryte() {
        Tryte tryte = mem[registers[VM::PC]];
        ++registers[VM::PC];
        return tryte;
    }

    Word VM::fetch_word() {
        Tryte hi = mem[registers[VM::PC]];
        ++registers[VM::PC];
        Tryte lo = mem[registers[VM::PC]];
        ++registers[VM::PC];
        Word word = Word(hi, lo);
        return word;
    }

    Word VM::read_word(const Word &addr) {
        Tryte hi = mem[registers[addr]];
        Tryte lo = mem[registers[addr + Word::ONE]];
        Word word = Word(hi, lo);
        return word;
    }

    void VM::write_word(const Word &addr, const Word &val) {
        mem[addr] = val.get_hi();
        mem[addr + Word::ONE] = val.get_lo();
    }

    void VM::step() {
        Tryte opcode = fetch_tryte();

        switch (static_cast<int>(opcode)) {
        case NOP:
            break;
        case HLT:
            exit(EXIT_SUCCESS);
        case MOV_ABS_IMM: {
            Word dest_addr = fetch_word();
            Word src = fetch_word();
            write_word(dest_addr, src);
            break;
        }
        case MOV_ABS_ABS: {
            Word dest_addr = fetch_word();
            Word src_addr = fetch_word();
            write_word(dest_addr, read_word(src_addr));
            break;
        }
        case MOV_ABS_REG: {
            Word dest_addr = fetch_word();
            Trybble src_idx = fetch_tryte().get_lo();
            write_word(dest_addr, registers[src_idx]);
            break;
        }
        case MOV_REG_IMM: {
            Trybble dest_idx = fetch_tryte().get_lo();
            Word src = fetch_word();
            registers[dest_idx] = src;
            break;
        }
        case MOV_REG_ABS: {
            Trybble dest_idx = fetch_tryte().get_lo();
            Word src_addr = fetch_word();
            registers[dest_idx] = read_word(src_addr); 
            break;
        }
        case MOV_REG_REG: {
            Tryte tryte = fetch_tryte();
            Trybble dest_idx = tryte.get_hi();
            Trybble src_idx = tryte.get_lo();
            registers[dest_idx] = registers[src_idx];
            break;
        }
        }
    }


    void VM::run() {
        while(true) {
            step();
        }
    }
} // namespace termite