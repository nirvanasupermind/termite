#include <iostream>
#include <string>
#include <utility>
#include <cstdint>
#include <vector>
#include "../core/tryte.h"
#include "../core/word.h"
#include "cpu.h"

namespace termite {
    void Mem::initialize() {
        if (data.size() == 0) {
            for (uint32_t i = 0; i < MAX_MEM; i++) {
                data.push_back(0);
            }
        }
        else {
            for (uint32_t i = 0; i < MAX_MEM; i++) {
                data[i] = 0;
            }
        }
    }

    Tryte Mem::get_tryte(uint32_t addr) const {
        return data[addr];
    }

    Tryte Mem::get_tryte(const Word& addr) const {
        return data[addr.to_int32() + 21523360];
    }

    void Mem::set_tryte(const Word& addr, const Tryte& val) {
        data[addr.to_int32() + 21523360] = val;
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
        return data;
    }

    Word CPU::fetch_word(Word& cycles, Mem& memory) {
        Word data = memory.get_word(regs[REG_IP]);
        regs[REG_IP] = regs[REG_IP] + Word::TWO;
        cycles = cycles - Word::TWO;
        return data;
    }

    Word CPU::get_addr_mode(Word& cycles, Mem& memory, const Word& mode, const Word& reg, const Word& imm) {
        if (mode.to_int32() == -4) {
            return imm;
        }
        else if (mode.to_int32() == -3) {
            return regs[reg.to_int32() + 4];
        }
        else if (mode.to_int32() == -2) {
            return memory.get_word(imm);
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
                Word dest_mode = ins.get_trit_range(10, 11);
                Word dest_reg = ins.get_trit_range(8, 9);

                Word src_mode = ins.get_trit_range(6, 7);
                Word src_reg = ins.get_trit_range(4, 5);


                if (dest_mode.to_int32() == -3) {
                    regs[dest_reg.to_int32() + 4] = get_addr_mode(cycles, memory, src_mode, src_reg, imm2);
                }
                else if (dest_mode.to_int32() == -2) {
                    memory.set_word(imm, get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                }
                else {
                    Word addr = regs[dest_reg.to_int32() + 4] + imm;
                    memory.set_word(addr, get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                }
                break;
            }
            case INS_PUSH: {
                Word src_mode = ins.get_trit_range(10, 11);
                Word src_reg = ins.get_trit_range(8, 9);

                regs[REG_SP] = regs[REG_SP] - Word::TWO;
                memory.set_word(regs[REG_SP], get_addr_mode(cycles, memory, src_mode, src_reg, imm));
                break;
            }
            case INS_POP: {
                Word dest_mode = ins.get_trit_range(10, 11);
                Word dest_reg = ins.get_trit_range(8, 9);
                Word val_at_sp = memory.get_word(regs[REG_SP]);
                if (dest_mode.to_int32() == -3) {
                    regs[dest_reg.to_int32() + 4] = val_at_sp;
                }
                else if (dest_mode.to_int32() == -2) {
                    memory.set_word(imm, val_at_sp);
                }
                else {
                    Word addr = regs[dest_reg.to_int32() + 4] + imm;
                    memory.set_word(addr, val_at_sp);
                }
                regs[REG_SP] = regs[REG_SP] + Word::TWO;
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
                Word dest_mode = ins.get_trit_range(10, 11);
                Word dest_reg = ins.get_trit_range(8, 9);

                Word src_mode = ins.get_trit_range(6, 7);
                Word src_reg = ins.get_trit_range(4, 5);
                Word result;
                if (dest_mode.to_int32() == -3) {
                    result = regs[dest_reg.to_int32() + 4] & get_addr_mode(cycles, memory, src_mode, src_reg, imm2);
                    regs[dest_reg.to_int32() + 4] = result;
                }
                else if (dest_mode.to_int32() == -2) {
                    result = memory.get_word(imm) & get_addr_mode(cycles, memory, src_mode, src_reg, imm2);
                    memory.set_word(imm, result);
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
                Word dest_mode = ins.get_trit_range(10, 11);
                Word dest_reg = ins.get_trit_range(8, 9);

                Word src_mode = ins.get_trit_range(6, 7);
                Word src_reg = ins.get_trit_range(4, 5);
                Word result;
                if (dest_mode.to_int32() == -3) {
                    result = regs[dest_reg.to_int32() + 4] | get_addr_mode(cycles, memory, src_mode, src_reg, imm2);
                    regs[dest_reg.to_int32() + 4] = result;
                }
                else if (dest_mode.to_int32() == -2) {
                    result = memory.get_word(imm) | get_addr_mode(cycles, memory, src_mode, src_reg, imm2);
                    memory.set_word(imm, result);
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
                Word dest_mode = ins.get_trit_range(10, 11);
                Word dest_reg = ins.get_trit_range(8, 9);

                Word src_mode = ins.get_trit_range(6, 7);
                Word src_reg = ins.get_trit_range(4, 5);
                Word result;
                if (dest_mode.to_int32() == -3) {
                    result = regs[dest_reg.to_int32() + 4] ^ get_addr_mode(cycles, memory, src_mode, src_reg, imm2);
                    regs[dest_reg.to_int32() + 4] = result;
                }
                else if (dest_mode.to_int32() == -2) {
                    result = memory.get_word(imm) ^ get_addr_mode(cycles, memory, src_mode, src_reg, imm2);
                    memory.set_word(imm, result);
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
                Word dest_mode = ins.get_trit_range(10, 11);
                Word dest_reg = ins.get_trit_range(8, 9);

                Word src_mode = ins.get_trit_range(6, 7);
                Word src_reg = ins.get_trit_range(4, 5);
                Word result;
                if (dest_mode.to_int32() == -3) {
                    result = regs[dest_reg.to_int32() + 4] << get_addr_mode(cycles, memory, src_mode, src_reg, imm2);
                    regs[dest_reg.to_int32() + 4] = result;
                }
                else if (dest_mode.to_int32() == -2) {
                    result = memory.get_word(imm) << get_addr_mode(cycles, memory, src_mode, src_reg, imm2);
                    memory.set_word(imm, result);
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
                Word dest_mode = ins.get_trit_range(10, 11);
                Word dest_reg = ins.get_trit_range(8, 9);

                Word src_mode = ins.get_trit_range(6, 7);
                Word src_reg = ins.get_trit_range(4, 5);
                Word result;
                if (dest_mode.to_int32() == -3) {
                    result = regs[dest_reg.to_int32() + 4] >> get_addr_mode(cycles, memory, src_mode, src_reg, imm2);
                    regs[dest_reg.to_int32() + 4] = result;
                }
                else if (dest_mode.to_int32() == -2) {
                    result = memory.get_word(imm) >> get_addr_mode(cycles, memory, src_mode, src_reg, imm2);
                    memory.set_word(imm, result);
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
                Word dest_mode = ins.get_trit_range(10, 11);
                Word dest_reg = ins.get_trit_range(8, 9);

                Word src_mode = ins.get_trit_range(6, 7);
                Word src_reg = ins.get_trit_range(4, 5);

                std::pair<Word, Word> result;
                if (dest_mode.to_int32() == -3) {
                    result = regs[dest_reg.to_int32() + 4].add_with_carry(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                    regs[dest_reg.to_int32() + 4] = result.first;
                }
                else if (dest_mode.to_int32() == -2) {
                    result = memory.get_word(imm).add_with_carry(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                    memory.set_word(imm, result.first);
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
                Word dest_mode = ins.get_trit_range(10, 11);
                Word dest_reg = ins.get_trit_range(8, 9);

                Word src_mode = ins.get_trit_range(6, 7);
                Word src_reg = ins.get_trit_range(4, 5);

                Word carry = Word::from_int32(flags.get_bct_trit(0) - 1);

                std::pair<Word, Word> result;
                if (dest_mode.to_int32() == -3) {
                    result = regs[dest_reg.to_int32() + 4].add_with_carry(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                    regs[dest_reg.to_int32() + 4] = result.first + carry;
                }
                else if (dest_mode.to_int32() == -2) {
                    result = memory.get_word(imm).add_with_carry(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                    memory.set_word(imm, result.first + carry);
                }
                else {
                    Word addr = regs[dest_reg.to_int32() + 4] + imm;
                    result = memory.get_word(addr).add_with_carry(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                    memory.set_word(addr, result.first + carry);
                }
                set_sign_flag(cycles, memory, result.first);
                flags.set_bct_trit(0, result.second.get_bct());
                break;
            }
            case INS_SUB: {
                Word dest_mode = ins.get_trit_range(10, 11);
                Word dest_reg = ins.get_trit_range(8, 9);

                Word src_mode = ins.get_trit_range(6, 7);
                Word src_reg = ins.get_trit_range(4, 5);

                std::pair<Word, Word> result;
                if (dest_mode.to_int32() == -3) {
                    result = regs[dest_reg.to_int32() + 4].sub_with_carry(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                    regs[dest_reg.to_int32() + 4] = result.first;
                }
                else if (dest_mode.to_int32() == -2) {
                    result = memory.get_word(imm).sub_with_carry(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                    memory.set_word(imm, result.first);
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
                Word dest_mode = ins.get_trit_range(10, 11);
                Word dest_reg = ins.get_trit_range(8, 9);

                Word src_mode = ins.get_trit_range(6, 7);
                Word src_reg = ins.get_trit_range(4, 5);

                Word carry = Word::from_int32(flags.get_bct_trit(0) - 1);

                std::pair<Word, Word> result;
                if (dest_mode.to_int32() == -3) {
                    result = regs[dest_reg.to_int32() + 4].sub_with_carry(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                    regs[dest_reg.to_int32() + 4] = result.first - carry;
                }
                else if (dest_mode.to_int32() == -2) {
                    result = memory.get_word(imm).sub_with_carry(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                    memory.set_word(imm, result.first - carry);
                }
                else {
                    Word addr = regs[dest_reg.to_int32() + 4] + imm;
                    result = memory.get_word(addr).sub_with_carry(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                    memory.set_word(addr, result.first - carry);
                }
                set_sign_flag(cycles, memory, result.first);
                flags.set_bct_trit(0, result.second.get_bct());
                break;
            }
            case INS_MUL: {
                Word src_mode = ins.get_trit_range(6, 7);
                Word src_reg = ins.get_trit_range(4, 5);
                std::pair<Word, Word> result = regs[REG_AX].mul32(get_addr_mode(cycles, memory, src_mode, src_reg, imm));
                regs[REG_AX] = result.first;
                regs[REG_DX] = result.second;
                set_sign_flag(cycles, memory, result.first);
                break;
            }
            case INS_DIV: {
                Word src_mode = ins.get_trit_range(6, 7);
                Word src_reg = ins.get_trit_range(4, 5);
                std::pair<Word, Word> result = regs[0].divmod(get_addr_mode(cycles, memory, src_mode, src_reg, imm));
                regs[REG_AX] = result.first;
                regs[REG_DX] = result.second;

                set_sign_flag(cycles, memory, result.first);
                break;
            }
            case INS_NEG: {
                Word src_mode = ins.get_trit_range(10, 11);
                Word src_reg = ins.get_trit_range(8, 9);

                Word result = -get_addr_mode(cycles, memory, src_mode, src_reg, imm);
                if (src_mode.to_int32() == -3) {
                    regs[src_reg.to_int32() + 4] = result;
                }
                else if (src_mode.to_int32() == -2) {
                    memory.set_word(imm, -regs[src_reg.to_int32() + 4]);
                }
                else {
                    Word addr = regs[src_reg.to_int32() + 4] + imm;
                    memory.set_word(addr, -result);
                }
                set_sign_flag(cycles, memory, result);
                break;
            }
            case INS_CMP: {
                Word dest_mode = ins.get_trit_range(10, 11);
                Word dest_reg = ins.get_trit_range(8, 9);

                Word src_mode = ins.get_trit_range(6, 7);
                Word src_reg = ins.get_trit_range(4, 5);

                std::pair<Word, Word> result;
                if (dest_mode.to_int32() == -3) {
                    result = regs[dest_reg.to_int32() + 4].sub_with_carry(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                }
                else if (src_mode.to_int32() == -2) {
                    result = memory.get_word(imm).sub_with_carry(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                }
                else {
                    Word addr = regs[dest_reg.to_int32() + 4] + imm;
                    result = memory.get_word(addr).sub_with_carry(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                }
                set_sign_flag(cycles, memory, result.first);
                flags.set_bct_trit(0, result.second.get_bct());
                break;
            }
            case INS_CALL: {
                regs[REG_SP] = regs[REG_SP] - Word::TWO;
                memory.set_word(regs[REG_SP], regs[REG_IP]);
                regs[REG_IP] = imm;
                break;
            }
            case INS_RET: {
                regs[REG_IP] = memory.get_word(regs[REG_SP]);
                regs[REG_SP] = regs[REG_SP] + 2;
                break;
            }
            case INS_JMP: {
                regs[REG_IP] = imm;
                break;
            }
            case INS_JL: {
                if (flags.get_bct_trit(1) < 0) {
                    regs[REG_IP] = imm;
                }
                break;
            }
            case INS_JLE: {
                if (flags.get_bct_trit(1) <= 0) {
                    regs[REG_IP] = imm;
                }
                break;
            }
            case INS_JG: {
                if (flags.get_bct_trit(1) > 0) {
                    regs[REG_IP] = imm;
                }
                break;
            }
            case INS_JGE: {
                if (flags.get_bct_trit(1) >= 0) {
                    regs[REG_IP] = imm;
                }
                break;
            }
            case INS_JE: {
                if (flags.get_bct_trit(1) == 0) {
                    regs[REG_IP] = imm;
                }
                break;
            }
            case INS_JNE: {
                if (flags.get_bct_trit(1) != 0) {
                    regs[REG_IP] = imm;
                }
                break;
            }
            case INS_JC: {
                if (flags.get_bct_trit(1) == 1) {
                    regs[REG_IP] = imm;
                }
                break;
            }
            case INS_JNC: {
                if (flags.get_bct_trit(1) != 1) {
                    regs[REG_IP] = imm;
                }
                break;
            }
            case INS_INT: {
                if (imm == Word::ZERO) {
                    Word code = regs[REG_AX].to_int32();
                    if (code == -40) {
                        std::exit(regs[REG_DX].to_int32());
                    }
                    else if (code == -39) {
                        std::cout << regs[REG_DX].to_int32();
                    }
                    else if (code == -38) {
                        std::cout << regs[REG_DX].to_ternary_str();
                    }
                }
                break;
            }
            }

        }
    }

    void CPU::exec_text(std::string& text, Mem& memory) {
       text.erase(std::remove(text.begin(), text.end(), ' '), text.end());
        reset(memory);

        for (int i = 0; i < text.size(); i += 8) {
            std::string word;
            for (int j = 0; j < 8; j++) {
                word += text.at(i + j);
            }
            memory.set_word(termite::Word::from_int32((i >> 2) - 21523360), termite::Word::from_nonary_str(word));
            // std::cout << memory.get_word(i >> 3).to_nonary_str() << '\n';
        }
        termite::Word cycles = termite::Word::from_int32(text.size() >> 2);
        execute(cycles, memory);
    }
    
}