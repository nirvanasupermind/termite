#ifndef INSTR_H
#define INSTR_H

namespace termite
{
    // Represents a CPU instruction.
    enum class Instr
    {
        NOP,    
        MOV,
        POP,
        IN,
        OUT,
        LOAD,
        STOR,
        ADD,
        NEG,
        SUB,
        MUL,
        NOT,
        AND,
        OR,
        XOR,
        LS,
        RS,
        CMP,
        JMP,
        CJMP
    };
} // namespace termite

#endif