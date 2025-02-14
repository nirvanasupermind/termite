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
        : tokens(tokens), pos(0), current(Token(TokenType::EOF_, "")) {
        advance();
    }

    void Assembler::error() const {
        throw std::string("Error: invalid syntax near '" + current.value + "'");
    }

    void Assembler::advance() {
        if (pos < tokens.size()) {
            current = tokens.at(pos++);
        }
        else {
            current = Token(TokenType::EOF_, "");
        }
    }

    void Assembler::assemble_program() {
        while (current.type != TokenType::EOF_) {
            assemble_label_instr();
            advance();
        }
    }

    void Assembler::assemble_label_instr() {
        if (current.type == TokenType::IDENTIFIER) {
            labels[current.value] = Word::from_int32((code.size() << 1) - 21523360);
            advance();
            if (current.type != TokenType::COLON) {
                error();
            }
        }
        else {
            assemble_instr();
        }
    }

    void Assembler::assemble_instr() {
        if (current.type != TokenType::INSTR_NAME) {
            error();
        }

        auto it = find(INSTR_NAMES.begin(), INSTR_NAMES.end(), current.value);
        int32_t opcode = it - INSTR_NAMES.begin();
        assemble_zero_operand_instr(opcode);
    }

    void Assembler::assemble_zero_operand_instr(int32_t opcode) { 
        code.push_back(Word(Word::from_int32(opcode).get_bct() << 24));
        code.push_back(Word::ZERO);
        code.push_back(Word::ZERO);
    }


} // namespace termite