#include <iostream>
#include <string>
#include <utility>
#include "word.h"

namespace termite {
    class Mem {
    public:
        static constexpr uint32_t MAX_MEM = 43046721;
        Tryte data[MAX_MEM];
        void initialize();
        // Read 1 tryte with uint32_t address
        Tryte get_tryte(uint32_t addr) const;
        // Read 1 tryte with ternry word address
        Tryte get_tryte(const Word& addr) const;
        Word get_word(const Word& addr) const;
        Tryte set_tryte(const Word& addr) const;
        void set_word(const Word& addr, const Word& val);
    };

    class CPU {
    public:
        Word regs[9];
        Word flags;
        // register indices
        static constexpr int32_t REG_AX = -4;
        static constexpr int32_t REG_BX = -3;
        static constexpr int32_t REG_CX = -2;
        static constexpr int32_t REG_SP = -1;
        static constexpr int32_t REG_BP = 0;
        static constexpr int32_t REG_DI = 1;
        static constexpr int32_t REG_SI = 2;
        static constexpr int32_t REG_DX = 3;
        static constexpr int32_t REG_IP = 4;
        // opcodes
        static constexpr int32_t INS_MOV = -40;
        static constexpr int32_t INS_PUSH = -39;
        static constexpr int32_t INS_POP = -38;
        static constexpr int32_t INS_PUSHF = -37;
        static constexpr int32_t INS_POPF = -36;
        static constexpr int32_t INS_AND = -35;
        static constexpr int32_t INS_OR = -34;
        static constexpr int32_t INS_XOR = -33;
        static constexpr int32_t INS_SHL = -32;
        static constexpr int32_t INS_SHR = -31;
        static constexpr int32_t INS_ADD = -30;
        static constexpr int32_t INS_ADC = -29;
        static constexpr int32_t INS_SUB = -28;
        static constexpr int32_t INS_SBB = -27;
        static constexpr int32_t INS_MUL = -26;
        static constexpr int32_t INS_DIV = -25;
        static constexpr int32_t INS_NEG = -24;
        static constexpr int32_t INS_CMP = -23;
        static constexpr int32_t INS_CALL = -22;
        static constexpr int32_t INS_RET = -21;
        static constexpr int32_t INS_JMP = -20;
        static constexpr int32_t INS_JL = -19;
        static constexpr int32_t INS_JLE = -18;
        static constexpr int32_t INS_JG = -17;
        static constexpr int32_t INS_JGE = -16;
        static constexpr int32_t INS_JE = -15;
        static constexpr int32_t INS_JNE = -14;
        static constexpr int32_t INS_JC = -13;
        static constexpr int32_t INS_JNC = -12;
        static constexpr int32_t INS_INT = -11;
        void reset(Mem& memory);
        void set_sign_flag(Word& cycles, Mem& memory, const Word& result);
        Tryte fetch_tryte(Word& cycles, Mem& memory);
        Word fetch_word(Word& cycles, Mem& memory);
        Word get_addr_mode(Word& cycles, Mem& memory, uint8_t mode, const Word& reg, const Word& imm);
        void execute(Word& cycles, Mem& memory);
    };
}