#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <memory>
#include <vector>
#include "token.h"
#include "node.h"

namespace anthill {
    class Parser {
    public:
        std::string filename;
        std::vector<Token> tokens;
        Token current;
        int pos;
        Parser(const std::string& filename, const std::vector<Token>& tokens);
        void advance();
        void raise_error() const;
        std::shared_ptr<Node> parse();
        std::shared_ptr<Node> stmt_list(const TokenType& terminator);
        std::shared_ptr<Node> stmt();
        std::shared_ptr<Node> print_stmt();
        std::shared_ptr<Node> return_stmt();
        std::shared_ptr<Node> for_stmt();
        std::shared_ptr<Node> while_stmt();
        std::shared_ptr<Node> if_stmt();
        std::shared_ptr<Node> block_stmt();
        std::shared_ptr<Node> var_func_def_stmt();
        std::shared_ptr<Node> static_type(const TokenType& terminator);
        std::shared_ptr<Node> expr_stmt();
        std::shared_ptr<Node> expr(const TokenType& terminator);
        std::shared_ptr<Node> assign_expr(const TokenType& terminator);
        std::shared_ptr<Node> or_expr(const TokenType& terminator);
        std::shared_ptr<Node> xor_expr(const TokenType& terminator);
        std::shared_ptr<Node> and_expr(const TokenType& terminator);
        std::shared_ptr<Node> eq_expr(const TokenType& terminator);
        std::shared_ptr<Node> comp_expr(const TokenType& terminator);
        std::shared_ptr<Node> additive_expr(const TokenType& terminator);
        std::shared_ptr<Node> multiplicative_expr(const TokenType& terminator);
        std::shared_ptr<Node> unary_expr();
        std::shared_ptr<Node> call_expr();
        std::shared_ptr<Node> basic_expr();
    };
} // namespace anthill

#endif // PARSER_H