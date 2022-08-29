#include <iostream>
#include <cstdint>

#include "../core/trybble.h"
#include "../core/tryte.h"
#include "../core/word.h"
#include "../core/exceptions.h"
#include "memory.h"
#include "vm.h"

namespace termite {
    void VM::nop() const {
    }

    void VM::syscall(const Trybble &reg) {
        switch (regfile.at(24).to_uint64()) {
            case 0:
                std::cout << regfile.at(reg.to_uint8()).to_uint64();
                break;
            case 1:
                std::cout << regfile.at(reg.to_uint8()).to_ternary_str();
                break;
            case 2:
                std::cout << regfile.at(reg.to_uint8()).to_hept_str();
                break;
            default:
                throw TermiteException("invalid syscall code");
        }
    }

    void VM::add(const Trybble &reg1, const Trybble &reg2, const Trybble &reg3) {
        regfile[reg1.to_uint8()] = regfile.at(reg2.to_uint8()) + regfile.at(reg3.to_uint8());
    }

    void VM::sub(const Trybble &reg1, const Trybble &reg2, const Trybble &reg3) {
        regfile[reg1.to_uint8()] = regfile.at(reg2.to_uint8()) - regfile.at(reg3.to_uint8());
    }

    void VM::addi(const Trybble &reg1, const Trybble &reg2, const Halfword &imm) {
        regfile[reg1.to_uint8()] = regfile.at(reg2.to_uint8()) + Word(imm);
    }

    void VM::addu(const Trybble &reg1, const Trybble &reg2, const Trybble &reg3) {
        regfile[reg1.to_uint8()] = regfile.at(reg2.to_uint8()) + regfile.at(reg3.to_uint8());
    }

    void VM::subu(const Trybble &reg1, const Trybble &reg2, const Trybble &reg3) {
        regfile[reg1.to_uint8()] = regfile.at(reg2.to_uint8()) - regfile.at(reg3.to_uint8());
    }

    void VM::addiu(const Trybble &reg1, const Trybble &reg2, const Halfword &imm) {
        regfile[reg1.to_uint8()] = regfile.at(reg2.to_uint8()) + Word(zero_ext, imm);
    }

    void VM::mul(const Trybble &reg1, const Trybble &reg2, const Trybble &reg3) {
        regfile[reg1.to_uint8()] = regfile.at(reg2.to_uint8()) * regfile.at(reg3.to_uint8());
    }

    void VM::mulu(const Trybble &reg1, const Trybble &reg2, const Trybble &reg3) {
        regfile[reg1.to_uint8()] = regfile.at(reg2.to_uint8()).mulu(regfile.at(reg3.to_uint8()));
    }

    void VM::div(const Trybble &reg1, const Trybble &reg2, const Trybble &reg3) {
        regfile[reg1.to_uint8()] = regfile.at(reg2.to_uint8()) / regfile.at(reg3.to_uint8());
    }

    void VM::divu(const Trybble &reg1, const Trybble &reg2, const Trybble &reg3) {
        regfile[reg1.to_uint8()] = regfile.at(reg2.to_uint8()).divu(regfile.at(reg3.to_uint8()));
    }
}
