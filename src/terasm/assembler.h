#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <string>
#include <map>
#include <vector>
#include <cinttypes>
#include "token.h"
#include "../core/trit.h"

namespace termite {
    class Assembler {
    private:
        std::vector<Token> tokens;
        std::string filename{};
        std::size_t pos;
        Token current{};
        std::vector<Trit> machine_code{};
        void append_num(int num, int trits);
        std::string to_lower(std::string s) const;
        void advance();
        void imm();
        void reg();
        void instruction();
    public:
        Assembler(const std::vector<Token>& tokens, const std::string& filename);
        std::vector<Trit> generate_machine_code();
    };

} // namespace termite

#endif // ASSEMBLER_H