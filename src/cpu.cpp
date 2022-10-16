#include <iostream>
#include <array>

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

    // void CPU::debug() {
    //     for (Word reg : register_file) {
        
    //     }
    // }

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
        return static_cast<Opcode>(static_cast<unsigned int>(tryte));
    }

    void CPU::execute() {

        while (true) {
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
                mem.write_word(dest, register_file[static_cast<unsigned int>(src)]);
                break;
            };

            case Opcode::MOV_REG_IMM: {
                Trybble dest = fetch_tryte().get_lo();
                Word src = fetch_word();
                register_file[static_cast<unsigned int>(dest)] = src;
                break;
            };

            case Opcode::MOV_REG_ABS: {
                Trybble dest = fetch_tryte().get_lo();
                Word src = fetch_word();
                register_file[static_cast<unsigned int>(dest)] = mem.read_word(src);
                break;
            };

            case Opcode::MOV_REG_REG: {
                Tryte temp = fetch_tryte();
                Trybble dest = temp.get_hi();
                Trybble src = temp.get_lo();
                register_file[static_cast<unsigned int>(dest)] = register_file[static_cast<unsigned int>(src)];
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
            
                mem.write_word(dest, mem.read_word(dest) + register_file[static_cast<unsigned int>(src)]);
                break;
            };

            case Opcode::ADD_REG_IMM: {
                Trybble dest = fetch_tryte().get_lo();
                Word src = fetch_word();
                int idx = static_cast<unsigned int>(idx);
                register_file[idx] = register_file[idx] + src;
                break;
            };

            case Opcode::ADD_REG_ABS: {
                Trybble dest = fetch_tryte().get_lo();
                Word src = fetch_word();
                int idx = static_cast<unsigned int>(dest);
                register_file[idx] = register_file[idx] + mem.read_word(src);
                break;
            };

            case Opcode::ADD_REG_REG: {
                Tryte temp = fetch_tryte();
                Trybble dest = temp.get_hi();
                Trybble src = temp.get_lo();
                int idx = static_cast<unsigned int>(dest);
                register_file[idx] = register_file[idx] + register_file[static_cast<unsigned int>(src)];
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

                mem.write_word(dest, mem.read_word(dest) - register_file[static_cast<unsigned int>(src)]);
                break;
            };

            case Opcode::SUB_REG_IMM: {
                Trybble dest = fetch_tryte().get_lo();
                Word src = fetch_word();
                int idx = static_cast<unsigned int>(dest);
                register_file[idx] = register_file[idx] - src;
                break;
            };

            case Opcode::SUB_REG_ABS: {
                Trybble dest = fetch_tryte().get_lo();
                Word src = fetch_word();
                int idx = static_cast<unsigned int>(dest);
                register_file[idx] = register_file[idx] - mem.read_word(src);
                break;
            };

            case Opcode::SUB_REG_REG: {
                Tryte temp = fetch_tryte();
                Trybble dest = temp.get_hi();
                Trybble src = temp.get_lo();
                int idx = static_cast<unsigned int>(dest);

                register_file[idx] = register_file[idx] - register_file[static_cast<unsigned int>(src)];
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

                mem.write_word(dest, mem.read_word(dest) * register_file[static_cast<unsigned int>(src)]);
                break;
            };

            case Opcode::MUL_REG_IMM: {
                Trybble dest = fetch_tryte().get_lo();
                Word src = fetch_word();
                int idx = static_cast<unsigned int>(dest);
                register_file[idx] = register_file[idx] * src;
                break;
            };

            case Opcode::MUL_REG_ABS: {
                Trybble dest = fetch_tryte().get_lo();
                Word src = fetch_word();
                int idx = static_cast<unsigned int>(dest);
                register_file[idx] = register_file[idx] * mem.read_word(src);
                break;
            };

            case Opcode::MUL_REG_REG: {
                Tryte temp = fetch_tryte();
                Trybble dest = temp.get_hi();
                Trybble src = temp.get_lo();
                int idx = static_cast<unsigned int>(dest);
                register_file[idx] = register_file[idx] * register_file[static_cast<unsigned int>(src)];
                break;
            };

            case Opcode::DIV_ABS_IMM: {
                Word dest = fetch_word();
                Word src = fetch_word();
                mem.write_word(dest, mem.read_word(dest) / src);
                break;
            };

            case Opcode::DIV_ABS_ABS: {
                Word dest = fetch_word();
                Word src = fetch_word();
                mem.write_word(dest, mem.read_word(dest) / mem.read_word(src));
                break;
            };

            case Opcode::DIV_ABS_REG: {
                Word dest = fetch_word();
                Trybble src = fetch_tryte().get_lo();

                mem.write_word(dest, mem.read_word(dest) / register_file[static_cast<unsigned int>(src)]);
                break;
            };

            case Opcode::DIV_REG_IMM: {
                Trybble dest = fetch_tryte().get_lo();
                Word src = fetch_word();
                int idx = static_cast<unsigned int>(dest);
                register_file[idx] = register_file[idx] / src;
                break;
            };

            case Opcode::DIV_REG_ABS: {
                Trybble dest = fetch_tryte().get_lo();
                Word src = fetch_word();
                int idx = static_cast<unsigned int>(dest);
                register_file[idx] = register_file[idx] / mem.read_word(src);
                break;
            };

            case Opcode::DIV_REG_REG: {
                Tryte temp = fetch_tryte();
                Trybble dest = temp.get_hi();
                Trybble src = temp.get_lo();
                int idx = static_cast<unsigned int>(dest);
                register_file[idx] = register_file[idx] / register_file[static_cast<unsigned int>(src)];
                break;
            };

            case Opcode::MOD_ABS_IMM: {
                Word dest = fetch_word();
                Word src = fetch_word();
                mem.write_word(dest, mem.read_word(dest) % src);
                break;
            };

            case Opcode::MOD_ABS_ABS: {
                Word dest = fetch_word();
                Word src = fetch_word();
                mem.write_word(dest, mem.read_word(dest) % mem.read_word(src));
                break;
            };

            case Opcode::MOD_ABS_REG: {
                Word dest = fetch_word();
                Trybble src = fetch_tryte().get_lo();

                mem.write_word(dest, mem.read_word(dest) % register_file[static_cast<unsigned int>(src)]);
                break;
            };

            case Opcode::MOD_REG_IMM: {
                Trybble dest = fetch_tryte().get_lo();
                Word src = fetch_word();
                int idx = static_cast<unsigned int>(dest);
                register_file[idx] = register_file[idx] % src;
                break;
            };

            case Opcode::MOD_REG_ABS: {
                Trybble dest = fetch_tryte().get_lo();
                Word src = fetch_word();
                int idx = static_cast<unsigned int>(dest);
                register_file[idx] = register_file[idx] % mem.read_word(src);
                break;
            };

            case Opcode::MOD_REG_REG: {
                Tryte temp = fetch_tryte();
                Trybble dest = temp.get_hi();
                Trybble src = temp.get_lo();
                int idx = static_cast<unsigned int>(dest);
                register_file[idx] = register_file[idx] % register_file[static_cast<unsigned int>(src)];
                break;
            };

            case Opcode::HLT: {
                return;
            };

            default:
                throw std::runtime_error("[termite] illegal opcode: " + static_cast<std::string>(op_tryte));
            }
        }
    }
} // namespace termite