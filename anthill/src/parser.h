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
    };
}

#endif