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

    Token Parser::eat(const TokenType& type) {
        Token result = current;
        if (current.type != type) {
            syntax_error();
        }
        advance();
        return result;
    }

    std::shared_ptr<Node> Parser::parse() {
        std::shared_ptr<Node> result = stmt_list();
        if (current.type != TokenType::XEOF) {
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
        else if (tok.type == TokenType::STRLIT) {
            advance();
            return std::make_shared<StrNode>(StrNode(tok.line, tok));
        }
        else if (tok.type == TokenType::IDENT) {
            advance();
            return std::make_shared<IdentNode>(IdentNode(tok.line, tok));
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

    std::shared_ptr<Node> Parser::postfix_expr() {
        std::shared_ptr<Node> expr = basic_expr();
        if (current.type == TokenType::INCR || current.type == TokenType::DECR) {
            return std::make_shared<PostfixNode>(PostfixNode(expr->line, expr, current));
        }
        else {
            return expr;
        }
    }

    std::shared_ptr<Node> Parser::prefix_expr() {
        Token tok = current;
        if (tok.type == TokenType::PLUS || tok.type == TokenType::MINUS || tok.type == TokenType::NOT || tok.type == TokenType::AMPER || tok.type == TokenType::STAR) {
            advance();
            return std::make_shared<PrefixNode>(PrefixNode(tok.line, tok, basic_expr()));
        }
        else {
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
        return bin_op_expr([this]() { return prefix_expr(); }, { TokenType::STAR, TokenType::SLASH, TokenType::MOD });
    }

    std::shared_ptr<Node> Parser::factor() {
        return bin_op_expr([this]() { return term(); }, { TokenType::PLUS, TokenType::MINUS });
    }

    std::shared_ptr<Node> Parser::shift_expr() {
        return bin_op_expr([this]() { return factor(); }, { TokenType::LSHIFT, TokenType::RSHIFT });
    }

    std::shared_ptr<Node> Parser::cmp_expr() {
        return bin_op_expr([this]() { return shift_expr(); }, { TokenType::LESS, TokenType::LTEQ, TokenType::GREATER, TokenType::GTEQ });
    }

    std::shared_ptr<Node> Parser::eq_expr() {
        return bin_op_expr([this]() { return cmp_expr(); }, { TokenType::EQUAL, TokenType::NOTEQ });
    }

    std::shared_ptr<Node> Parser::and_expr() {
        return bin_op_expr([this]() { return eq_expr(); }, { TokenType::AMPER });
    }

    std::shared_ptr<Node> Parser::xor_expr() {
        return bin_op_expr([this]() { return and_expr(); }, { TokenType::CARET });
    }

    std::shared_ptr<Node> Parser::or_expr() {
        return bin_op_expr([this]() { return xor_expr(); }, { TokenType::PIPE });
    }

    std::shared_ptr<Node> Parser::logand_expr() {
        return bin_op_expr([this]() { return or_expr(); }, { TokenType::LOGAND });
    }

    std::shared_ptr<Node> Parser::logor_expr() {
        return bin_op_expr([this]() { return logand_expr(); }, { TokenType::LOGOR });
    }

    std::shared_ptr<Node> Parser::assign_expr() {
        // return bin_op_expr([this]() { return logor_expr(); }, { TokenType::ASSIGN
        //     , TokenType::ASAND
        //     , TokenType::ASXOR
        //     , TokenType::ASLSHIFT
        //     , TokenType::ASMINUS
        //     , TokenType::ASMOD
        //     ,TokenType::ASOR
        //     ,TokenType::ASPLUS
        //     ,TokenType::ASRSHIFT
        //     ,TokenType::ASDIV
        //    ,TokenType::ASMUL });

        std::shared_ptr<Node> left = logor_expr();
        if (current.type == TokenType::ASSIGN
            || current.type == TokenType::ASAND
            || current.type == TokenType::ASXOR
            || current.type == TokenType::ASLSHIFT
            || current.type == TokenType::ASMINUS
            || current.type == TokenType::ASMOD
            || current.type == TokenType::ASOR
            || current.type == TokenType::ASPLUS
            || current.type == TokenType::ASRSHIFT
            || current.type == TokenType::ASDIV
            || current.type == TokenType::ASMUL) {
            Token op_tok = current;
            advance();
            std::shared_ptr<Node> right = assign_expr();
            left = std::make_shared<AssignNode>(AssignNode(left->line, left, op_tok, right));
        }
        return left;
    }

    std::shared_ptr<Node> Parser::expr() {
        return assign_expr();
    }

    std::shared_ptr<Node> Parser::expr_stmt() {
        std::shared_ptr<Node> result = expr();
        eat(TokenType::SEMI);
        return result;
    }

    std::shared_ptr<Node> Parser::type() {
        int line = current.line;
        Token base_type = current;
        int num_pointers = 0;
        advance();
        while(current.type == TokenType::STAR) {
            num_pointers++;
            advance();
        }
        return std::make_shared<TypeNode>(line, base_type, num_pointers);
    }

    std::shared_ptr<Node> Parser::var_def_stmt() {
        std::shared_ptr<Node> my_type = type();
        Token name = eat(TokenType::IDENT);
        eat(TokenType::ASSIGN);
        std::shared_ptr<Node> val = expr_stmt();
        return std::make_shared<VarDefNode>(my_type->line, my_type, name, val);
    }

    std::shared_ptr<Node> Parser::stmt() {
        if(current.type == TokenType::INT || current.type == TokenType::CHAR) {
            return var_def_stmt();
        } else {
            return expr_stmt();
        }
    }

    std::shared_ptr<Node> Parser::stmt_list() {
        int line = current.line;
        std::vector<std::shared_ptr<Node> > stmts;
        while (current.type != TokenType::XEOF) {
            stmts.push_back(stmt());
        }
        return std::make_shared<StmtListNode>(line, stmts);
    }
}