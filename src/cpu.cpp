#include <iostream>
#include <array>

#include "typedefs.hpp"
#include "tryte.hpp"
#include "word.hpp"
#include "mem.hpp"
#include "opcodes.hpp"
#include "cpu.hpp"

namespace termite {
    CPU::CPU() {
        reset();
    }

    void CPU::reset() {
        mem.reset();
        std::fill(std::begin(register_file), std::end(register_file), Word::ZERO);
    }

    void CPU::inc_pc() {
        register_file[26] = register_file[26] + Word::ONE;
    }

    void CPU::inc2_pc() {
        register_file[26] = register_file[26] + Word::TWO;
    }

    Tryte CPU::fetch_tryte() {
        Tryte result = mem.read_tryte(register_file[26]);
        inc_pc();
        return result;
    }

    Word CPU::fetch_word() {
        Word result = mem.read_word(register_file[26]);
        inc2_pc();
        return result;
    }

    Opcode CPU::decode_opcode(const Tryte& tryte) const {
        return static_cast<Opcode>(tryte.to_u16());
    }

    void CPU::execute() {

        while (true) {
            if(register_file[26].to_i32() >= 30)  {
                break;
            }

            Tryte op_tryte = fetch_tryte();

            Opcode opcode = decode_opcode(op_tryte);

            switch (opcode) {
            case Opcode::MOV_ABS_IMM: {
                Word dest = fetch_word();
                Word src = fetch_word();
                mem.write_word(dest, src);
                break;
            };

            case Opcode::MOV_ABS_ABS: {
                Word dest = fetch_word();
                Word src = fetch_word();
                mem.write_word(dest, mem.read_word(src));
                break;
            };

            case Opcode::MOV_ABS_REG: {
                Word dest = fetch_word();
                Trybble src = fetch_tryte().get_lo();
                mem.write_word(dest, register_file[src.to_u8()]);
                break;
            };

            case Opcode::MOV_REG_IMM: {
                Trybble dest = fetch_tryte().get_lo();
                Word src = fetch_word();
                register_file[dest.to_u8()] = src;
                break;
            };

            case Opcode::MOV_REG_ABS: {
                Trybble dest = fetch_tryte().get_lo();
                Word src = fetch_word();
                register_file[dest.to_u8()] = mem.read_word(src);
                break;
            };

            case Opcode::MOV_REG_REG: {
                Tryte temp = fetch_tryte();
                Trybble dest = temp.get_hi();
                Trybble src = temp.get_lo();
                register_file[dest.to_u8()] = register_file[src.to_u8()];
                break;
            };

            case Opcode::ADD_ABS_IMM: {
                Word dest = fetch_word();
                Word src = fetch_word();
                mem.write_word(dest, mem.read_word(dest) + src);
                break;
            };

            case Opcode::ADD_ABS_ABS: {
                Word dest = fetch_word();
                Word src = fetch_word();
                mem.write_word(dest, mem.read_word(dest) + mem.read_word(src));
                break;
            };

            case Opcode::ADD_ABS_REG: {
                Word dest = fetch_word();
                Trybble src = fetch_tryte().get_lo();
            
                mem.write_word(dest, mem.read_word(dest) + register_file[src.to_u8()]);
                break;
            };

            case Opcode::ADD_REG_IMM: {
                Trybble dest = fetch_tryte().get_lo();
                Word src = fetch_word();
                u8 idx = dest.to_u8();
                register_file[idx] = register_file[idx] + src;
                break;
            };

            case Opcode::ADD_REG_ABS: {
                Trybble dest = fetch_tryte().get_lo();
                Word src = fetch_word();
                u8 idx = dest.to_u8();
                register_file[idx] = register_file[idx] + mem.read_word(src);
                break;
            };

            case Opcode::ADD_REG_REG: {
                Tryte temp = fetch_tryte();
                Trybble dest = temp.get_hi();
                Trybble src = temp.get_lo();
                u8 idx = dest.to_u8();
                register_file[idx] = register_file[idx] + register_file[src.to_u8()];
                break;
            };

            case Opcode::SUB_ABS_IMM: {
                Word dest = fetch_word();
                Word src = fetch_word();
                mem.write_word(dest, mem.read_word(dest) - src);
                break;
            };

            case Opcode::SUB_ABS_ABS: {
                Word dest = fetch_word();
                Word src = fetch_word();
                mem.write_word(dest, mem.read_word(dest) - mem.read_word(src));
                break;
            };

            case Opcode::SUB_ABS_REG: {
                Word dest = fetch_word();
                Trybble src = fetch_tryte().get_lo();

                mem.write_word(dest, mem.read_word(dest) - register_file[src.to_u8()]);
                break;
            };

            case Opcode::SUB_REG_IMM: {
                Trybble dest = fetch_tryte().get_lo();
                Word src = fetch_word();
                u8 idx = dest.to_u8();
                register_file[idx] = register_file[idx] - src;
                break;
            };

            case Opcode::SUB_REG_ABS: {
                Trybble dest = fetch_tryte().get_lo();
                Word src = fetch_word();
                u8 idx = dest.to_u8();
                register_file[idx] = register_file[idx] - mem.read_word(src);
                break;
            };

            case Opcode::SUB_REG_REG: {
                Tryte temp = fetch_tryte();
                Trybble dest = temp.get_hi();
                Trybble src = temp.get_lo();
                u8 idx = dest.to_u8();

                register_file[idx] = register_file[idx] - register_file[src.to_u8()];
                break;
            };

            case Opcode::MUL_ABS_IMM: {
                Word dest = fetch_word();
                Word src = fetch_word();
                mem.write_word(dest, mem.read_word(dest) * src);
                break;
            };

            case Opcode::MUL_ABS_ABS: {
                Word dest = fetch_word();
                Word src = fetch_word();
                mem.write_word(dest, mem.read_word(dest) * mem.read_word(src));
                break;
            };

            case Opcode::MUL_ABS_REG: {
                Word dest = fetch_word();
                Trybble src = fetch_tryte().get_lo();

                mem.write_word(dest, mem.read_word(dest) * register_file[src.to_u8()]);
                break;
            };

            case Opcode::MUL_REG_IMM: {
                Trybble dest = fetch_tryte().get_lo();
                Word src = fetch_word();
                u8 idx = dest.to_u8();
                register_file[idx] = register_file[idx] * src;
                break;
            };

            case Opcode::MUL_REG_ABS: {
                Trybble dest = fetch_tryte().get_lo();
                Word src = fetch_word();
                u8 idx = dest.to_u8();
                register_file[idx] = register_file[idx] * mem.read_word(src);
                break;
            };

            case Opcode::MUL_REG_REG: {
                Tryte temp = fetch_tryte();
                Trybble dest = temp.get_hi();
                Trybble src = temp.get_lo();
                u8 idx = dest.to_u8();
                register_file[idx] = register_file[idx] * register_file[src.to_u8()];
                break;
            };

            case Opcode::HLT: {
                return;
            };

            default:
                throw std::runtime_error("[termite] illegal opcode: " + op_tryte.to_sept_str());
            }
        }
    }
} // namespace termite