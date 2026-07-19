#include <iostream>
#include <string>
#include <utility>
#include <cstdint>
#include <vector>
#include <cmath>
#include "../core/tryte.h"
#include "../core/word.h"
#include "cpu.h"

namespace termite {
    void Mem::initialize() {
        if (data.size() == 0) {
            for (uint32_t i = 0; i < MAX_MEM; i++) {
                data.push_back(Tryte());
            }
        }
        else {
            for (uint32_t i = 0; i < MAX_MEM; i++) {
                data[i] = Tryte();
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
        // std::cout << "dbg37 " << addr.to_int32() << '\n';
        // std::cout << "dbg38 "<< get_tryte(addr).to_int16() << '\n';
        // std::cout << "dbg39 "<< get_tryte(addr + Word::ONE).to_int16() << '\n';
        return Word(get_tryte(addr), get_tryte(addr + Word::ONE));
    }

    void Mem::set_word(const Word& addr, const Word& val) {
        data[addr.to_int32() + 21523360] = val.get_lo_tryte();
        data[addr.to_int32() + 21523361] = val.get_hi_tryte();
    }

    void CPU::reset(Mem& memory) {
        for (int i = 0; i < 9; i++) {
            regs[i] = Word::from_int32(0);
        }
        regs[REG_SP] = Word::from_int32(21523360);
        regs[REG_IP] = Word::from_int32(-21523360);
        flags = Word::from_int32(0);
        memory.initialize();
    }

    Tryte CPU::fetch_tryte(Word& cycles, Mem& memory) {
        Tryte data = memory.get_tryte(regs[REG_IP]);
        regs[REG_IP] = regs[REG_IP] + Word::ONE;
        cycles = cycles - Word::ONE;
        return data;
    }

    Word CPU::fetch_word(Word& cycles, Mem& memory) {
        // std::cout << "! " << regs[REG_IP].to_nonary_str() << '\n';
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

        void CPU::set_sign_flag_float(Word& cycles, Mem& memory, const TerFloat& result) {
        if (result < TerFloat::ZERO) {
            flags.set_bct_trit(1, 0);
        }
        else if (result == TerFloat::ZERO) {
            flags.set_bct_trit(1, 1);
        }
        else {
            flags.set_bct_trit(1, 2);
        }
    }


    void CPU::print_state() {
        std::cout << "*** ip = " << regs[REG_IP].to_int32() << '\n';
        std::cout << "ax = " << regs[REG_AX].to_int32() << '\n';
        std::cout << "bx = " << regs[REG_BX].to_int32() << '\n';
        std::cout << "cx = " << regs[REG_CX].to_int32() << '\n';
        std::cout << "sp = " << regs[REG_SP].to_int32() << '\n';
        std::cout << "bp = " << regs[REG_BP].to_int32() << '\n';
        std::cout << "di = " << regs[REG_DI].to_int32() << '\n';
        std::cout << "si = " << regs[REG_SI].to_int32() << '\n';
        std::cout << "dx = " << regs[REG_DX].to_int32() << '\n';
        std::cout << "ip = " << regs[REG_IP].to_int32() << '\n';
        std::cout << "flags = " << flags.to_ternary_str() << '\n';
    }

    void CPU::execute(Word& cycles, Mem& memory, bool verbose) {
        while (cycles > Word::ZERO) {
            if (verbose) {
                print_state();
            }

            Word ins = fetch_word(cycles, memory);
            Word imm = fetch_word(cycles, memory);
            Word imm2 = fetch_word(cycles, memory);
            Word opcode = ins.get_trit_range(12, 15);
            // std::cout << "dbg121 " << opcode.to_int32() << '\n';
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
                // std::cout << "dbg143 " << regs[REG_SP].to_int32() << '\n';
                break;
            }
            case INS_PUSH: {
                Word src_mode = ins.get_trit_range(10, 11);
                Word src_reg = ins.get_trit_range(8, 9);

                // std::cout << "dbg153 OLD REG SP: " <<  regs[REG_SP].to_int32() << '\n';
                regs[REG_SP] = regs[REG_SP] - Word::TWO;
                memory.set_word(regs[REG_SP], get_addr_mode(cycles, memory, src_mode, src_reg, imm));
                break;
            }
            case INS_POP: {
                // std::cout << "dbg158 REG SP: " <<  regs[REG_SP].to_int32() << '\n';

                Word dest_mode = ins.get_trit_range(10, 11);
                Word dest_reg = ins.get_trit_range(8, 9);
                Word val_at_sp = memory.get_word(regs[REG_SP]);
                // std::cout << "dbg163 " <<  regs[REG_SP].to_int32() << '\n';

                if (dest_mode.to_int32() == -3) {
                    regs[dest_reg.to_int32() + 4] = val_at_sp;

                }
                else if (dest_mode.to_int32() == -2) {
                    memory.set_word(imm, val_at_sp);
                }
                else {
                    Word addr = regs[dest_reg.to_int32()] + imm;
                    memory.set_word(addr, val_at_sp);
                }
                // std::cout << "dbg171 MIDDLE REG SP: " <<  regs[REG_SP].to_int32() << '\n';
                regs[REG_SP] = regs[REG_SP] + Word::TWO;
                // std::cout << "dbg172 NEW REG SP: " <<  regs[REG_SP].to_int32() << '\n';
                break;
            }
                        // case INS_POP: {
                        //     Word dest_mode = ins.get_trit_range(10, 11);
                        //     Word dest_reg = ins.get_trit_range(8, 9);
                        //     Word val_at_sp = memory.get_word(regs[REG_SP]);
                        //     if (dest_mode.to_int32() == -3) {
                        //         regs[dest_reg.to_int32() + 4] = val_at_sp;
                        //     }
                        //     else if (dest_mode.to_int32() == -2) {
                        //         memory.set_word(imm, val_at_sp);
                        //     }
                        //     else {
                        //         Word addr = regs[dest_reg.to_int32() + 4] + imm;
                        //         memory.set_word(addr, val_at_sp);
                        //     }
                        //     regs[REG_SP] = regs[REG_SP] + Word::TWO;
                        //     break;
                        // }
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
                    result = regs[dest_reg.to_int32() + 4].sub_with_borrow(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                    regs[dest_reg.to_int32() + 4] = result.first;
                }
                else if (dest_mode.to_int32() == -2) {
                    result = memory.get_word(imm).sub_with_borrow(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                    memory.set_word(imm, result.first);
                }
                else {
                    Word addr = regs[dest_reg.to_int32() + 4] + imm;
                    result = memory.get_word(addr).sub_with_borrow(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
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
                    result = regs[dest_reg.to_int32() + 4].sub_with_borrow(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                    regs[dest_reg.to_int32() + 4] = result.first - carry;
                }
                else if (dest_mode.to_int32() == -2) {
                    result = memory.get_word(imm).sub_with_borrow(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                    memory.set_word(imm, result.first - carry);
                }
                else {
                    Word addr = regs[dest_reg.to_int32() + 4] + imm;
                    result = memory.get_word(addr).sub_with_borrow(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                    memory.set_word(addr, result.first - carry);
                }
                set_sign_flag(cycles, memory, result.first);
                flags.set_bct_trit(0, result.second.get_bct());
                break;
            }
            case INS_MUL: {
                Word src_mode = ins.get_trit_range(10, 11);
                Word src_reg = ins.get_trit_range(8, 9);
                std::pair<Word, Word> result = regs[REG_AX].mul32(get_addr_mode(cycles, memory, src_mode, src_reg, imm));
                regs[REG_AX] = result.first;
                regs[REG_DX] = result.second;
                set_sign_flag(cycles, memory, result.first);
                break;
            }
            case INS_DIV: {
                Word src_mode = ins.get_trit_range(10, 11);
                Word src_reg = ins.get_trit_range(8, 9);
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
                // std::cout << "DBG485 " << regs[dest_reg.to_int32() + 4].to_int32() << '\n';
                    result = regs[dest_reg.to_int32() + 4].sub_with_borrow(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                // std::cout << "DBG487 " << get_addr_mode(cycles, memory, src_mode, src_reg, imm2).to_int32() << '\n';
                }
                else if (src_mode.to_int32() == -2) {
                    result = memory.get_word(imm).sub_with_borrow(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                }
                else {
                    Word addr = regs[dest_reg.to_int32() + 4] + imm;
                    result = memory.get_word(addr).sub_with_borrow(get_addr_mode(cycles, memory, src_mode, src_reg, imm2));
                }

                // std::cout << "DBG495 " << result.first.to_int32() << '\n';
                set_sign_flag(cycles, memory, result.first);
                flags.set_bct_trit(0, result.second.get_bct());
                break;
            }
            case INS_CALL: {
                // std::cout << "dbg455 " << regs[REG_SP].to_int32() << '\n';
                regs[REG_SP] = regs[REG_SP] - Word::TWO;
                memory.set_word(regs[REG_SP], regs[REG_IP]);
                cycles = cycles + (regs[REG_IP] - imm);
                regs[REG_IP] = imm;
                break;
            }
            case INS_RET: {
                // std::cout << "dbg465 " << regs[REG_SP].to_int32() << '\n';
                Word val_at_sp = memory.get_word(regs[REG_SP]);
                cycles = cycles + (regs[REG_IP] - val_at_sp);
                regs[REG_IP] = val_at_sp;
                regs[REG_SP] = regs[REG_SP] + Word::TWO;
                break;
            }
            case INS_JMP: {
                cycles = cycles + (regs[REG_IP] - imm);
                regs[REG_IP] = imm;
                break;
            }
            case INS_JL: {
                if (flags.get_bct_trit(1) < 1) {
                    cycles = cycles + (regs[REG_IP] - imm);
                    regs[REG_IP] = imm;
                }
                break;
            }
            case INS_JLE: {
                if (flags.get_bct_trit(1) <= 1) {
                    cycles = cycles + (regs[REG_IP] - imm);
                    regs[REG_IP] = imm;
                }
                break;
            }
            case INS_JG: {
                if (flags.get_bct_trit(1) > 1) {
                    cycles = cycles + (regs[REG_IP] - imm);
                    regs[REG_IP] = imm;
                }
                break;
            }
            case INS_JGE: {
                if (flags.get_bct_trit(1) >= 1) {
                    cycles = cycles + (regs[REG_IP] - imm);
                    regs[REG_IP] = imm;
                }
                break;
            }
            case INS_JE: {
                if (flags.get_bct_trit(1) == 1) {
                    cycles = cycles + (regs[REG_IP] - imm);
                    regs[REG_IP] = imm;
                }
                break;
            }
            case INS_JNE: {
                if (flags.get_bct_trit(1) != 1) {
                    cycles = cycles + (regs[REG_IP] - imm);
                    regs[REG_IP] = imm;
                }
                break;
            }
            case INS_JC: {
                if (flags.get_bct_trit(0) != 1) {
                    cycles = cycles + (regs[REG_IP] - imm);
                    regs[REG_IP] = imm;
                }
                break;
            }
            case INS_JNC: {
                if (flags.get_bct_trit(0) == 1) {
                    cycles = cycles + (regs[REG_IP] - imm);
                    regs[REG_IP] = imm;
                }
                break;
            }
            case INS_INT: {
                if (imm == Word::ZERO) {
                    int code = regs[REG_AX].to_int32();
                    // std::cerr << "INT $0 with code (ax): " << code << "\n";
                    // std::cerr << "Value in DX: " << regs[REG_DX].to_int32() << "\n";
                    if (code == -40) { // DD
                        std::exit(regs[REG_DX].to_int32());
                    }
                    else if (code == -39) { // DC
                        // std::cout << "dbg571 THE CODE -39 PATH HAS HIT" << '\n';
                        std::cout << regs[REG_DX].to_int32();
                    }
                    else if (code == -38) { // DB
                        std::cout << regs[REG_DX].to_ternary_str();
                    }
                    else if (code == -37) { // DA
                        std::cout << regs[REG_DX].to_nonary_str();
                    }
                    else if (code == -36) { // D0
                        std::cout << (char)(regs[REG_DX].get_lo_tryte().to_int16());
                    }
                    else if (code == -35) { // D1
                        std::cout << (char)(regs[REG_DX].get_hi_tryte().to_int16());
                    }
                    else if (code == -34) { // D2
                        print_state();
                    }
                    else if (code == -33) { // D3
                        std::string in;
                        std::cin >> in;
                        regs[REG_DX] = Word::from_int32(std::stoi(in));
                    }
                    else if (code == -32) { // D4
                        std::string in;
                        std::cin >> in;
                        regs[REG_DX] = Word::from_ternary_str(in);
                    }
                    else if (code == -31) { // CD
                        std::string in;
                        std::cin >> in;
                        regs[REG_DX] = Word::from_nonary_str(in);
                    }
                    else if (code == -30) { // CC
                        char in;
                        std::cin >> in;
                        regs[REG_DX] = Word::from_int32(in);
                        // regs[REG_DX] = Word::from_int32(Tryte::from_int16(in).get_bct() + ((regs[REG_DX].get_hi_tryte().get_bct()) << 16));
                    }
                    else if (code == -29) { // CB
                        auto now = std::chrono::system_clock::now();
                        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
                        long long shifted_count = ms.count() + 21523360;
                        long long lo = shifted_count % 43046721;
                        long long hi = shifted_count / 43046721;
                        lo -= 21523360;
                        regs[REG_AX] = Word::from_int32(lo);
                        regs[REG_DX] = Word::from_int32(hi);
                    } else if (code == -28) { // CA
                        std::cout << st.top().to_str();
                    }
                }
                break;
            }
            case INS_XCHG: {
                Word dest_mode = ins.get_trit_range(10, 11);
                Word dest_reg = ins.get_trit_range(8, 9);

                Word src_mode = ins.get_trit_range(6, 7);
                Word src_reg = ins.get_trit_range(4, 5);

                if (dest_mode.to_int32() == -3 && src_mode.to_int32() == -3) {
                    Word temp = regs[dest_reg.to_int32() + 4];
                    regs[dest_reg.to_int32() + 4] = regs[src_reg.to_int32() + 4];
                    regs[src_reg.to_int32() + 4] = temp;
                }

                break;
            }
            case INS_FLD: {
                Word src_mode = ins.get_trit_range(10, 11);
                Word src_reg = ins.get_trit_range(8, 9);
                Word addr = get_addr_mode(cycles, memory, src_mode, src_reg, imm);
                // std::cout << addr.to_nonary_str();
                // std::cout << "dbg647 " << memory.get_word(addr).to_nonary_str();
                // std::cout << "dbg648 " << memory.get_word(addr + Word::TWO).to_nonary_str();

                st.push(TerFloat(memory.get_word(addr), memory.get_word(addr + Word::TWO)));
                break;
            }
            case INS_FST: {

                TerFloat top = st.top();

                Word dest_mode = ins.get_trit_range(10, 11);
                Word dest_reg = ins.get_trit_range(8, 9);
                Word addr = get_addr_mode(cycles, memory, dest_mode, dest_reg, imm);

                memory.set_word(addr, top.significand);
                memory.set_word(addr + Word::TWO, top.exponent);
                // std::cout << "dbg143 " << regs[REG_SP].to_int32() << '\n';
                break;
            }
            case INS_FSTP: {

                TerFloat top = st.top();
                st.pop();

                Word dest_mode = ins.get_trit_range(10, 11);
                Word dest_reg = ins.get_trit_range(8, 9);
                Word addr = get_addr_mode(cycles, memory, dest_mode, dest_reg, imm2);

                memory.set_word(addr, top.significand);
                memory.set_word(addr + Word::TWO, top.exponent);
                // std::cout << "dbg143 " << regs[REG_SP].to_int32() << '\n';
                break;
            }
            case INS_FADD: {
                TerFloat b = st.top();
                st.pop();
                TerFloat a = st.top();
                st.pop();
                TerFloat result = a + b;
                st.push(result);
                set_sign_flag_float(cycles, memory, result);
                break;
            }
            case INS_FSUB: {
                TerFloat b = st.top();
                st.pop();
                TerFloat a = st.top();
                st.pop();
                TerFloat result = a - b;
                st.push(result);
                set_sign_flag_float(cycles, memory, result);
                break;
            }
            case INS_FMUL: {
                TerFloat b = st.top();
                st.pop();
                TerFloat a = st.top();
                st.pop();
                TerFloat result = a * b;
                st.push(result);
                set_sign_flag_float(cycles, memory, result);
                break;
            }
            case INS_FDIV: {
                TerFloat b = st.top();
                st.pop();
                TerFloat a = st.top();
                st.pop();
                TerFloat result = a / b;
                st.push(result);
                set_sign_flag_float(cycles, memory, result);
                break;
            }
            case INS_FSQRT: {
                TerFloat a = st.top();
                st.pop();
                TerFloat result = a.sqrt();
                st.push(result);
                set_sign_flag_float(cycles, memory, result);
                break;
            }
            case INS_FSIN: {
                TerFloat a = st.top();
                st.pop();
                TerFloat result = a.sin();
                st.push(result);
                set_sign_flag_float(cycles, memory, result);
                break;
            }
            case INS_FCOS: {
                TerFloat a = st.top();
                st.pop();
                TerFloat result = a.cos();
                st.push(result);
                set_sign_flag_float(cycles, memory, result);
                break;
            }
            case INS_FTAN: {
                TerFloat a = st.top();
                st.pop();
                TerFloat result = a.tan();
                st.push(result);
                set_sign_flag_float(cycles, memory, result);
                break;
            }
        case INS_FATAN: {
            TerFloat x = st.top(); st.pop();
            TerFloat y = st.top(); st.pop();

            TerFloat result;

            if (x == TerFloat::ZERO) {
                if (y == TerFloat::ZERO) result = TerFloat::NAN_;
                else if (y > TerFloat::ZERO) result = TerFloat::HALF_PI;
                else result = -TerFloat::HALF_PI;
            } else {
                result = (y / x).atan();

                if (x < TerFloat::ZERO) {
                    if (y >= TerFloat::ZERO) result = result + TerFloat::PI;
                    else result = result - TerFloat::PI;
                }
            }

            st.push(result);
            set_sign_flag_float(cycles, memory, result);
            break;
        }
            // case INS_FATAN: {
            //     TerFloat b = st.top();
            //     st.pop();
            //     TerFloat a = st.top();
            //     st.pop();
            //     TerFloat result = (b/a).atan();
            //     st.push(result);
            //     set_sign_flag_float(cycles, memory, result);
            //     break;
            // }
            case INS_FEXP: {
                TerFloat a = st.top();
                st.pop();
                TerFloat result = a.exp();
                st.push(result);
                set_sign_flag_float(cycles, memory, result);
                break;
            }
            case INS_FLOG: {
                TerFloat a = st.top();
                st.pop();
                TerFloat result = a.log();
                st.push(result);
                set_sign_flag_float(cycles, memory, result);
                break;
            }
            case INS_FABS: {
                TerFloat a = st.top();
                st.pop();
                TerFloat result = a.abs();
                st.push(result);
                set_sign_flag_float(cycles, memory, result);
                break;
            }
            case INS_FFLOOR: {
                TerFloat a = st.top();
                st.pop();
                TerFloat result = a.floor();
                st.push(result);
                set_sign_flag_float(cycles, memory, result);
                break;
            }
            case INS_FCMP: {
                TerFloat b = st.top();
                st.pop();
                TerFloat a = st.top();
                st.pop();
                TerFloat result = a - b;
                if(a == TerFloat::NEGATIVE_INFINITY) {
                    if(b == TerFloat::NEGATIVE_INFINITY) {
                        result = TerFloat::from_double(0.0);
                    } else {
                        result = TerFloat::from_double(1.0);
                    }
                } else if(a == TerFloat::POSITIVE_INFINITY) {
                    if(b == TerFloat::POSITIVE_INFINITY) {
                        // std::cout << "!!!!DBG842" << '\n';
                        result = TerFloat::from_double(0.0);
                    } else {
                        result = TerFloat::from_double(-1.0);
                    }
                }

                // like fsub but doesn't actually push the result, just sets the flag
                set_sign_flag_float(cycles, memory, result);
                break;
            }
case INS_LDT: {
    Word src_mode = ins.get_trit_range(10, 11);
    Word src_reg  = ins.get_trit_range(8, 9);

    Tryte loaded_tryte;

        if (src_mode.to_int32() == -4) {
        loaded_tryte = imm.get_lo_tryte();
    } else if (src_mode.to_int32() == -3) {
        loaded_tryte = regs[src_reg.to_int32() + 4].get_lo_tryte();
    }
    else if (src_mode.to_int32() == -2) {
        loaded_tryte = memory.get_tryte(imm);
    }
    else {
        Word addr = regs[src_reg.to_int32() + 4] + imm;
        loaded_tryte = memory.get_tryte(addr);
    }

    regs[REG_AX] = Word(loaded_tryte, Tryte::from_int16(0));
    // std::cout << "DBG875 " << loaded_tryte.to_int16() << '\n';
    // std::cout << "DBG876 " << regs[REG_AX].to_int32() << '\n';
    break;
}
            //             case INS_LDT: {
            //     Word src_mode = ins.get_trit_range(10, 11);
            //     Word src_reg = ins.get_trit_range(8, 9);
            //     Tryte loaded_tryte = get_addr_mode(cycles, memory, src_mode, src_reg, imm).get_lo_tryte();
            //     Word new_ax = Word(loaded_tryte, Tryte::from_int16(0));
            //     regs[REG_AX] = new_ax;
            //     break;
            // }
                                    case INS_STT: {
                Word ax_word = regs[REG_AX];
                Tryte ax_lo_tryte = ax_word.get_lo_tryte();
Word dest_mode = ins.get_trit_range(10, 11);
                Word dest_reg = ins.get_trit_range(8, 9);

                

                if (dest_mode.to_int32() == -3) {
                    regs[dest_reg.to_int32() + 4] = Word(ax_lo_tryte, Tryte::from_int16(0));
                }
                else if (dest_mode.to_int32() == -2) {
                    memory.set_tryte(imm, ax_lo_tryte);
                }
                else {
                    Word addr = regs[dest_reg.to_int32() + 4] + imm;
                    memory.set_tryte(addr, ax_lo_tryte);
                }
                break;
            }
            case INS_FILD: {
                Word src_mode = ins.get_trit_range(10, 11);
                Word src_reg = ins.get_trit_range(8, 9);
                Word addr = get_addr_mode(cycles, memory, src_mode, src_reg, imm);
                st.push(TerFloat::from_double((double)((memory.get_word(addr)).to_int32())));
                break;
            }
            case INS_FIST: {
       
                TerFloat top = st.top();

                Word dest_mode = ins.get_trit_range(10, 11);
                Word dest_reg = ins.get_trit_range(8, 9);
                Word addr = get_addr_mode(cycles, memory, dest_mode, dest_reg, imm);

                memory.set_word(addr, Word::from_int32((int32_t)(top.to_double())));
                break;
            }
            case INS_FISTP: {
                TerFloat top = st.top();
                st.pop();
                Word dest_mode = ins.get_trit_range(10, 11);
                Word dest_reg = ins.get_trit_range(8, 9);
                Word addr = get_addr_mode(cycles, memory, dest_mode, dest_reg, imm);

                memory.set_word(addr, Word::from_int32((int32_t)(top.to_double())));
                break;
            }
            case INS_FNEG: {
                TerFloat a = st.top();
                st.pop();
                TerFloat result = -a;
                st.push(result);
                set_sign_flag_float(cycles, memory, result);
                break;
            }      
            }
        }


    }

    void CPU::exec_text(std::string& text, Mem& memory, bool verbose) {
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
        execute(cycles, memory, verbose);
    }

}