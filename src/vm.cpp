// -*- vm.cpp -*-
// Part of the Termite project, under the MIT License.

#include <cassert>

#include "opcodes.hpp"
#include "trybble.hpp"
#include "tryte.hpp"
#include "word.hpp"
#include "vm.hpp"

namespace termite {
    void VM::assert_register_val(size_t idx, unsigned int expected_val) const {
        assert(static_cast<unsigned int>(registers[idx]) == expected_val);
    }

    Tryte VM::fetch_tryte() {
        Tryte tryte = mem[registers[VM::pc_idx]];
        ++registers[VM::pc_idx];
        return tryte;
    }

    Word VM::fetch_word() {
        Tryte hi = mem[registers[VM::pc_idx]];
        ++registers[VM::pc_idx];
        Tryte lo = mem[registers[VM::pc_idx]];
        ++registers[VM::pc_idx];
        Word word = Word(hi, lo);
        return word;
    }

    void VM::cycle() {
        Tryte opcode = fetch_tryte();

        switch (static_cast<unsigned int>(opcode)) {
        case NOP:
            break;
        case HLT:
            exit(EXIT_SUCCESS);
        case MOV_ABS_ABS: {
            Word dest_addr = fetch_word();
            Word src_addr = fetch_word();
            unsigned int dest_idx = static_cast<unsigned int>(dest_addr);
            unsigned int src_idx = static_cast<unsigned int>(src_addr);
            mem[dest_idx] = mem[src_idx];
            mem[dest_idx + 1] = mem[src_idx + 1];
            break;
        }
        case MOV_ABS_IMM: {
            Word dest_addr = fetch_word();
            Word src = fetch_word();
            unsigned int dest_idx = static_cast<unsigned int>(dest_addr);
            mem[dest_idx] = src.get_hi();
            mem[dest_idx + 1] = src.get_lo();
            break;
        }
        case MOV_ABS_REG: {
            Word dest_addr = fetch_word();
            Trybble src_addr = fetch_tryte().get_lo();
            unsigned int dest_idx = static_cast<unsigned int>(dest_addr);
            unsigned int src_idx = static_cast<unsigned int>(src_addr);
            Word src = registers[src_idx];
            mem[dest_idx] = src.get_hi();
            mem[dest_idx + 1] = src.get_lo();
            break;
        }
        }
    }

} // namespace termite