#ifndef OPCODE_H
#define OPCODE_H


namespace termite
{
    // Enum of all opcodes supported by the ISA
    enum class Opcode {
        NOP,
        LD,
        LDI,
        ST,
        ADD,
        ADDI,
        ADDC,
        SUB,
        SUBB,
        MUL,
        UDIV,
        SDIV,
        UMOD,
        SL,
        ASR,
        LSR,
        AND,
        OR,
        XOR,
        CMP,
        JMP,
        JEQ,
        JNE,
        JLT,
        JLE,
        JGT,
        JGE,
        PUSH,
        POP,
        CALL,
        RET,
        INT
    };
} // namespace termite

#endif // OPCODE_H