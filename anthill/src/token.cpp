#include <string>
#include "token.h"

namespace anthill {
    Token::Token(int line, TokenType type, const std::string& val)
        : line(line), type(type), val(val) {

    }

    std::string Token::to_str() const {
        std::string str;
        switch (type) {
        case TokenType::SLASH: {
            str += "SLASH";
            break;
        }
        case TokenType::STAR: {
            str += "STAR";
            break;
        }
        case TokenType::MOD: {
            str += "MOD";
            break;
        }
        case TokenType::PLUS: {
            str += "PLUS";
            break;
        }
        case TokenType::MINUS: {
            str += "MINUS";
            break;
        }
        case TokenType::LSHIFT: {
            str += "LSHIFT";
            break;
        }
        case TokenType::RSHIFT: {
            str += "RSHIFT";
            break;
        }
        case TokenType::GREATER: {
            str += "GREATER";
            break;
        }
        case TokenType::GTEQ: {
            str += "GTEQ";
            break;
        }
        case TokenType::LESS: {
            str += "LESS";
            break;
        }
        case TokenType::LTEQ: {
            str += "LTEQ";
            break;
        }
        case TokenType::EQUAL: {
            str += "EQUAL";
            break;
        }
        case TokenType::NOTEQ: {
            str += "NOTEQ";
            break;
        }
        case TokenType::AMPER: {
            str += "AMPER";
            break;
        }
        case TokenType::CARET: {
            str += "CARET";
            break;
        }
        case TokenType::PIPE: {
            str += "PIPE";
            break;
        }
        case TokenType::LOGAND: {
            str += "LOGAND";
            break;
        }
        case TokenType::LOGOR: {
            str += "LOGOR";
            break;
        }
        case TokenType::__ARGC: {
            str += "__ARGC";
            break;
        }
        case TokenType::ASAND: {
            str += "ASAND";
            break;
        }
        case TokenType::ASXOR: {
            str += "ASXOR";
            break;
        }
        case TokenType::ASLSHIFT: {
            str += "ASLSHIFT";
            break;
        }
        case TokenType::ASMINUS: {
            str += "ASMINUS";
            break;
        }
        case TokenType::ASMOD: {
            str += "ASMOD";
            break;
        }
        case TokenType::ASOR: {
            str += "ASOR";
            break;
        }
        case TokenType::ASPLUS: {
            str += "ASPLUS";
            break;
        }
        case TokenType::ASRSHIFT: {
            str += "ASRSHIFT";
            break;
        }
        case TokenType::ASDIV: {
            str += "ASDIV";
            break;
        }
        case TokenType::ASMUL: {
            str += "ASMUL";
            break;
        }
        case TokenType::ASSIGN: {
            str += "ASSIGN";
            break;
        }
        case TokenType::BREAK: {
            str += "BREAK";
            break;
        }
        case TokenType::CASE: {
            str += "CASE";
            break;
        }
        case TokenType::CHAR: {
            str += "CHAR";
            break;
        }
        case TokenType::COLON: {
            str += "COLON";
            break;
        }
        case TokenType::COMMA: {
            str += "COMMA";
            break;
        }
        case TokenType::CONTINUE: {
            str += "CONTINUE";
            break;
        }
        case TokenType::DECR: {
            str += "DECR";
            break;
        }
        case TokenType::DEFAULT: {
            str += "DEFAULT";
            break;
        }
        case TokenType::DO: {
            str += "DO";
            break;
        }
        case TokenType::ELLIPSIS: {
            str += "ELLIPSIS";
            break;
        }
        case TokenType::ELSE: {
            str += "ELSE";
            break;
        }
        case TokenType::ENUM: {
            str += "ENUM";
            break;
        }
        case TokenType::EXTERN: {
            str += "EXTERN";
            break;
        }
        case TokenType::FOR: {
            str += "FOR";
            break;
        }
        case TokenType::IDENT: {
            str += "IDENT";
            break;
        }
        case TokenType::IF: {
            str += "IF";
            break;
        }
        case TokenType::INCR: {
            str += "INCR";
            break;
        }
        case TokenType::INT: {
            str += "INT";
            break;
        }
        case TokenType::INTLIT: {
            str += "INTLIT";
            break;
        }
        case TokenType::LBRACE: {
            str += "LBRACE";
            break;
        }
        case TokenType::LBRACK: {
            str += "LBRACK";
            break;
        }
        case TokenType::LPAREN: {
            str += "LPAREN";
            break;
        }
        case TokenType::NOT: {
            str += "NOT";
            break;
        }
        case TokenType::QMARK: {
            str += "QMARK";
            break;
        }
        case TokenType::RBRACE: {
            str += "RBRACE";
            break;
        }
        case TokenType::RBRACK: {
            str += "RBRACK";
            break;
        }
        case TokenType::RETURN: {
            str += "RETURN";
            break;
        }
        case TokenType::RPAREN: {
            str += "RPAREN";
            break;
        }
        case TokenType::SEMI: {
            str += "SEMI";
            break;
        }
        case TokenType::SIZEOF: {
            str += "SIZEOF";
            break;
        }
        case TokenType::STATIC: {
            str += "STATIC";
            break;
        }
        case TokenType::STRLIT: {
            str += "STRLIT";
            break;
        }
        case TokenType::SWITCH: {
            str += "SWITCH";
            break;
        }
        case TokenType::VOID: {
            str += "VOID";
            break;
        }
        case TokenType::WHILE: {
            str += "WHILE";
            break;
        }
        case TokenType::XEOF: {
            str += "XEOF";
            break;
        }
        case TokenType::XMARK: {
            str += "XMARK";
            break;
        }
        case TokenType::P_INCLUDE: {
            str += "P_INCLUDE";
            break;
        }
        case TokenType::P_DEFINE: {
            str += "P_DEFINE";
            break;
        }
        case TokenType::P_ENDIF: {
            str += "P_ENDIF";
            break;
        }
        case TokenType::P_ELSE: {
            str += "P_ELSE";
            break;
        }
        case TokenType::P_ELSENOT: {
            str += "P_ELSENOT";
            break;
        }
        case TokenType::P_IFDEF: {
            str += "P_IFDEF";
            break;
        }
        case TokenType::P_IFNDEF: {
            str += "P_IFNDEF";
            break;
        }
        case TokenType::P_UNDEF: {
            str += "P_UNDEF";
            break;
        }

        }

        str += ':';
        str += val;
        return str;
    }
} // namespace termite

