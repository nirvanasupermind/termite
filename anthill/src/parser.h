#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <memory>
#include <vector>
#include <functional>
#include "token.h"
#include "node.h"

namespace anthill {
    class Parser {
    public:
    std::string file{};
    std::vector<Token> tokens{};
    int pos;
    Token current;
        Parser(const std::string& file, const std::vector<Token>& tokens);
        void advance();
        void syntax_error();
        void eat(const TokenType& type);
        std::shared_ptr<Node> parse();      
        std::shared_ptr<Node> basic_expr();      
        std::shared_ptr<Node> postfix_expr();
        std::shared_ptr<Node> prefix_expr();      
        std::shared_ptr<Node> bin_op_expr(const std::function<std::shared_ptr<Node>() >& func, const std::vector<TokenType>& types);
        std::shared_ptr<Node> term();
        std::shared_ptr<Node> factor();
        std::shared_ptr<Node> shift_expr();
        std::shared_ptr<Node> cmp_expr();
        std::shared_ptr<Node> eq_expr();
        std::shared_ptr<Node> and_expr();
        std::shared_ptr<Node> xor_expr();
        std::shared_ptr<Node> or_expr();
        std::shared_ptr<Node> logand_expr();
        std::shared_ptr<Node> logor_expr();
        std::shared_ptr<Node> expr();
        std::shared_ptr<Node> expr_stmt();
        std::shared_ptr<Node> stmt();
        std::shared_ptr<Node> stmt_list();

    };
}

#endif