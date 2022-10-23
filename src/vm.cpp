// -*- vm.cpp -*-
// Part of the Termite project, under the MIT License.

#include <array>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "util.hpp"
#include "opcodes.hpp"
#include "trybble.hpp"
#include "tryte.hpp"
#include "word.hpp"
#include "vm.hpp"

namespace termite {
    VM::VM() {
        clear();
    }

    void VM::assert_register_val(size_t idx, int expected_val) const {
        assert(static_cast<int>(registers[idx]) == expected_val);
    }

    void VM::display_state() const {
        for (size_t i = 0; i < registers.size(); i += 3) {
            if (i == 24) {
                std::cout << "r24 = " << registers[24] << ' ';
                std::cout << "sp = " << registers[25] << ' ';
                std::cout << "pc = " << registers[26] << '\n';
            }
            else {
                std::cout << 'r' << i << " = " << registers[i] << ' ';
                std::cout << 'r' << i + 1 << " = " << registers[i + 1] << ' ';
                std::cout << 'r' << i + 2 << " = " << registers[i + 2] << '\n';
            }
        }

        std::cout << '\n';

        for (size_t i = 19683; i < 19737; i += 3) {
            std::string sept_i = static_cast<std::string>(Word(native_int, i));
            std::string sept_i_1 = static_cast<std::string>(Word(native_int, i + 1));
            std::string sept_i_2 = static_cast<std::string>(Word(native_int, i + 2));

            std::cout << "0s" << sept_i << " = " << mem[i] << ' ';
            std::cout << "0s" << sept_i_1 << " = " << mem[i + 1] << ' ';
            std::cout << "0s" << sept_i_2 << " = " << mem[i + 2] << '\n';
        }

        std::cout << '\n';
    }

    void VM::clear() {
        memset(&mem, 0x00, 1062882);
        memset(&registers, 0x00, 108);
    }

