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
        HLT
    };
} // namespace termite

#endif // TRYTE_HPP