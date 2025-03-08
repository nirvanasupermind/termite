#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <memory>
#include <vector>
#include <functional>
#include "token.h"
#include "node.h"
#include "symbol_table.h"

namespace anthill {
    class Parser {
    public:
    std::string file{};
    std::vector<Token> tokens{};
    int pos;
    Token current;
    SymbolTable global_symbol_table;
        Parser(const std::string& file, const std::vector<Token>& tokens);
        void advance();
        void syntax_error();
        Token eat(const TokenType& type);
        std::shared_ptr<Node> parse();      
        std::shared_ptr<Node> basic_expr(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);      
        std::shared_ptr<Node> call_expr(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> postfix_expr(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> prefix_expr(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);      
        std::shared_ptr<Node> bin_op_expr(const SymbolTable& symbol_table, const std::function<std::shared_ptr<Node>(const TokenType&) >& func, const std::vector<TokenType>& types, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> term(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> factor(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> shift_expr(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> cmp_expr(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> eq_expr(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> and_expr(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> xor_expr(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> or_expr(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> logand_expr(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> logor_expr(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> assign_expr(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> expr(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> expr_stmt(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> type(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> var_or_func_def_stmt(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> block_stmt(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> if_stmt(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> while_stmt(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> for_stmt(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> continue_stmt(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> break_stmt(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> return_stmt(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> enum_stmt(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> stmt(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);
        std::shared_ptr<Node> stmt_list(const SymbolTable& symbol_table, const TokenType& terminator = TokenType::XEOF);

    };
}

#endif