    void VM::load_machine_code(const std::vector<std::string>& code) {
        for (size_t i = 0; i < code.size(); i++) {
            mem[i] = Tryte(sept, code.at(i));
        }
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

    Word VM::read_word(const Word& addr) {
        Tryte hi = mem[addr];
        Tryte lo = mem[addr + Word::ONE];
        Word word = Word(hi, lo);
        return word;
    }

    void VM::write_word(const Word& addr, const Word& val) {

        mem[addr] = val.get_hi();
        mem[addr + Word::ONE] = val.get_lo();
    }

    void VM::step(bool verbose) {
        if (verbose) {
            display_state();
            std::cout << "*** EXECUTED INSTRUCTION @0s" << static_cast<std::string>(registers[VM::PC]) << "\n\n";
        }

        Tryte opcode = fetch_tryte();

        switch (static_cast<int>(opcode)) {
        case NOP: {
            break;
        }
        case HLT: {
            running = false;
            break;
        }
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
        case ADD_ABS_IMM: {
            Word dest_addr = fetch_word();
            Word src = fetch_word();
            write_word(dest_addr, read_word(dest_addr) + src);
            break;
        }
        case ADD_ABS_ABS: {
            Word dest_addr = fetch_word();
            Word src_addr = fetch_word();
            write_word(dest_addr, read_word(dest_addr) + read_word(src_addr));
            break;
        }
        case ADD_ABS_REG: {
            Word dest_addr = fetch_word();
            Trybble src_idx = fetch_tryte().get_lo();
            write_word(dest_addr, read_word(dest_addr) + registers[src_idx]);
            break;
        }
        case ADD_REG_IMM: {
            Trybble dest_idx = fetch_tryte().get_lo();
            Word src = fetch_word();
            registers[dest_idx] = registers[dest_idx] + src;
            break;
        }
        case ADD_REG_ABS: {
            Trybble dest_idx = fetch_tryte().get_lo();
            Word src_addr = fetch_word();
            registers[dest_idx] = registers[dest_idx] + read_word(src_addr);
            break;
        }
        case ADD_REG_REG: {
            Tryte tryte = fetch_tryte();
            Trybble dest_idx = tryte.get_hi();
            Trybble src_idx = tryte.get_lo();
            registers[dest_idx] = registers[dest_idx] + registers[src_idx];
            break;
        }
        case SUB_ABS_IMM: {
            Word dest_addr = fetch_word();
            Word src = fetch_word();
            write_word(dest_addr, read_word(dest_addr) - src);
            break;
        }
        case SUB_ABS_ABS: {
            Word dest_addr = fetch_word();
            Word src_addr = fetch_word();
            write_word(dest_addr, read_word(dest_addr) - read_word(src_addr));
            break;
        }
        case SUB_ABS_REG: {
            Word dest_addr = fetch_word();
            Trybble src_idx = fetch_tryte().get_lo();
            write_word(dest_addr, read_word(dest_addr) - registers[src_idx]);
            break;
        }
        case SUB_REG_IMM: {
            Trybble dest_idx = fetch_tryte().get_lo();
            Word src = fetch_word();
            registers[dest_idx] = registers[dest_idx] - src;
            break;
        }
        case SUB_REG_ABS: {
            Trybble dest_idx = fetch_tryte().get_lo();
            Word src_addr = fetch_word();
            registers[dest_idx] = registers[dest_idx] - read_word(src_addr);
            break;
        }
        case SUB_REG_REG: {
            Tryte tryte = fetch_tryte();
            Trybble dest_idx = tryte.get_hi();
            Trybble src_idx = tryte.get_lo();
            registers[dest_idx] = registers[dest_idx] - registers[src_idx];
            break;
        }
        case MUL_ABS_IMM: {
            Word dest_addr = fetch_word();
            Word src = fetch_word();
            write_word(dest_addr, read_word(dest_addr) * src);
            break;
        }
        case MUL_ABS_ABS: {
            Word dest_addr = fetch_word();
            Word src_addr = fetch_word();
            write_word(dest_addr, read_word(dest_addr) * read_word(src_addr));
            break;
        }
        case MUL_ABS_REG: {
            Word dest_addr = fetch_word();
            Trybble src_idx = fetch_tryte().get_lo();
            write_word(dest_addr, read_word(dest_addr) * registers[src_idx]);
            break;
        }
        case MUL_REG_IMM: {
            Trybble dest_idx = fetch_tryte().get_lo();
            Word src = fetch_word();
            registers[dest_idx] = registers[dest_idx] * src;
            break;
        }
        case MUL_REG_ABS: {
            Trybble dest_idx = fetch_tryte().get_lo();
            Word src_addr = fetch_word();
            registers[dest_idx] = registers[dest_idx] * read_word(src_addr);
            break;
        }
        case MUL_REG_REG: {
            Tryte tryte = fetch_tryte();
            Trybble dest_idx = tryte.get_hi();
            Trybble src_idx = tryte.get_lo();
            registers[dest_idx] = registers[dest_idx] * registers[src_idx];
            break;
        }
        case DIV_ABS_IMM: {
            Word dest_addr = fetch_word();
            Word src = fetch_word();
            write_word(dest_addr, read_word(dest_addr) / src);
            break;
        }
        case DIV_ABS_ABS: {
            Word dest_addr = fetch_word();
            Word src_addr = fetch_word();
            write_word(dest_addr, read_word(dest_addr) / read_word(src_addr));
            break;
        }
        case DIV_ABS_REG: {
            Word dest_addr = fetch_word();
            Trybble src_idx = fetch_tryte().get_lo();
            write_word(dest_addr, read_word(dest_addr) / registers[src_idx]);
            break;
        }
        case DIV_REG_IMM: {
            Trybble dest_idx = fetch_tryte().get_lo();
            Word src = fetch_word();
            registers[dest_idx] = registers[dest_idx] / src;
            break;
        }
        case DIV_REG_ABS: {
            Trybble dest_idx = fetch_tryte().get_lo();
            Word src_addr = fetch_word();
            registers[dest_idx] = registers[dest_idx] / read_word(src_addr);
            break;
        }
        case DIV_REG_REG: {
            Tryte tryte = fetch_tryte();
            Trybble dest_idx = tryte.get_hi();
            Trybble src_idx = tryte.get_lo();
            registers[dest_idx] = registers[dest_idx] / registers[src_idx];
            break;
        }
        case MOD_ABS_IMM: {
            Word dest_addr = fetch_word();
            Word src = fetch_word();
            write_word(dest_addr, read_word(dest_addr) % src);
            break;
        }
        case MOD_ABS_ABS: {
            Word dest_addr = fetch_word();
            Word src_addr = fetch_word();
            write_word(dest_addr, read_word(dest_addr) % read_word(src_addr));
            break;
        }
        case MOD_ABS_REG: {
            Word dest_addr = fetch_word();
            Trybble src_idx = fetch_tryte().get_lo();
            write_word(dest_addr, read_word(dest_addr) % registers[src_idx]);
            break;
        }
        case MOD_REG_IMM: {
            Trybble dest_idx = fetch_tryte().get_lo();
            Word src = fetch_word();
            registers[dest_idx] = registers[dest_idx] % src;
            break;
        }
        case MOD_REG_ABS: {
            Trybble dest_idx = fetch_tryte().get_lo();
            Word src_addr = fetch_word();
            registers[dest_idx] = registers[dest_idx] % read_word(src_addr);
            break;
        }
        case MOD_REG_REG: {
            Tryte tryte = fetch_tryte();
            Trybble dest_idx = tryte.get_hi();
            Trybble src_idx = tryte.get_lo();
            registers[dest_idx] = registers[dest_idx] % registers[src_idx];
            break;
        }
        case AND_ABS_ABS: {
            Word dest_addr = fetch_word();
            Word src_addr = fetch_word();
            write_word(dest_addr, read_word(dest_addr) & read_word(src_addr));
            break;
        }
        case AND_ABS_REG: {
            Word dest_addr = fetch_word();
            Trybble src_idx = fetch_tryte().get_lo();
            write_word(dest_addr, read_word(dest_addr) & registers[src_idx]);
            break;
        }
        case AND_REG_IMM: {
            Trybble dest_idx = fetch_tryte().get_lo();
            Word src = fetch_word();
            registers[dest_idx] = registers[dest_idx] & src;
            break;
        }
        case AND_REG_ABS: {
            Trybble dest_idx = fetch_tryte().get_lo();
            Word src_addr = fetch_word();
            registers[dest_idx] = registers[dest_idx] & read_word(src_addr);
            break;
        }
        case AND_REG_REG: {
            Tryte tryte = fetch_tryte();
            Trybble dest_idx = tryte.get_hi();
            Trybble src_idx = tryte.get_lo();
            registers[dest_idx] = registers[dest_idx] & registers[src_idx];
            break;
        }
        case OR_ABS_ABS: {
            Word dest_addr = fetch_word();
            Word src_addr = fetch_word();
            write_word(dest_addr, read_word(dest_addr) | read_word(src_addr));
            break;
        }
        case OR_ABS_REG: {
            Word dest_addr = fetch_word();
            Trybble src_idx = fetch_tryte().get_lo();
            write_word(dest_addr, read_word(dest_addr) | registers[src_idx]);
            break;
        }
        case OR_REG_IMM: {
            Trybble dest_idx = fetch_tryte().get_lo();
            Word src = fetch_word();
            registers[dest_idx] = registers[dest_idx] | src;
            break;
        }
        case OR_REG_ABS: {
            Trybble dest_idx = fetch_tryte().get_lo();
            Word src_addr = fetch_word();
            registers[dest_idx] = registers[dest_idx] | read_word(src_addr);
            break;
        }
        case OR_REG_REG: {
            Tryte tryte = fetch_tryte();
            Trybble dest_idx = tryte.get_hi();
            Trybble src_idx = tryte.get_lo();
            registers[dest_idx] = registers[dest_idx] | registers[src_idx];
            break;
        }
        case XOR_ABS_ABS: {
            Word dest_addr = fetch_word();
            Word src_addr = fetch_word();
            write_word(dest_addr, read_word(dest_addr) ^ read_word(src_addr));
            break;
        }
        case XOR_ABS_REG: {
            Word dest_addr = fetch_word();
            Trybble src_idx = fetch_tryte().get_lo();
            write_word(dest_addr, read_word(dest_addr) ^ registers[src_idx]);
            break;
        }
        case XOR_REG_IMM: {
            Trybble dest_idx = fetch_tryte().get_lo();
            Word src = fetch_word();
            registers[dest_idx] = registers[dest_idx] ^ src;
            break;
        }
        case XOR_REG_ABS: {
            Trybble dest_idx = fetch_tryte().get_lo();
            Word src_addr = fetch_word();
            registers[dest_idx] = registers[dest_idx] ^ read_word(src_addr);
            break;
        }
        case XOR_REG_REG: {
            Tryte tryte = fetch_tryte();
            Trybble dest_idx = tryte.get_hi();
            Trybble src_idx = tryte.get_lo();
            registers[dest_idx] = registers[dest_idx] ^ registers[src_idx];
            break;
        }
        }
    }

    void VM::run(bool verbose) {
        running = true;
        while (running) {
            step(verbose);
        }
    }
} // namespace termite