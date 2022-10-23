// -*- opcodes.hpp -*-
// Part of the Termite project, under the MIT License.

#ifndef OPCODES_HPP
#define OPCODES_HPP

namespace termite {
    enum Opcode {
        NOP, // No operation
        HLT, // Halt
        MOV_ABS_IMM, // Move
        MOV_ABS_ABS,
        MOV_ABS_REG,
        MOV_REG_IMM,
        MOV_REG_ABS,
        MOV_REG_REG,
        ADD_ABS_IMM,
        ADD_ABS_ABS, // Add
        ADD_ABS_REG,
        ADD_REG_IMM,
        ADD_REG_ABS,
        ADD_REG_REG,
        ADC_ABS_IMM, // Add with carry
        ADC_ABS_ABS,
        ADC_ABS_REG,
        ADC_REG_IMM,
        ADC_REG_ABS,
        ADC_REG_REG,
        SUB_ABS_IMM, // Subtract
        SUB_ABS_ABS,
        SUB_ABS_REG,
        SUB_REG_IMM,
        SUB_REG_ABS,
        SUB_REG_REG,
        MUL_ABS_IMM, // Multiply
        MUL_ABS_ABS,
        MUL_ABS_REG,
        MUL_REG_IMM,
        MUL_REG_ABS,
        MUL_REG_REG,
        DIV_ABS_IMM, // Divide
        DIV_ABS_ABS,
        DIV_ABS_REG,
        DIV_REG_IMM,
        DIV_REG_ABS,
        DIV_REG_REG,
        MOD_ABS_IMM, // Modulo
        MOD_ABS_ABS,
        MOD_ABS_REG,
        MOD_REG_IMM,
        MOD_REG_ABS,
        MOD_REG_REG,
        AND_ABS_IMM, // Tritwise AND
        AND_ABS_ABS,
        AND_ABS_REG,
        AND_REG_IMM,
        AND_REG_ABS,
        AND_REG_REG,
        OR_ABS_IMM, // Tritwise OR
        OR_ABS_ABS,
        OR_ABS_REG,
        OR_REG_IMM,
        OR_REG_ABS,
        OR_REG_REG,
        XOR_ABS_IMM, // Tritwise XOR
        XOR_ABS_ABS,
        XOR_ABS_REG,
        XOR_REG_IMM,
        XOR_REG_ABS,
        XOR_REG_REG,
        SL_ABS_IMM, // Shift left
        SL_ABS_ABS,
        SL_ABS_REG,
        SL_REG_IMM,
        SL_REG_ABS,
        SL_REG_REG,
        SR_ABS_IMM, // Shift right
        SR_ABS_ABS,
        SR_ABS_REG,
        SR_REG_IMM,
        SR_REG_ABS,
        SR_REG_REG,
        CMP_ABS_IMM, // Compare
        CMP_ABS_ABS,
        CMP_ABS_REG,
        CMP_REG_IMM,
        CMP_REG_ABS,
        CMP_REG_REG,
        JMP, // Jump
        JE, // Jump if equal
        JNE, // Jump if not equal
        JL, // Jump if less
        JG, // Jump if greater
        JLE, // Jump if less than or equal
        JGE, // Jump if greater than or equal
        JC, // Jump if carry
        JNC, // Jump if not carry
        JSR, // Jump to subroutine
        RET, // Return from subroutine
        PUSH, // Push to stack
        POP // Pop from stack
    };
} // namespace termite

#endif // OPCODES_HPP