
#include <string>
#include <memory>
#include <vector>
#include "token.h"
#include "node.h"
#include "error.h"
#include "parser.h"

namespace anthill {
    Parser::Parser(const std::string& file, const std::vector<Token>& tokens)
        : file(file), tokens(tokens), pos(0) {
        advance();
    }

    void Parser::advance() {
        current = tokens.at(pos++);
    }

    void Parser::syntax_error() {
        error(file, current.line, std::string("invalid syntax near '") + current.val + "'");
    }

    void Parser::eat(const TokenType& type) {
        if(current.type != type) {
            syntax_error();
        }
        advance();
    }

    std::shared_ptr<Node> Parser::parse() {
        return basic_expr();
    }

    std::shared_ptr<Node> Parser::basic_expr() {
        Token tok = current;
        if(tok.type == TokenType::INTLIT) {
            advance();
            return std::make_shared<IntNode>(IntNode(tok.line, tok));
        } else if(tok.type == TokenType::CHARLIT) {
            advance();
            return std::make_shared<CharNode>(CharNode(tok.line, tok));
        } else {
           syntax_error();
        }
    }
}
