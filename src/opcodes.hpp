// -*- opcodes.hpp -*-
// Part of the Termite project, under the MIT License.

#ifndef OPCODES_HPP
#define OPCODES_HPP

#include "typedefs.hpp"

namespace termite {
    enum class Opcode : u16 {
        MOV_ABS_IMM,
        MOV_ABS_ABS,
        MOV_ABS_REG,
        MOV_REG_IMM,
        MOV_REG_ABS,
        MOV_REG_REG,
        ADD_ABS_IMM,
        ADD_ABS_ABS,
        ADD_ABS_REG,
        ADD_REG_IMM,
        ADD_REG_ABS,
        ADD_REG_REG,
        SUB_ABS_IMM,
        SUB_ABS_ABS,
        SUB_ABS_REG,
        SUB_REG_IMM,
        SUB_REG_ABS,
        SUB_REG_REG,
        MUL_ABS_IMM,
        MUL_ABS_ABS,
        MUL_ABS_REG,
        MUL_REG_IMM,
        MUL_REG_ABS,
        MUL_REG_REG,
        HLT
    };
} // namespace termite

#endif // TRYTE_HPP