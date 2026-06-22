#include <iostream>
#include <string>
#include <utility>
#include <cstdint>
#include "../core/tryte.h"
#include "../core/word.h"
#include "../core/terfloat.h"

namespace termite {
    class Mem {
    public:
        static constexpr uint32_t MAX_MEM = 43046721;
        std::vector<Tryte> data;

        void initialize();
        // Read 1 tryte with uint32_t address
        Tryte get_tryte(uint32_t addr) const;
        // Read 1 tryte with ternry word address
        Tryte get_tryte(const Word& addr) const;
        Word get_word(const Word& addr) const;
        void set_tryte(const Word& addr, const Tryte& val);
        void set_word(const Word& addr, const Word& val);
    };

    class CPU {
    public:
        Word regs[9];
        Word flags;
        std::stack<TerFloat> st;
        // register indices
        static constexpr int32_t REG_AX = 0;
        static constexpr int32_t REG_BX = 1;
        static constexpr int32_t REG_CX = 2;
        static constexpr int32_t REG_SP = 3;
        static constexpr int32_t REG_BP = 4;
        static constexpr int32_t REG_DI = 5;
        static constexpr int32_t REG_SI = 6;
        static constexpr int32_t REG_DX = 7;
        static constexpr int32_t REG_IP = 8;
        // opcodes
        static constexpr int32_t INS_MOV = -40; // DD
        static constexpr int32_t INS_PUSH = -39; // DC
        static constexpr int32_t INS_POP = -38; // DB
        static constexpr int32_t INS_PUSHF = -37; // DA
        static constexpr int32_t INS_POPF = -36; // D0
        static constexpr int32_t INS_AND = -35; // D1
        static constexpr int32_t INS_OR = -34; // D2
        static constexpr int32_t INS_XOR = -33; // D3
        static constexpr int32_t INS_SHL = -32; // D4
        static constexpr int32_t INS_SHR = -31; // CD
        static constexpr int32_t INS_ADD = -30; // CC
        static constexpr int32_t INS_ADC = -29; // CB
        static constexpr int32_t INS_SUB = -28; // CA
        static constexpr int32_t INS_SBB = -27; // C0
        static constexpr int32_t INS_MUL = -26; // C1
        static constexpr int32_t INS_DIV = -25; // C2
        static constexpr int32_t INS_NEG = -24; // C3
        static constexpr int32_t INS_CMP = -23; // C4
        static constexpr int32_t INS_CALL = -22; // BD
        static constexpr int32_t INS_RET = -21; // BC
        static constexpr int32_t INS_JMP = -20; // BB
        static constexpr int32_t INS_JL = -19; // BA
        static constexpr int32_t INS_JLE = -18; // B0
        static constexpr int32_t INS_JG = -17; // B1
        static constexpr int32_t INS_JGE = -16; // B2
        static constexpr int32_t INS_JE = -15; // B3
        static constexpr int32_t INS_JNE = -14; // B4
        static constexpr int32_t INS_JC = -13; // AD
        static constexpr int32_t INS_JNC = -12; // AC
        static constexpr int32_t INS_INT = -11; // AB
        static constexpr int32_t INS_XCHG = -10; // AA
        static constexpr int32_t INS_FLD = -9; // A0
        static constexpr int32_t INS_FST = -8; // A1
        static constexpr int32_t INS_FSTP = -7; // A2
        static constexpr int32_t INS_FADD = -6; // A3
        static constexpr int32_t INS_FSUB = -5; // A4
        static constexpr int32_t INS_FMUL = -4; // 0D
        static constexpr int32_t INS_FDIV = -3; // 0C
        static constexpr int32_t INS_FSQRT = -2; // 0B
        static constexpr int32_t INS_FSIN = -1; // 0A
        static constexpr int32_t INS_FCOS = 0; // 00
        static constexpr int32_t INS_FTAN = 1; // 01
        static constexpr int32_t INS_FATAN = 2; // 02
        static constexpr int32_t INS_FEXP = 3; // 03
        static constexpr int32_t INS_FLOG = 4; // 04
        static constexpr int32_t INS_FABS = 5; // 1D
        static constexpr int32_t INS_FFLOOR = 6; // 1C
        static constexpr int32_t INS_FCMP = 7; // 1B
        static constexpr int32_t INS_LDT = 8; // 1A
        static constexpr int32_t INS_STT = 9; // 10


        void reset(Mem& memory);
        void set_sign_flag(Word& cycles, Mem& memory, const Word& result);
        void set_sign_flag_float(Word& cycles, Mem& memory, const TerFloat& result);

        Tryte fetch_tryte(Word& cycles, Mem& memory);
        Word fetch_word(Word& cycles, Mem& memory);
        Word get_addr_mode(Word& cycles, Mem& memory, const Word& mode, const Word& reg, const Word& imm);
        void print_state();
        void execute(Word& cycles, Mem& memory, bool verbose = false);
        void exec_text(std::string& text, Mem& memory, bool verbose = false);
    };

}