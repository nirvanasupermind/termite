#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "token.h"
#include "lexer.h"
#include "assembler.h"
#include "../core/word.h"

namespace termite {
    Assembler::Assembler(const std::vector<Token>& tokens)
        : tokens(tokens), pos(0), current(Token(1, TokenType::EOF_, "")) {
        advance();
    }

    void Assembler::error() const {
        throw std::string("line " + std::to_string(current.line) + ": error: invalid syntax near '" + current.value + "'");
    }

    void Assembler::advance() {
        if (pos < tokens.size()) {
            current = tokens.at(pos++);
        }
        else {
            current = Token(current.line, TokenType::EOF_, "");
        }
    }

    void Assembler::assemble_program() {
        while (current.type != TokenType::EOF_) {
            assemble_label_instr();
        }
    }


    void Assembler::label_pass() {
        int32_t addr = -21523360;
        for (int i = 0; i < tokens.size(); i++) {
            Token tok = tokens.at(i);
            if (tok.type == TokenType::INSTR_NAME) {
                addr += 6;
            }
            else if (i >= 1) {
                if (tokens.at(i - 1).type == TokenType::IDENTIFIER && tok.type == TokenType::COLON) {
                    labels[tokens.at(i - 1).value] = Word::from_int32(addr);
                }
            }
        }
    }

    void Assembler::assemble_label_instr() {
        while (current.type == TokenType::NEWLINE) {
            advance();
        }

        if (current.type == TokenType::IDENTIFIER) {
            // labels[current.value] = Word::from_int32((code.size() << 1) c
            advance();
            if (current.type != TokenType::COLON) {
                error();
            }
            advance();
        }
        else {
            assemble_instr();
        }
        
        while (current.type == TokenType::NEWLINE) {
            advance();
        }
    }

    void Assembler::assemble_instr() {
        if (current.type != TokenType::INSTR_NAME) {
            error();
        }

        std::string instr_name = current.value;


        advance();


        auto it = find(INSTR_NAMES.begin(), INSTR_NAMES.end(), instr_name);
        int32_t opcode = it - INSTR_NAMES.begin() - 40;
        Word num_operands = NUM_OPERANDS_TABLE.at(instr_name);
        if (NUM_OPERANDS_TABLE.at(instr_name) == 0) {
            assemble_zero_operand_instr(opcode);
        }
        else if (NUM_OPERANDS_TABLE.at(instr_name) == 1) {
            assemble_one_operand_instr(opcode);
        }
        else {
            assemble_two_operand_instr(opcode);
        }

        advance();
        if (!(current.type == TokenType::EOF_ || current.type == TokenType::NEWLINE || current.type == TokenType::INSTR_NAME || current.type == TokenType::IDENTIFIER)) {
            error();
        }
    }

