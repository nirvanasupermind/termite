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
        void reset(Mem& memory);
        void set_sign_flag(Word& cycles, Mem& memory, const Word& result);
        Tryte fetch_tryte(Word& cycles, Mem& memory);
        Word fetch_word(Word& cycles, Mem& memory);
        Word get_addr_mode(Word& cycles, Mem& memory, uint8_t mode, const Word& reg);
        void execute(Word& cycles, Mem& memory);
    };
}