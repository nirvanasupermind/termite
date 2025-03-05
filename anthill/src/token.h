#ifndef TOKEN_H
#define TOKEN_H

#include <string>

namespace anthill {
    enum class TokenType {
        SLASH, STAR, MOD, PLUS, MINUS, LSHIFT, RSHIFT,
        GREATER, GTEQ, LESS, LTEQ, EQUAL, NOTEQ, AMPER,
        CARET, PIPE, LOGAND, LOGOR,
        __ARGC, ASAND, ASXOR, ASLSHIFT, ASMINUS, ASMOD, ASOR,
        ASPLUS, ASRSHIFT, ASDIV, ASMUL, ASSIGN, BREAK, CASE,
        CHAR, CHARLIT, COLON, COMMA, CONTINUE, DECR, DEFAULT, DO,
        ELLIPSIS, ELSE, ENUM, EXTERN, FOR, IDENT, IF, INCR,
        INT, INTLIT, LBRACE, LBRACK, LPAREN, NOT, QMARK,
        RBRACE, RBRACK, RETURN, RPAREN, SEMI, SIZEOF, STATIC,
        STRLIT, SWITCH, VOID, WHILE, XEOF, XMARK,
        P_INCLUDE, P_DEFINE, P_ENDIF, P_ELSE, P_ELSENOT,
        P_IFDEF, P_IFNDEF, P_UNDEF
    };

    class Token {
    public:
        int line;
        TokenType type;
        std::string val;
        Token();
        Token(int line, TokenType type, const std::string& val);
        std::string to_str() const;
    };
}

#endif