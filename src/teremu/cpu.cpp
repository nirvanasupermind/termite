#include <vector>
#include <iostream>
#include <utility>
#include <tuple>

#include "../core/tryte.h"
#include "../core/word.h"
#include "./mem.h"
#include "./cpu.h"

namespace termite {
    CPU::CPU() {
        reset();
    }

    void CPU::reset() {
        registers[PC] = Word::from_int32(-(Mem::MAX_MEM >> 1));
        registers[SP] = Word::from_int32(Mem::MAX_MEM >> 1);
        mem.initialize();
    }

    Word CPU::fetch_word(int& cycles) {
        Word data = mem.get_word(registers[PC]);
        registers[PC] = registers[PC] + Word::TWO;
        cycles--;
        return data;
    }

    void CPU::set_sign_flag(Word& result) {
        int32_t result_int32 = result.to_int32();
        psr.set_bct_trit(SF, (result_int32 < 0) ? 0b00 : ((result_int32 == 0) ? 0b01 : 0b10));
    }

    void CPU::print_state() const {
        std::cout << "********* Program counter = " << registers[PC].to_int32() << '\n';
        for (int i = 0; i < 27; i++) {
            std::cout << "r" << i - 13 << " = " << registers[i].to_int32() << '\n';
        }
    }

    void CPU::execute(int cycles, bool verbose) {
        if (verbose) {
            print_state();
        }

        while (cycles > 0) {
            Word instr = fetch_word(cycles);
            int opcode = instr.get_trit_range(12, 15).to_int32();
            switch (opcode) {
            case MOV: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                int rs_idx = instr.get_trit_range(6, 8).to_int32() + 13;
                registers[rd_idx] = registers[rs_idx];
                break;
            }
            case MOVI: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                std::cout << "YES " << rd_idx << '\n';
                Word imm = instr.get_trit_range(0, 8);
                registers[rd_idx] = imm;
                break;
            }
            case MOVPS: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                registers[rd_idx] = psr;
                break;
            }
            case LD: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                int rs_idx = instr.get_trit_range(6, 8).to_int32() + 13;
                Word imm = instr.get_trit_range(0, 5);
                registers[rd_idx] = mem.get_word(registers[rs_idx] + imm);
                break;
            }
            case ST: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                int rs_idx = instr.get_trit_range(6, 8).to_int32() + 13;
                Word imm = instr.get_trit_range(0, 5);
                mem.set_word(registers[rs_idx] + imm, registers[rd_idx]);
                break;
            }
            case ADD: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                int rs_idx = instr.get_trit_range(6, 8).to_int32() + 13;
                int rt_idx = instr.get_trit_range(3, 5).to_int32() + 13;
                Word sum;
                uint8_t carry;
                std::tie(sum, carry) = registers[rs_idx].add_with_carry(registers[rt_idx]);
                registers[rd_idx] = sum;
                set_sign_flag(sum);
                psr.set_bct_trit(CF, carry);
                break;
            }
            case ADDI: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                int rs_idx = instr.get_trit_range(6, 8).to_int32() + 13;
                Word imm = instr.get_trit_range(0, 5);
                Word sum;
                uint8_t carry;
                std::tie(sum, carry) = registers[rs_idx].add_with_carry(imm);
                registers[rd_idx] = sum;
                set_sign_flag(sum);
                psr.set_bct_trit(CF, carry);
                break;
            }
            case ADDC: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                int rs_idx = instr.get_trit_range(6, 8).to_int32() + 13;
                int rt_idx = instr.get_trit_range(3, 5).to_int32() + 13;
                Word sum;
                uint8_t carry;
                std::tie(sum, carry) = (registers[rs_idx] + registers[rt_idx]).add_with_carry(CF);
                registers[rd_idx] = sum;
                set_sign_flag(sum);
                psr.set_bct_trit(CF, carry);
                break;
            }
            case ADDCI: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                int rs_idx = instr.get_trit_range(6, 8).to_int32() + 13;
                Word imm = instr.get_trit_range(0, 5);
                Word sum;
                uint8_t carry;
                std::tie(sum, carry) = (registers[rs_idx] + imm).add_with_carry(CF);
                registers[rd_idx] = sum;
                set_sign_flag(sum);
                psr.set_bct_trit(CF, carry);
                break;
            }
            case SUB: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                int rs_idx = instr.get_trit_range(6, 8).to_int32() + 13;
                int rt_idx = instr.get_trit_range(3, 5).to_int32() + 13;
                Word diff;
                uint8_t carry;
                std::tie(diff, carry) = registers[rs_idx].sub_with_carry(registers[rt_idx]);
                registers[rd_idx] = diff;
                set_sign_flag(diff);
                psr.set_bct_trit(CF, carry);
                break;
            }
            case SUBI: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                int rs_idx = instr.get_trit_range(6, 8).to_int32() + 13;
                Word imm = instr.get_trit_range(0, 5);
                Word diff;
                uint8_t carry;
                std::tie(diff, carry) = registers[rs_idx].sub_with_carry(imm);
                registers[rd_idx] = diff;
                set_sign_flag(diff);
                psr.set_bct_trit(CF, carry);
                break;
            }
            case SUBC: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                int rs_idx = instr.get_trit_range(6, 8).to_int32() + 13;
                int rt_idx = instr.get_trit_range(3, 5).to_int32() + 13;
                Word diff;
                uint8_t carry;
                std::tie(diff, carry) = (registers[rs_idx] - registers[rt_idx]).sub_with_carry(CF);
                registers[rd_idx] = diff;
                set_sign_flag(diff);
                psr.set_bct_trit(CF, carry);
                break;
            }
            case SUBCI: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                int rs_idx = instr.get_trit_range(8, 6).to_int32() + 13;
                Word imm = instr.get_trit_range(5, 0);
                Word diff;
                uint8_t carry;
                std::tie(diff, carry) = (registers[rs_idx] - imm).sub_with_carry(CF);
                registers[rd_idx] = diff;
                set_sign_flag(diff);
                psr.set_bct_trit(CF, carry);
                break;
            }
            case MUL: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                int rs_idx = instr.get_trit_range(8, 6).to_int32() + 13;
                int rt_idx = instr.get_trit_range(3, 5).to_int32() + 13;
                Word result = registers[rs_idx] * registers[rt_idx];
                registers[rd_idx] = result;
                set_sign_flag(result);
                break;
            }
            case MULI: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                int rs_idx = instr.get_trit_range(8, 6).to_int32() + 13;
                Word imm = instr.get_trit_range(5, 0);
                Word result = registers[rs_idx] * imm;
                registers[rd_idx] = result;
                set_sign_flag(result);
                break;
            }
            case NOT: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                int rs_idx = instr.get_trit_range(8, 6).to_int32() + 13;
                Word result = ~registers[rs_idx];
                registers[rd_idx] = result;
                set_sign_flag(result);
                break;
            }
            case NOTI: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                Word imm = instr.get_trit_range(0, 8);
                Word result = ~imm;
                registers[rd_idx] = result;
                set_sign_flag(result);
                break;
            }
            case AND: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                int rs_idx = instr.get_trit_range(8, 6).to_int32() + 13;
                int rt_idx = instr.get_trit_range(3, 5).to_int32() + 13;
                Word result = registers[rs_idx] & registers[rt_idx];
                registers[rd_idx] = result;
                set_sign_flag(result);
                break;
            }
            case ANDI: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                int rs_idx = instr.get_trit_range(8, 6).to_int32() + 13;
                Word imm = instr.get_trit_range(5, 0);
                Word result = registers[rs_idx] & imm;
                registers[rd_idx] = result;
                set_sign_flag(result);
                break;
            }
            case OR: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                int rs_idx = instr.get_trit_range(8, 6).to_int32() + 13;
                int rt_idx = instr.get_trit_range(3, 5).to_int32() + 13;
                Word result = registers[rs_idx] | registers[rt_idx];
                registers[rd_idx] = result;
                set_sign_flag(result);
                break;
            }
            case ORI: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                int rs_idx = instr.get_trit_range(8, 6).to_int32() + 13;
                Word imm = instr.get_trit_range(5, 0);
                Word result = registers[rs_idx] | imm;
                registers[rd_idx] = result;
                set_sign_flag(result);
                break;
            }
            case LSH: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                int rs_idx = instr.get_trit_range(8, 6).to_int32() + 13;
                int rt_idx = instr.get_trit_range(3, 5).to_int32() + 13;
                Word result = registers[rs_idx] << registers[rt_idx];
                registers[rd_idx] = result;
                set_sign_flag(result);
                break;
            }
            case LSHI: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                int rs_idx = instr.get_trit_range(8, 6).to_int32() + 13;
                Word imm = instr.get_trit_range(5, 0);
                Word result = registers[rs_idx] << imm;
                registers[rd_idx] = result;
                set_sign_flag(result);
                break;
            }
            case RSH: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                int rs_idx = instr.get_trit_range(8, 6).to_int32() + 13;
                int rt_idx = instr.get_trit_range(3, 5).to_int32() + 13;
                Word result = registers[rs_idx] >> registers[rt_idx];
                registers[rd_idx] = result;
                set_sign_flag(result);
                break;
            }
            case RSHI: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                int rs_idx = instr.get_trit_range(8, 6).to_int32() + 13;
                Word imm = instr.get_trit_range(5, 0);
                Word result = registers[rs_idx] >> imm;
                registers[rd_idx] = result;
                set_sign_flag(result);
                break;
            }
            case CMP: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                int rs_idx = instr.get_trit_range(8, 6).to_int32() + 13;
                Word diff;
                uint8_t carry;
                std::tie(diff, carry) = registers[rd_idx].sub_with_carry(registers[rs_idx]);
                set_sign_flag(diff);
                psr.set_bct_trit(CF, carry);
                break;
            }
            case CMPI: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                Word imm = instr.get_trit_range(0, 8);
                Word diff;
                uint8_t carry;
                std::tie(diff, carry) = registers[rd_idx].sub_with_carry(imm);
                set_sign_flag(diff);
                psr.set_bct_trit(CF, carry);
                break;
            }
            case JMP: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                registers[PC] = registers[rd_idx];
                cycles += (registers[PC] - registers[rd_idx]).to_int32();
                break;
            }
            case JEQ: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                if (psr.get_bct_trit(SF) == 0b01) {
                    registers[PC] = registers[rd_idx];
                    cycles += (registers[PC] - registers[rd_idx]).to_int32();
                }
                break;
            }
            case JNE: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                if (psr.get_bct_trit(SF) != 0b01) {
                    registers[PC] = registers[rd_idx];
                    cycles += (registers[PC] - registers[rd_idx]).to_int32();
                }
                break;
            }
            case JLT: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                if (psr.get_bct_trit(SF) < 0b01) {
                    registers[PC] = registers[rd_idx];
                    cycles += (registers[PC] - registers[rd_idx]).to_int32();
                }
                break;
            }
            case JLE: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                if (psr.get_bct_trit(SF) <= 0b01) {
                    registers[PC] = registers[rd_idx];
                    cycles += (registers[PC] - registers[rd_idx]).to_int32();
                }
                break;
            }
            case JGT: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                if (psr.get_bct_trit(SF) > 0b01) {
                    registers[PC] = registers[rd_idx];
                    cycles += (registers[PC] - registers[rd_idx]).to_int32();
                }
                break;
            }
            case JGE: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                if (psr.get_bct_trit(SF) >= 0b01) {
                    registers[PC] = registers[rd_idx];
                    cycles += (registers[PC] - registers[rd_idx]).to_int32();
                }
                break;
            }
            case PUSH: {
                Word imm = instr.get_trit_range(0, 11);
                registers[SP] = registers[SP] - Word::TWO;
                mem.set_word(registers[SP], imm);
                break;
            }
            case POP: {
                int rd_idx = instr.get_trit_range(9, 11).to_int32() + 13;
                registers[rd_idx] = mem.get_word(registers[SP]);
                registers[SP] = registers[SP] + Word::TWO;
                break;
            }
            case CALL: {
                Word imm = instr.get_trit_range(0, 11);
                registers[SP] = registers[SP] - 2;
                mem.set_word(registers[SP], registers[PC]);
                registers[PC] = imm;
                break;
            }
            case RET: {
                registers[PC] = mem.get_word(registers[SP]);
                registers[SP] = registers[SP] + Word::TWO;
                break;
            }
            case SYS: {
                Word imm = instr.get_trit_range(0, 11);
                if (imm.to_int32() == 0) {
                    std::cout << registers[0].to_int32() << '\n';
                }
                else if (imm.to_int32() == 1) {
                    std::cout << registers[0].str() << '\n';
                }
                break;
            }
            default: {
                throw std::string("Invalid opcode");
                break;
            }
            }
            if (verbose) {
                print_state();
            }
        }
    }
} // namespace termite