    std::vector<Word> Assembler::assemble_operand() {
        Word addr_mode = Word::ZERO;
        Word reg = Word::ZERO;
        Word imm = Word::ZERO;

        if (current.type == TokenType::DOLLAR) {
            advance();
            if(current.type != TokenType::NUMBER) {
                error();
            }
            addr_mode = Word::from_int32(-4);
            if (current.value[0] == '0' && current.value[1] == 't') {
                imm = Word::from_ternary_str(current.value.substr(2));
            }
            else if (current.value[0] == '0' && current.value[1] == 'n') {
                imm = Word::from_nonary_str(current.value.substr(2));
            }
            else {
                imm = Word::from_int32(std::stoi(current.value));
            }
        }
        else if (current.type == TokenType::IDENTIFIER) {
            addr_mode = Word::from_int32(-4);
            imm = labels.at(current.value);
        }
        else if (current.type == TokenType::PERCENT) {
            advance();
            if(current.type != TokenType::REG_NAME) {
                error();
            }
            addr_mode = Word::from_int32(-3);

            auto it = find(REG_NAMES.begin(), REG_NAMES.end(), current.value);
            reg = Word::from_int32(it - REG_NAMES.begin() - 4);
        }
        else if(current.type == TokenType::NUMBER) {
            addr_mode = Word::from_int32(-2);
            if (current.value[0] == '0' && current.value[1] == 't') {
                imm = Word::from_ternary_str(current.value.substr(2));
            }
            else if (current.value[0] == '0' && current.value[1] == 'n') {
                imm = Word::from_nonary_str(current.value.substr(2));
            }
            else {
                imm = Word::from_int32(std::stoi(current.value));
            }

            if(tokens[pos].type == TokenType::LPAREN) {
                advance();
                advance();
                if(current.type != TokenType::PERCENT) {
                    error();
                }
                advance();
                if(current.type != TokenType::REG_NAME) {
                    error();
                }
                addr_mode = Word::from_int32(-1);
                auto it = find(REG_NAMES.begin(), REG_NAMES.end(), current.value);
                reg = Word::from_int32(it - REG_NAMES.begin() - 4);
                advance();
                if(current.type != TokenType::RPAREN) {
                    error();
                }  
            }
        }
        // else if (current.type == TokenType::LSQUARE) {
        //     advance();
        //     if (current.type == TokenType::NUMBER) {
        //         addr_mode = Word::from_int32(-2);
        //         if (current.value[0] == '0' && current.value[1] == 't') {
        //             imm = Word::from_ternary_str(current.value.substr(2));
        //         }
        //         else if (current.value[0] == '0' && current.value[1] == 'n') {
        //             imm = Word::from_nonary_str(current.value.substr(2));
        //         }
        //         else {
        //             imm = Word::from_int32(std::stoi(current.value));
        //         }
        //         advance();
        //         if (current.type != TokenType::RSQUARE) {
        //             error();
        //         }
        //     }
        //     else if (current.type == TokenType::REG_NAME) {
        //         addr_mode = Word::from_int32(-1);

        //         auto it = find(REG_NAMES.begin(), REG_NAMES.end(), current.value);
        //         reg = Word::from_int32(it - REG_NAMES.begin() - 4);
        //         advance();
        //         if (current.type != TokenType::PLUS) {
        //             error();
        //         }
        //         advance();
        //         if (current.type != TokenType::NUMBER) {
        //             error();
        //         }
        //         if (current.value[0] == '0' && current.value[1] == 't') {
        //             imm = Word::from_ternary_str(current.value.substr(2));
        //         }
        //         else if (current.value[0] == '0' && current.value[1] == 'n') {
        //             imm = Word::from_nonary_str(current.value.substr(2));
        //         }
        //         else {
        //             imm = Word::from_int32(std::stoi(current.value));
        //         }
        //         advance();
        //         if (current.type != TokenType::RSQUARE) {
        //             error();
        //         }
        //     }
        // }
        else {
            error();
        }

        return { addr_mode, reg, imm };
    }

    void Assembler::assemble_zero_operand_instr(int32_t opcode) {
        code.push_back(Word(((Word::from_int32(opcode).get_bct() & 0xff) << 24) + 0x555555));
        code.push_back(Word::ZERO);
        code.push_back(Word::ZERO);
    }

    void Assembler::assemble_one_operand_instr(int32_t opcode) {
        std::vector<Word> operand = assemble_operand();
        code.push_back(Word(((Word::from_int32(opcode).get_bct() & 0xff) << 24)
            + ((operand[0].get_bct() & 0xf) << 20)
            + ((operand[1].get_bct() & 0xf) << 16)
            + 0x5555));
        code.push_back(operand[2]);
        code.push_back(Word::ZERO);
    }

    void Assembler::assemble_two_operand_instr(int32_t opcode) {
        std::vector<Word> operand1 = assemble_operand();
        advance();
        if (current.type != TokenType::COMMA) {
            advance();
        }
        advance();
        std::vector<Word> operand2 = assemble_operand();

        code.push_back(Word(((Word::from_int32(opcode).get_bct() & 0xff) << 24)
            + ((operand2[0].get_bct() & 0xf) << 20)
            + ((operand2[1].get_bct() & 0xf) << 16)
            + ((operand1[0].get_bct() & 0xf) << 12)
            + ((operand1[1].get_bct() & 0xf) << 8)
            + 0x55));
        code.push_back(operand2[2]);
        code.push_back(operand1[2]);
    }


} // namespace termite