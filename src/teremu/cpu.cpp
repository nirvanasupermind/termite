#include "word.h"
#include "cpu.h"

namespace termite {
    void Mem::initialize() {
        for (uint32_t i = 0; i < MAX_MEM; i++) {
            data[i] = 0;
        }
    }

    Tryte Mem::get_tryte(uint32_t addr) const {
        return data[addr];
    }

    Tryte Mem::get_tryte(const Word& addr) const {
        return data[addr.to_int32() + 21523360];
    }

    Word Mem::get_word(const Word& addr) const {
        return Word(get_tryte(addr), get_tryte(addr + Word::ONE));
    }

    void Mem::set_word(const Word& addr, const Word& val) {
        data[addr.to_int32() + 21523360] = val.get_lo_tryte();
        data[addr.to_int32() + 21523361] = val.get_hi_tryte();
    }

    void CPU::reset(Mem& memory) {
        for (int i = 0; i < 7; i++) {
            regs[i] = 0;
        }
        regs[REG_SP] = Word::from_int32(21523360);
        regs[REG_IP] = Word::from_int32(-21523360);
        memory.initialize();
    }

    Tryte CPU::fetch_tryte(Word& cycles, Mem& memory) {
        Tryte data = memory.get_tryte(regs[REG_IP]);
        regs[REG_IP] = regs[REG_IP] + Word::ONE;
        cycles = cycles - Word::ONE;
    }

    Word CPU::fetch_word(Word& cycles, Mem& memory) {
        return Word(fetch_tryte(cycles, memory), fetch_tryte(cycles, memory));
    }

    Word CPU::get_addr_mode(Word& cycles, Mem& memory, uint8_t mode, const Word& reg, const Word& imm) {
        if (mode == 0) {
            return imm;
        }
        else if (mode == 1) {
            return regs[reg.to_int32() + 4];
        }
        else {
            return memory.get_word(regs[reg.to_int32() + 4] + imm);
        }
    }

    void CPU::set_sign_flag(Word& cycles, Mem& memory, const Word& result) {
        if (result < Word::ZERO) {
            flags.set_bct_trit(1, 0);
        }
        else if (result == Word::ZERO) {
            flags.set_bct_trit(1, 1);
        }
        else {
            flags.set_bct_trit(1, 2);
        }
    }

