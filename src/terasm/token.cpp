#include <string>
#include "token.h"

namespace termite {
    Token::Token(TokenType type, const std::string& value)
        : type(type), value(value) {

    }
} // namespace termite