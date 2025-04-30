#include <string>
#include "token.h"

namespace termite {
    Token::Token(int line, TokenType type, const std::string& value)
        : line(line), type(type), value(value) {

    }
} // namespace termite