#include <iostream>
#include <iomanip>
#include "trit.h"
#include "tryte.h"
#include "word.h"
#include "mem.h"
#include "cpu.h"

namespace termite {
    void CPU::reset() {
        std::fill(registers, registers + 27, 0);
        memory.data = std::vector<Tryte>(WORD_MAX);
    }

    Tryte CPU::fetch_tryte(int& cycles) {
        Tryte tryte = memory.get_tryte(registers[PC]);
        registers[PC] = (registers[PC] + Word::from_int(1)).first;
        cycles--;
        return tryte;
    }

    Word CPU::fetch_word(int& cycles) {
        Word word = memory.get_word(registers[PC]);
        registers[PC] = (registers[PC] + Word::from_int(2)).first;
        cycles--;
        return word;
    }

    void CPU::execute(int cycles) {
        while (cycles > 0) {
            Word ins = fetch_word(cycles);
            Word opcode = ins.get_trit_range(12, 4);
            switch (opcode.to_int()) {
            case MOV: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                registers[rd.to_int()] = registers[rs.to_int()];
                break;
            }
            case MOVI: {
                Word rd = ins.get_trit_range(9, 3);
                Word imm = ins.get_trit_range(0, 6);
                registers[rd.to_int()] = imm.to_int();
                break;
            }
            case LDR: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                registers[rd.to_int()] = memory.get_word(rs.to_int() + imm.to_int());
                break;
            }
            case STR: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                memory.set_word(rd.to_int() + imm.to_int(), rs.to_int());
                break;
            }
            case NEG: {
                Word rd = ins.get_trit_range(9, 3);
                Word result = -registers[rd.to_int()];
                registers[rd.to_int()] = -registers[rd.to_int()];
                set_sign_flag(result);
                break;
            }
            case ADD: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word rt = ins.get_trit_range(3, 3);
                std::pair<Word, Trit> sum = registers[rs.to_int()] + registers[rt.to_int()];
                registers[rd.to_int()] = sum.first;
                flags.set_trit(C, sum.second);
                set_sign_flag(sum.first);
                break;
            }
            case ADDI: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                std::pair<Word, Trit> sum = registers[rs.to_int()] + imm;
                registers[rd.to_int()] = sum.first;
                flags.set_trit(C, sum.second);
                set_sign_flag(sum.first);
                break;
            }
            case ADDC: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word rt = ins.get_trit_range(3, 3);
                std::pair<Word, Trit> sum = registers[rs.to_int()] + registers[rt.to_int()];
                registers[rd.to_int()] = (sum.first + Word::from_int(flags.get_trit(C).val)).first;
                flags.set_trit(C, sum.second);
                set_sign_flag(sum.first);
                break;
            }
            case ADDCI: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                std::pair<Word, Trit> sum = registers[rs.to_int()] + imm;
                registers[rd.to_int()] = (sum.first + Word::from_int(flags.get_trit(C).val)).first;
                flags.set_trit(C, sum.second);
                set_sign_flag(sum.first);
                break;
            }
            case SUB: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word rt = ins.get_trit_range(3, 3);
                std::pair<Word, Trit> diff = registers[rs.to_int()] - registers[rt.to_int()];
                registers[rd.to_int()] = diff.first;
                flags.set_trit(C, diff.second);
                set_sign_flag(diff.first);
                break;
            }
            case SUBI: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                std::pair<Word, Trit> diff = registers[rs.to_int()] - imm;
                registers[rd.to_int()] = diff.first;
                flags.set_trit(C, diff.second);
                set_sign_flag(diff.first);
                break;
            }
            case SUBC: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word rt = ins.get_trit_range(3, 3);
                std::pair<Word, Trit> diff = registers[rs.to_int()] - registers[rt.to_int()];
                registers[rd.to_int()] = (diff.first + Word::from_int(flags.get_trit(C).val)).first;
                flags.set_trit(C, diff.second);
                set_sign_flag(diff.first);
                break;
            }
            case SUBCI: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                std::pair<Word, Trit> diff = registers[rs.to_int()] - imm;
                registers[rd.to_int()] = (diff.first + Word::from_int(flags.get_trit(C).val)).first;
                flags.set_trit(C, diff.second);
                set_sign_flag(diff.first);
                break;
            }
            case MUL: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word rt = ins.get_trit_range(3, 3);
                Word result = registers[rs.to_int()] * registers[rt.to_int()];
                registers[rd.to_int()] = result;
                set_sign_flag(result);
                break;
            }
            case MULI: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                Word result = registers[rs.to_int()] * registers[rt.to_int()];
                registers[rd.to_int()] = result;
                set_sign_flag(result);
                break;
            }
            case NOT: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word result = ~registers[rs.to_int()];;
                registers[rd.to_int()] = result;
                set_sign_flag(result);
                break;
            }
            case AND: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word rt = ins.get_trit_range(3, 3);
                Word result = registers[rs.to_int()] & registers[rt.to_int()];
                registers[rd.to_int()] = result;
                set_sign_flag(result);
                break;
            }
            case ANDI: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                Word result = registers[rs.to_int()] & registers[rt.to_int()];
                registers[rd.to_int()] = registers[rs.to_int()] & imm;
                set_sign_flag(result);   
                break;
            }
            case OR: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word rt = ins.get_trit_range(3, 3);
                Word resutl
                registers[rd.to_int()] = registers[rs.to_int()] | registers[rt.to_int()];
                break;
            }
            case ORI: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                registers[rd.to_int()] = registers[rs.to_int()] | imm;
                break;
            }
            case SL: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                registers[rd.to_int()] = registers[rs.to_int()] >> imm.to_int();
                break;
            }
            case B: {
                Word imm = ins.get_trit_range(0, 6);
                registers[PC] = (registers[PC] + imm).first;
                break;
            }
            case BEQ: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                if (rd.to_int() == rs.to_int()) {
                    registers[PC] = (registers[PC] + imm).first;
                }
                break;
            }
            case BNE: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                if (rd.to_int() != rs.to_int()) {
                    registers[PC] = (registers[PC] + imm).first;
                }
                break;
            }
            case BLT: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                if (rd.to_int() < rs.to_int()) {
                    registers[PC] = (registers[PC] + imm).first;
                }
                break;
            }
            case BLE: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                if (rd.to_int() <= rs.to_int()) {
                    registers[PC] = (registers[PC] + imm).first;
                }
                break;
            }
            case BGT: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                if (rd.to_int() > rs.to_int()) {
                    registers[PC] = (registers[PC] + imm).first;
                }
                break;
            }
            case BGE: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                if (rd.to_int() >= rs.to_int()) {
                    registers[PC] = (registers[PC] + imm).first;
                }
                break;
            }
            case BL: {
                Word imm = ins.get_trit_range(0, 6);
                registers[LR] = registers[PC];
                registers[PC] = (registers[PC] + imm).first;
                break;
            }
            case SWI: {
                Word interrupt = ins.get_trit_range(0, 12);
                if (interrupt.to_int() == 0) {
                    int syscall = registers[0].to_int();

                    if (syscall == 0) {
                        return;
                    }
                }
            }
            default:
                invalid_opcode(opcode);
            }
        }
    }


    void CPU::print_state() {
        std::cout << "Registers:" << '\n';
        for (int i = 0; i < 27; i++) {
            std::string s = "r" + std::to_string(i) + "=" + std::to_string(registers[i].to_int());
            s.append(12 - s.size(), ' ');
            std::cout << s;
            if (i % 9 == 8) {
                std::cout << '\n';
            }
        }

        std::cout << "First 81 trytes of memory (addresses in nonary):" << '\n';
        for (int i = 0; i < 81; i++) {
            Word w = Word::from_int(i);
            std::string s = w.to_nonary_str() + "=" + std::to_string(memory.get_tryte(w).to_int());
            s.append(18 - s.size(), ' ');
            std::cout << s;
            if (i % 9 == 8) {
                std::cout << '\n';
            }
        }

    }

    void CPU::invalid_opcode(const Word& opcode) {
        throw std::string("invalid opcode: " + opcode.to_nonary_str());
    }


    void CPU::set_sign_flag(const Word& result) {
        int n = result.to_int();
        if (n == 0) {
            flags.set_trit(S, Trit(0));
        }
        else if (n <= (WORD_MAX / 2)) {
            flags.set_trit(S, Trit(1));
        }
        else if (n > (WORD_MAX / 2)) {
            flags.set_trit(S, Trit(2));
        }
    }

} // namespace termite   