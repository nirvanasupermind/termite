#ifndef OPCODE_H
#define OPCODE_H


namespace termite
{
    // Enum of all opcodes supported by the ISA
    enum class Opcode {
        NOP,
        LDT,
        LDW,
        LDI,
        LDPS,
        STT,
        STW,
        NEG,
        ADD,
        ADDC,
        ADDI,
        SUB,
        SUBB,
        MUL,
        UDIV,
        SDIV,
        SL,
        ASR,
        LSR,
        NOT,
        AND,
        OR,
        XOR,
        CMP,
        JMP,
        JE,
        JNE,
        JL,
        JLE,
        JG,
        JGE,
        PUSH,
        POP,
        CALL,
        RET,
        SYSCALL
    };
} // namespace termite

#endif // OPCODE_H