    void CPU::execute(Word& cycles, Mem& memory) {
        while (cycles > Word::ZERO) {
            Word ins = fetch_word(cycles, memory);
            Word imm = fetch_word(cycles, memory);
            Word imm2 = fetch_word(cycles, memory);
            Word opcode = ins.get_trit_range(12, 15);
            switch (opcode.to_int32()) {
            case INS_MOV: {
                uint8_t dest_mode = ins.get_bct_trit(11);
                Word dest_reg = ins.get_trit_range(9, 10);

                uint8_t src_mode = ins.get_bct_trit(8);
                Word src_reg = ins.get_trit_range(6, 7);
                if (dest_mode == 1) {
                    regs[dest_reg.to_int32() + 4] = get_addr_mode(cycles, memory, src_mode, src_reg, imm2);
                }
                else {
                    Word addr = regs[dest_reg.to_int32() + 4] + imm;
                    memory.set_word(addr, get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                }
                break;
            }
            case INS_PUSH: {
                uint8_t src_mode = ins.get_bct_trit(11);
                Word src_reg = ins.get_trit_range(9, 10);

                regs[REG_SP] = regs[REG_SP] - Word::TWO;
                memory.set_word(regs[REG_SP], get_addr_mode(cycles, memory, src_mode, src_reg, imm));
                break;
            }
            case INS_POP: {
                uint8_t dest_mode = ins.get_bct_trit(11);
                Word dest_reg = ins.get_trit_range(9, 10);

                if (dest_mode == 0) {
                    regs[dest_reg.to_int32() + 4] = regs[REG_SP];
                    regs[REG_SP] = regs[REG_SP] + Word::TWO;
                }
                else {
                    Word addr = regs[dest_reg.to_int32() + 4] + imm;
                    memory.set_word(addr, regs[REG_SP]);
                    regs[REG_SP] = regs[REG_SP] + Word::TWO;
                }
            }
            case INS_PUSHF: {
                regs[REG_SP] = regs[REG_SP] - Word::TWO;
                memory.set_word(regs[REG_SP], flags);
                break;
            }
            case INS_POPF: {
                flags = memory.get_word(regs[REG_SP]);
                regs[REG_SP] = regs[REG_SP] + Word::TWO;
                break;
            }
            case INS_AND: {
                uint8_t dest_mode = ins.get_bct_trit(11);
                Word dest_reg = ins.get_trit_range(9, 10);

                uint8_t src_mode = ins.get_bct_trit(8);
                Word src_reg = ins.get_trit_range(6, 7);
                Word result;
                if (dest_mode == 1) {
                    result = regs[dest_reg.to_int32() + 4] & get_addr_mode(cycles, memory, src_mode, src_reg, imm2);
                    regs[dest_reg.to_int32() + 4] = result;
                }
                else {
                    Word addr = regs[dest_reg.to_int32() + 4] + imm;
                    result = memory.get_word(addr) & get_addr_mode(cycles, memory, src_mode, src_reg, imm2);
                    memory.set_word(addr, result);
                }
                set_sign_flag(cycles, memory, result);
                break;
            }
            case INS_OR: {
                uint8_t dest_mode = ins.get_bct_trit(11);
                Word dest_reg = ins.get_trit_range(9, 10);

                uint8_t src_mode = ins.get_bct_trit(8);
                Word src_reg = ins.get_trit_range(6, 7);
                Word result;
                if (dest_mode == 1) {
                    result = regs[dest_reg.to_int32() + 4] | get_addr_mode(cycles, memory, src_mode, src_reg, imm2);
                    regs[dest_reg.to_int32() + 4] = result;
                }
                else {
                    Word addr = regs[dest_reg.to_int32() + 4] + imm;
                    result = memory.get_word(addr) | get_addr_mode(cycles, memory, src_mode, src_reg, imm2);
                    memory.set_word(addr, result);
                }
                set_sign_flag(cycles, memory, result);
                break;
            }
            case INS_XOR: {
                uint8_t dest_mode = ins.get_bct_trit(11);
                Word dest_reg = ins.get_trit_range(9, 10);

                uint8_t src_mode = ins.get_bct_trit(8);
                Word src_reg = ins.get_trit_range(6, 7);
                Word result;
                if (dest_mode == 1) {
                    result = regs[dest_reg.to_int32() + 4] ^ get_addr_mode(cycles, memory, src_mode, src_reg, imm2);
                    regs[dest_reg.to_int32() + 4] = result;
                }
                else {
                    Word addr = regs[dest_reg.to_int32() + 4] + imm;
                    result = memory.get_word(addr) ^ get_addr_mode(cycles, memory, src_mode, src_reg, imm2);
                    memory.set_word(addr, result);
                }
                set_sign_flag(cycles, memory, result);
                break;
            }
            case INS_SHL: {
                uint8_t dest_mode = ins.get_bct_trit(11);
                Word dest_reg = ins.get_trit_range(9, 10);

                uint8_t src_mode = ins.get_bct_trit(8);
                Word src_reg = ins.get_trit_range(6, 7);
                Word result;
                if (dest_mode == 1) {
                    result = regs[dest_reg.to_int32() + 4] << get_addr_mode(cycles, memory, src_mode, src_reg, imm2);
                    regs[dest_reg.to_int32() + 4] = result;
                }
                else {
                    Word addr = regs[dest_reg.to_int32() + 4] + imm;
                    result = memory.get_word(addr) << get_addr_mode(cycles, memory, src_mode, src_reg, imm2);
                    memory.set_word(addr, result);
                }
                set_sign_flag(cycles, memory, result);
                break;
            }
            case INS_SHR: {
                uint8_t dest_mode = ins.get_bct_trit(11);
                Word dest_reg = ins.get_trit_range(9, 10);

                uint8_t src_mode = ins.get_bct_trit(8);
                Word src_reg = ins.get_trit_range(6, 7);
                Word result;
                if (dest_mode == 1) {
                    result = regs[dest_reg.to_int32() + 4] >> get_addr_mode(cycles, memory, src_mode, src_reg, imm2);
                    regs[dest_reg.to_int32() + 4] = result;
                }
                else {
                    Word addr = regs[dest_reg.to_int32() + 4] + imm;
                    result = memory.get_word(addr) >> get_addr_mode(cycles, memory, src_mode, src_reg, imm2);
                    memory.set_word(addr, result);
                }
                set_sign_flag(cycles, memory, result);
                break;
            }
            case INS_ADD: {
                uint8_t dest_mode = ins.get_bct_trit(11);
                Word dest_reg = ins.get_trit_range(9, 10);

                uint8_t src_mode = ins.get_bct_trit(8);
                Word src_reg = ins.get_trit_range(6, 7);

                std::pair<Word, Word> result;
                if (dest_mode == 1) {
                    result = regs[dest_reg.to_int32() + 4].add_with_carry(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                    regs[dest_reg.to_int32() + 4] = result.first;
                }
                else {
                    Word addr = regs[dest_reg.to_int32() + 4] + imm;
                    result = memory.get_word(addr).add_with_carry(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                    memory.set_word(addr, result.first);
                }
                set_sign_flag(cycles, memory, result.first);
                flags.set_bct_trit(0, result.second.get_bct());
                break;
            }
            case INS_ADC: {
                uint8_t dest_mode = ins.get_bct_trit(11);
                Word dest_reg = ins.get_trit_range(9, 10);

                uint8_t src_mode = ins.get_bct_trit(8);
                Word src_reg = ins.get_trit_range(6, 7);

                std::pair<Word, Word> result;
                if (dest_mode == 1) {
                    result = regs[dest_reg.to_int32() + 4].add_with_carry(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                    regs[dest_reg.to_int32() + 4] = result.first + Word(flags.get_bct_trit(0));;
                }
                else {
                    Word addr = regs[dest_reg.to_int32() + 4] + imm;
                    result = memory.get_word(addr).add_with_carry(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                    memory.set_word(addr, result.first + Word(flags.get_bct_trit(0)));
                }
                set_sign_flag(cycles, memory, result.first);
                flags.set_bct_trit(0, result.second.get_bct());
                break;
            }
            case INS_SUB: {
                uint8_t dest_mode = ins.get_bct_trit(11);
                Word dest_reg = ins.get_trit_range(9, 10);

                uint8_t src_mode = ins.get_bct_trit(8);
                Word src_reg = ins.get_trit_range(6, 7);

                std::pair<Word, Word> result;
                if (dest_mode == 1) {
                    result = regs[dest_reg.to_int32() + 4].sub_with_carry(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                    regs[dest_reg.to_int32() + 4] = result.first;
                }
                else {
                    Word addr = regs[dest_reg.to_int32() + 4] + imm;
                    result = memory.get_word(addr).sub_with_carry(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                    memory.set_word(addr, result.first);
                }
                set_sign_flag(cycles, memory, result.first);
                flags.set_bct_trit(0, result.second.get_bct());
                break;
            }
            case INS_SBB: {
                uint8_t dest_mode = ins.get_bct_trit(11);
                Word dest_reg = ins.get_trit_range(9, 10);

                uint8_t src_mode = ins.get_bct_trit(8);
                Word src_reg = ins.get_trit_range(6, 7);

                std::pair<Word, Word> result;
                if (dest_mode == 1) {
                    result = regs[dest_reg.to_int32() + 4].sub_with_carry(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                    regs[dest_reg.to_int32() + 4] = result.first - Word(flags.get_bct_trit(0));;
                }
                else {
                    Word addr = regs[dest_reg.to_int32() + 4] + imm;
                    result = memory.get_word(addr).sub_with_carry(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                    memory.set_word(addr, result.first - Word(flags.get_bct_trit(0)));
                }
                set_sign_flag(cycles, memory, result.first);
                flags.set_bct_trit(0, result.second.get_bct());
                break;
            }
            case INS_MUL: {
                uint8_t src_mode = ins.get_bct_trit(8);
                Word src_reg = ins.get_trit_range(6, 7);
                std::pair<Word, Word> result = regs[REG_AX].mul32(get_addr_mode(cycles, memory, src_mode, src_reg, imm));
                regs[REG_AX] = result.first;
                regs[REG_DX] = result.second;
                set_sign_flag(cycles, memory, result.first);
                break;
            }
            case INS_DIV: {
                uint8_t src_mode = ins.get_bct_trit(8);
                Word src_reg = ins.get_trit_range(6, 7);
                std::pair<Word, Word> result = regs[0].divmod(get_addr_mode(cycles, memory, src_mode, src_reg, imm));
                regs[REG_AX] = result.first;
                regs[REG_DX] = result.second;

                set_sign_flag(cycles, memory, result.first);
                break;
            }
            case INS_NEG: {
                uint8_t src_mode = ins.get_bct_trit(11);
                Word src_reg = ins.get_trit_range(9, 10);

                Word result = -get_addr_mode(cycles, memory, src_mode, src_reg, imm);
                if (src_mode == 1) {
                    regs[src_reg.to_int32() + 4] = result;
                }
                else {
                    Word addr = regs[src_reg.to_int32() + 4] + imm;
                    memory.set_word(addr, -result);
                }
                set_sign_flag(cycles, memory, result);
                break;
            }
            case INS_CMP: {
                uint8_t dest_mode = ins.get_bct_trit(11);
                Word dest_reg = ins.get_trit_range(9, 10);

                uint8_t src_mode = ins.get_bct_trit(8);
                Word src_reg = ins.get_trit_range(6, 7);

                std::pair<Word, Word> result;
                if (dest_mode == 1) {
                    result = regs[dest_reg.to_int32() + 4].sub_with_carry(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                }
                else {
                    Word addr = regs[dest_reg.to_int32() + 4] + imm;
                    result = memory.get_word(addr).sub_with_carry(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                }
                set_sign_flag(cycles, memory, result.first);
                flags.set_bct_trit(0, result.second.get_bct());
                break;
            }
            }

        }
    }
}