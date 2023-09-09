#include <iostream>
#include <iomanip>
#include <algorithm>
#include "trit.h"
#include "tryte.h"
#include "word.h"
#include "mem.h"
#include "cpu.h"
#include "text.h"

namespace termite {
    void CPU::reset() {
        std::fill(registers, registers + 27, 0);
        memory.data = std::vector<Word>(WORD_MAX);
    }

    Word CPU::fetch_tryte(int& cycles) {
        Word tryte = memory.get_tryte(registers[PC]);
        registers[PC] = (registers[PC] + Word::from_int32(1)).first;
        cycles--;
        return tryte;
    }

    Word CPU::fetch_word(int& cycles) {
        Word word = memory.get_word(registers[PC]);
        registers[PC] = (registers[PC] + Word::from_int32(2)).first;
        cycles--;
        return word;
    }

    void CPU::execute(int cycles, bool verbose) {
        while (cycles > 0) {
            Word ins = fetch_word(cycles);
            Word opcode = ins.get_trit_range(12, 4);
            if(verbose) {
                std::cout << "******** Program counter (nonary): " << registers[PC].to_nonary_str() << '\n';
                std::cout << "******** Current machine code instruction (nonary): " << ins.to_nonary_str() << '\n';
                print_state();
            }
            // std::cout << "Opcode " << opcode.to_nonary_str() << '\n';
            // std::cout << "Ins " << ins.to_nonary_str() << '\n';
            switch (opcode.to_int32()) {
            case MOV: {
                Word rd = ins.get_trit_range(3, 3);
                Word rs = ins.get_trit_range(6, 3);
                registers[rd.to_int32()] = registers[rs.to_int32()];
                break;
            }
            case MOVI: {
                std::cout << "MOVI" << '\n';
                Word rd = ins.get_trit_range(9, 3);
                std::cout << rd.to_int32() << '\n';
                Word imm = ins.get_trit_range(0, 6);
                std::cout << imm.to_int32() << '\n';
                registers[rd.to_int32()] = imm.to_int32();
                break;
            }
            case LDR: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                registers[rd.to_int32()] = memory.get_word(rs.to_int32() + imm.to_int32());
                break;
            }
            case STR: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                memory.set_word(rd.to_int32() + imm.to_int32(), rs.to_int32());
                break;
            }
            case NEG: {
                Word rd = ins.get_trit_range(9, 3);
                Word result = -registers[rd.to_int32()];
                registers[rd.to_int32()] = -registers[rd.to_int32()];
                set_sign_flag(result);
                break;
            }
            case ADD: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word rt = ins.get_trit_range(3, 3);
                std::pair<Word, Trit> sum = registers[rs.to_int32()] + registers[rt.to_int32()];
                registers[rd.to_int32()] = sum.first;
                sr.set_trit(C, sum.second);
                set_sign_flag(sum.first);
                break;
            }
            case ADDI: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                std::pair<Word, Trit> sum = registers[rs.to_int32()] + imm;
                registers[rd.to_int32()] = sum.first;
                sr.set_trit(C, sum.second);
                set_sign_flag(sum.first);
                break;
            }
            case ADDC: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word rt = ins.get_trit_range(3, 3);
                std::pair<Word, Trit> sum = registers[rs.to_int32()] + registers[rt.to_int32()];
                registers[rd.to_int32()] = (sum.first + Word::from_int32(sr.get_trit(C).val)).first;
                sr.set_trit(C, sum.second);
                set_sign_flag(sum.first);
                break;
            }
            case ADDCI: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                std::pair<Word, Trit> sum = registers[rs.to_int32()] + imm;
                registers[rd.to_int32()] = (sum.first + Word::from_int32(sr.get_trit(C).val)).first;
                sr.set_trit(C, sum.second);
                set_sign_flag(sum.first);
                break;
            }
            case SUB: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word rt = ins.get_trit_range(3, 3);
                std::pair<Word, Trit> diff = registers[rs.to_int32()] - registers[rt.to_int32()];
                registers[rd.to_int32()] = diff.first;
                sr.set_trit(C, diff.second);
                set_sign_flag(diff.first);
                break;
            }
            case SUBI: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                std::pair<Word, Trit> diff = registers[rs.to_int32()] - imm;
                registers[rd.to_int32()] = diff.first;
                sr.set_trit(C, diff.second);
                set_sign_flag(diff.first);
                break;
            }
            case SUBC: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word rt = ins.get_trit_range(3, 3);
                std::pair<Word, Trit> diff = registers[rs.to_int32()] - registers[rt.to_int32()];
                registers[rd.to_int32()] = (diff.first + Word::from_int32(sr.get_trit(C).val)).first;
                sr.set_trit(C, diff.second);
                set_sign_flag(diff.first);
                break;
            }
            case SUBCI: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                std::pair<Word, Trit> diff = registers[rs.to_int32()] - imm;
                registers[rd.to_int32()] = (diff.first + Word::from_int32(sr.get_trit(C).val)).first;
                sr.set_trit(C, diff.second);
                set_sign_flag(diff.first);
                break;
            }
            case MUL: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word rt = ins.get_trit_range(3, 3);
                Word result = registers[rs.to_int32()] * registers[rt.to_int32()];
                registers[rd.to_int32()] = result;
                set_sign_flag(result);
                break;
            }
            case MULI: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                Word result = registers[rs.to_int32()] * imm;
                registers[rd.to_int32()] = result;
                set_sign_flag(result);
                break;
            }
            case NOT: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word result = ~registers[rs.to_int32()];
                registers[rd.to_int32()] = result;
                set_sign_flag(result);
                break;
            }
            case AND: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word rt = ins.get_trit_range(3, 3);
                Word result = registers[rs.to_int32()] & registers[rt.to_int32()];
                registers[rd.to_int32()] = result;
                set_sign_flag(result);
                break;
            }
            case ANDI: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                Word result = registers[rs.to_int32()] & imm.to_int32();
                registers[rd.to_int32()] = registers[rs.to_int32()] & imm;
                set_sign_flag(result);
                break;
            }
            case OR: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word rt = ins.get_trit_range(3, 3);
                registers[rd.to_int32()] = registers[rs.to_int32()] | registers[rt.to_int32()];
                break;
            }
            case ORI: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                registers[rd.to_int32()] = registers[rs.to_int32()] | imm;
                break;
            }
            case SL: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                registers[rd.to_int32()] = registers[rs.to_int32()] >> imm.to_int32();
                break;
            }
            case LSR: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                registers[rd.to_int32()] = registers[rs.to_int32()] << imm.to_int32();
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
                if (rd.to_int32() == rs.to_int32()) {
                    registers[PC] = (registers[PC] + imm).first;
                }
                break;
            }
            case BNE: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                if (rd.to_int32() != rs.to_int32()) {
                    registers[PC] = (registers[PC] + imm).first;
                }
                break;
            }
            case BLT: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                if (rd.to_int32() < rs.to_int32()) {
                    registers[PC] = (registers[PC] + imm).first;
                }
                break;
            }
            case BLE: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                if (rd.to_int32() <= rs.to_int32()) {
                    registers[PC] = (registers[PC] + imm).first;
                }
                break;
            }
            case BGT: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                if (rd.to_int32() > rs.to_int32()) {
                    registers[PC] = (registers[PC] + imm).first;
                }
                break;
            }
            case BGE: {
                Word rd = ins.get_trit_range(9, 3);
                Word rs = ins.get_trit_range(6, 3);
                Word imm = ins.get_trit_range(0, 6);
                if (rd.to_int32() >= rs.to_int32()) {
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
                if (interrupt.to_int32() == 0) {
                    int syscall = registers[0].to_int32();

                    if (syscall == 0) {
                        return;
                    }
                    else if (syscall == 1) {
                        wchar_t w = std::getwchar();
                        registers[0] = Word::from_int32(std::find(CHAR_ENCODING_LIST.begin(),
                            CHAR_ENCODING_LIST.end(), w) - CHAR_ENCODING_LIST.begin());
                    }
                    else if (syscall == 2) {
                        std::wcout << CHAR_ENCODING_LIST[registers[1].to_int32()];
                    }
                    else if (syscall == 3) {
                        std::cout << registers[1].to_int32();
                    } 
                    else if (syscall == 4) {
                        std::cout << registers[1].to_nonary_str();
                    } 
                    else if(syscall == 5) {
                        uint64_t ms = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::system_clock::now().time_since_epoch()).count();
                        registers[1] = Word::from_int32(ms / WORD_MAX);
                        registers[1] = Word::from_int32(ms % WORD_MAX);
                    }
                }
                break;
            }
            default:
                invalid_opcode(opcode);
            }
        }
    }


    void CPU::print_state() {
        std::cout << "Registers:" << '\n';
        for (int i = 0; i < 27; i++) {
            std::string s = (i == 25 ? "lr" : (i == 26 ? "pc" : ("r" + std::to_string(i)))) + "=" + std::to_string(registers[i].to_int32());
            s.append(12 - s.size(), ' ');
            std::cout << s;
            if (i % 9 == 8) {
                std::cout << '\n';
            }
        }

        std::cout << "First 81 trytes of memory (addresses in nonary):" << '\n';
        for (int i = 0; i < 81; i++) {
            Word w = Word::from_int32(i);
            std::string s = w.to_nonary_str() + "=" + std::to_string(memory.get_tryte(w).to_int16());
            s.append(18 - s.size(), ' ');
            std::cout << s;
            if (i % 9 == 8) {
                std::cout << '\n';
            }
        }

    }

    void CPU::invalid_opcode(const Word& opcode) {
        std::cerr << "invalid opcode: " + opcode.to_nonary_str() << '\n';
        std::exit(1);
    }


    void CPU::set_sign_flag(const Word& result) {
        int n = result.to_int32();
        if (n == 0) {
            sr.set_trit(S, Trit(0));
        }
        else if (n <= (WORD_MAX / 2)) {
            sr.set_trit(S, Trit(1));
        }
        else if (n > (WORD_MAX / 2)) {
            sr.set_trit(S, Trit(2));
        }
    }

} // namespace termite   