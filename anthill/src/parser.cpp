#include <string>
#include <memory>
#include <vector>
#include <algorithm>
#include <iostream>
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
        if (current.type != type) {
            syntax_error();
        }
        advance();
    }

    std::shared_ptr<Node> Parser::parse() {
        std::shared_ptr<Node> result = expr();
        if(current.type != TokenType::XEOF) {
            syntax_error();
        }
        return result;
    }

    std::shared_ptr<Node> Parser::basic_expr() {
        Token tok = current;
        if (tok.type == TokenType::INTLIT) {
            advance();
            return std::make_shared<IntNode>(IntNode(tok.line, tok));
        }
        else if (tok.type == TokenType::CHARLIT) {
            advance();
            return std::make_shared<CharNode>(CharNode(tok.line, tok));
        }
        else if (tok.type == TokenType::LPAREN) {
            advance();
            std::shared_ptr<Node> result = expr();
            eat(TokenType::RPAREN);
            return result;  
        }
        else {
            syntax_error();
        }
    }

    std::shared_ptr<Node> Parser::unary_op_expr() {
        Token tok = current;
        if (tok.type == TokenType::PLUS || tok.type == TokenType::MINUS) {
            advance();
            return std::make_shared<UnaryOpNode>(UnaryOpNode(tok.line, tok, basic_expr()));
        } else {
            return basic_expr();
        }
    }
    
    std::shared_ptr<Node> Parser::bin_op_expr(const std::function<std::shared_ptr<Node>() >& func, const std::vector<TokenType>& types) {
        std::shared_ptr<Node> left = func();
        while (std::find(types.begin(), types.end(), current.type) != types.end() && current.type != TokenType::XEOF) {
            Token op_tok = current;
            advance();
            std::shared_ptr<Node> right = func();
            left = std::make_shared<BinOpNode>(BinOpNode(left->line, left, op_tok, right));
        }
        return left;
    }

    std::shared_ptr<Node> Parser::term() {
        return bin_op_expr([this]() { return unary_op_expr(); }, { TokenType::STAR, TokenType::SLASH, TokenType::MOD });
    }
            
    std::shared_ptr<Node> Parser::factor() {
        return bin_op_expr([this]() { return term(); }, { TokenType::PLUS, TokenType::MINUS });
    }

    std::shared_ptr<Node> Parser::shift_expr() {
        return bin_op_expr([this]() { return factor(); }, { TokenType::LSHIFT, TokenType::RSHIFT });
    }

    std::shared_ptr<Node> Parser::expr() {
        return shift_expr();
    }
}
