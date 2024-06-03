#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include "token.h"
#include "node.h"
#include "parser.h"

namespace anthill {
    Parser::Parser(const std::string& filename, const std::vector<Token>& tokens)
        : filename(filename), tokens(tokens), pos(0), current(Token(1, TokenType::EOF_, "")) {
        advance();
    }

    void Parser::advance() {
        current = tokens.at(pos++);
    }

    void Parser::raise_error() const {
        throw std::string(filename + ':' + std::to_string(current.line) + ": invalid syntax near '" + current.val + "'");
    }

    std::shared_ptr<Node> Parser::parse() {
        std::shared_ptr<Node> result = stmt_list(TokenType::EOF_);
        if (current.type != TokenType::EOF_) {
            raise_error();
        }

        return result;
    }


    std::shared_ptr<Node> Parser::stmt_list(const TokenType& terminator) {
        int line = current.line;
        std::vector<std::shared_ptr<Node> > stmts;
        while (current.type != terminator) {
            stmts.push_back(stmt());
            // advance();
        }
        return std::shared_ptr<StmtListNode>(new StmtListNode(line, stmts));
    }


    std::shared_ptr<Node> Parser::stmt() {
        Token token = current;
        if (current.type == TokenType::KEYWORD && current.val == "print") {
            return print_stmt();
        } else if (current.type == TokenType::KEYWORD && current.val == "return") {
            return return_stmt();
        } else if (current.type == TokenType::KEYWORD && current.val == "for") {
            return for_stmt();
        }
        else if (current.type == TokenType::KEYWORD && current.val == "while") {
            return while_stmt();
        }
        else if (current.type == TokenType::KEYWORD && current.val == "if") {
            return if_stmt();
        }
        else if (current.type == TokenType::LCURLY) {
            return block_stmt();
        }
        else if (current.type == TokenType::KEYWORD && (current.val == "void" || current.val == "char" || current.val == "int")) {
            return var_func_def_stmt();
        }
        else {
            return expr_stmt();
        }
    }

    std::shared_ptr<Node> Parser::return_stmt() {
        int line = current.line;
        if (!(current.type == TokenType::KEYWORD && current.val == "return")) {
            raise_error();
        }
        advance();
        std::shared_ptr<Node> value = expr_stmt();
        return std::shared_ptr<ReturnNode>(new ReturnNode(line, value));
    }

    std::shared_ptr<Node> Parser::print_stmt() {
        int line = current.line;
        if (!(current.type == TokenType::KEYWORD && current.val == "print")) {
            raise_error();
        }
        advance();
        std::shared_ptr<Node> value = expr_stmt();
        return std::shared_ptr<PrintNode>(new PrintNode(line, value));
    }

    std::shared_ptr<Node> Parser::while_stmt() {
        int line = current.line;

        if (!(current.type == TokenType::KEYWORD && current.val == "while")) {
            raise_error();
        }
        advance();

        if (current.type != TokenType::LPAREN) {
            raise_error();
        }
        advance();

        std::shared_ptr<Node> cond = expr(TokenType::EOF_);
        if (current.type != TokenType::RPAREN) {
            raise_error();
        }
        advance();
        std::shared_ptr<Node> body = block_stmt();
        return std::shared_ptr<WhileNode>(new WhileNode(line, cond, body));
    }


    std::shared_ptr<Node> Parser::for_stmt() {
        int line = current.line;
        if (!(current.type == TokenType::KEYWORD && current.val == "for")) {
            raise_error();
        }
        advance();
        if (current.type != TokenType::LPAREN) {
            raise_error();
        }
        advance();

        std::shared_ptr<Node> init = var_func_def_stmt();
        std::shared_ptr<Node> cond = expr_stmt();
        std::shared_ptr<Node> update = expr(TokenType::RPAREN);
        if (current.type != TokenType::RPAREN) {
            raise_error();
        }
        advance();
        std::shared_ptr<Node> body = block_stmt();
        return std::shared_ptr<ForNode>(new ForNode(line, init, cond, update, body));
    }

    std::shared_ptr<Node> Parser::if_stmt() {
        int line = current.line;

        if (!(current.type == TokenType::KEYWORD && current.val == "if")) {
            raise_error();
        }
        advance();

        if (current.type != TokenType::LPAREN) {
            raise_error();
        }
        advance();

        std::shared_ptr<Node> cond = expr(TokenType::EOF_);
        if (current.type != TokenType::RPAREN) {
            raise_error();
        }
        advance();
        std::shared_ptr<Node> body = block_stmt();
        if (current.type == TokenType::KEYWORD && current.val == "else") {
            advance();
            std::shared_ptr<Node> else_body = block_stmt();
            return std::shared_ptr<IfElseNode>(new IfElseNode(line, cond, body, else_body));

        }
        return std::shared_ptr<IfNode>(new IfNode(line, cond, body));
    }



    std::shared_ptr<Node> Parser::block_stmt() {
        int line = current.line;
        if (current.type != TokenType::LCURLY) {
            raise_error();
        }
        advance();
        std::shared_ptr<Node> node = stmt_list(TokenType::RCURLY);
        if (current.type != TokenType::RCURLY) {
            raise_error();
        }
        advance();
        return std::shared_ptr<BlockNode>(new BlockNode(line, node));
    }

    std::shared_ptr<Node> Parser::var_func_def_stmt() {
        int line = current.line;
        std::shared_ptr<Node> var_or_return_type;
        bool is_void = current.type == TokenType::KEYWORD && current.val == "void";
        if (is_void) {
            var_or_return_type = std::shared_ptr<IdentifierNode>(new IdentifierNode(line, current.val));
            advance();
        } else {
            var_or_return_type = static_type(TokenType::EOF_);
        }

        if (current.type != TokenType::IDENTIFIER) {
            raise_error();
        }
        Token name = current;
        advance();
        if (current.type == TokenType::EQ) {
            if(is_void) {
                raise_error();
            }
            advance();
            std::shared_ptr<Node> value = expr_stmt();
            return std::shared_ptr<VarDefNode>(new VarDefNode(line, var_or_return_type, name.val, value));
        }
        else if (current.type == TokenType::LPAREN) {
            advance();
            std::vector<std::shared_ptr<Node> > arg_types;
            std::vector<std::string> arg_names;
            while (current.type != TokenType::EOF_) {
                if (current.type == TokenType::RPAREN) {
                    advance();
                    break;
                }
                arg_types.push_back(static_type(TokenType::EOF_));
                if (current.type != TokenType::IDENTIFIER) {
                    raise_error();
                }
                arg_names.push_back(current.val);
                advance();
                if (current.type == TokenType::COMMA) {
                    advance();
                }
                else if (current.type == TokenType::RPAREN) {
                    advance();
                    break;
                }
                else {
                    raise_error();
                }
            }
            
            std::shared_ptr<Node> body = block_stmt();

            return std::shared_ptr<FuncDefNode>(new FuncDefNode(line, var_or_return_type, name.val, arg_types, arg_names, body));
        }
    }

    std::shared_ptr<Node> Parser::static_type(const TokenType& terminator) {
        int line = current.line;
        if (!(current.type == TokenType::KEYWORD && (current.val == "char" || current.val == "int"))) {
            raise_error();
        }
        Token var_type = current;
        std::shared_ptr<Node> result = std::shared_ptr<IdentifierNode>(new IdentifierNode(line, var_type.val));
        advance();
        while (current.type != terminator && current.type == TokenType::MUL) {
            result = std::shared_ptr<PointerTypeNode>(new PointerTypeNode(line, result));
            advance();
        }
        return result;
    }


    std::shared_ptr<Node> Parser::expr_stmt() {
        std::shared_ptr<Node> value = expr(TokenType::SEMICOLON);
        // advance();
        if (current.type != TokenType::SEMICOLON) {
            raise_error();
        }
        advance();
        return value;
    }

    std::shared_ptr<Node> Parser::expr(const TokenType& terminator) {
        return assign_expr(terminator);
    }

    std::shared_ptr<Node> Parser::assign_expr(const TokenType& terminator) {
        std::shared_ptr<Node> result = or_expr(terminator);
        while (current.type != terminator && current.type == TokenType::EQ) {
            Token op = current;
            advance();
            result = std::shared_ptr<BinaryOpNode>(new BinaryOpNode(result->line, op, result, or_expr(terminator)));
        }
        return result;
    }

    std::shared_ptr<Node> Parser::or_expr(const TokenType& terminator) {
        std::shared_ptr<Node> result = xor_expr(terminator);
        while (current.type != terminator && current.type == TokenType::OR) {
            Token op = current;
            advance();
            result = std::shared_ptr<BinaryOpNode>(new BinaryOpNode(result->line, op, result, xor_expr(terminator)));
        }
        return result;
    }

    std::shared_ptr<Node> Parser::xor_expr(const TokenType& terminator) {
        std::shared_ptr<Node> result = and_expr(terminator);
        while (current.type != terminator && current.type == TokenType::XOR) {
            Token op = current;
            advance();
            result = std::shared_ptr<BinaryOpNode>(new BinaryOpNode(result->line, op, result, and_expr(terminator)));
        }
        return result;
    }

    std::shared_ptr<Node> Parser::and_expr(const TokenType& terminator) {
        std::shared_ptr<Node> result = eq_expr(terminator);
        while (current.type != terminator && current.type == TokenType::AND) {
            Token op = current;
            advance();
            result = std::shared_ptr<BinaryOpNode>(new BinaryOpNode(result->line, op, result, eq_expr(terminator)));
        }
        return result;
    }

    std::shared_ptr<Node> Parser::eq_expr(const TokenType& terminator) {
        std::shared_ptr<Node> result = comp_expr(terminator);
        while (current.type != terminator && (current.type == TokenType::EE || current.type == TokenType::NE)) {
            Token op = current;
            advance();
            result = std::shared_ptr<BinaryOpNode>(new BinaryOpNode(result->line, op, result, comp_expr(terminator)));
        }
        return result;
    }


    std::shared_ptr<Node> Parser::comp_expr(const TokenType& terminator) {
        std::shared_ptr<Node> result = additive_expr(terminator);
        while (current.type != terminator && (current.type == TokenType::LT  || current.type == TokenType::LE
        || current.type == TokenType::GT || current.type == TokenType::GE)) {
            Token op = current;
            advance();
            result = std::shared_ptr<BinaryOpNode>(new BinaryOpNode(result->line, op, result, additive_expr(terminator)));
        }
        return result;
    }

    std::shared_ptr<Node> Parser::additive_expr(const TokenType& terminator) {
        std::shared_ptr<Node> result = multiplicative_expr(terminator);
        while (current.type != terminator && (current.type == TokenType::PLUS || current.type == TokenType::MINUS)) {
            Token op = current;
            advance();
            result = std::shared_ptr<BinaryOpNode>(new BinaryOpNode(result->line, op, result, multiplicative_expr(terminator)));
        }
        return result;
    }

    std::shared_ptr<Node> Parser::multiplicative_expr(const TokenType& terminator) {
        std::shared_ptr<Node> result = unary_expr();
        while (current.type != TokenType::EOF_ && (current.type == TokenType::MUL || current.type == TokenType::DIV || current.type == TokenType::MOD)) {
            Token op = current;
            advance();
            result = std::shared_ptr<BinaryOpNode>(new BinaryOpNode(result->line, op, result, unary_expr()));
        }
        return result;
    }

    std::shared_ptr<Node> Parser::unary_expr() {
        if (current.type == TokenType::PLUS || current.type == TokenType::MINUS || current.type == TokenType::MUL || current.type == TokenType::AND) {
            Token op = current;
            advance();
            std::shared_ptr<Node> node = unary_expr();
            return std::shared_ptr<UnaryOpNode>(new UnaryOpNode(op.line, op, node));
        }
        else {
            return call_expr();
        }
    }

    std::shared_ptr<Node> Parser::call_expr() {
        int line = current.line;
        std::shared_ptr<Node> result = basic_expr();
        while (current.type == TokenType::LPAREN) {
            advance();
            std::vector<std::shared_ptr<Node> > args;
            if(current.type == TokenType::RPAREN) {
                advance();
            } else {
                while (current.type != TokenType::EOF_) {
                    args.push_back(expr(TokenType::COMMA));
                    if (current.type == TokenType::COMMA) {
                        advance();
                    }
                    else if (current.type == TokenType::RPAREN) {
                        advance();
                        break;
                    }
                    else {
                        raise_error();
                    }
                }
            }

            result = std::shared_ptr<CallNode>(new CallNode(line, result, args));
        }

        return result;
    }

    std::shared_ptr<Node> Parser::basic_expr() {
        Token token = current;
        if (current.type == TokenType::LPAREN) {
            advance();
            if(current.type == TokenType::KEYWORD && (current.val == "void" || current.val == "char" || current.val == "int")) {
                std::shared_ptr<Node> cast_type = static_type(TokenType::RPAREN);
                if(current.type != TokenType::RPAREN) {
                    raise_error();
                }
                advance();
                std::shared_ptr<Node> val = expr(TokenType::EOF_);
                return std::shared_ptr<CastNode>(new CastNode(token.line, cast_type, val));
            } 
            std::shared_ptr<Node> result = expr(TokenType::RPAREN);

            if (current.type != TokenType::RPAREN) {
                raise_error();
            }

            advance();
            return result;
        }
        else if (current.type == TokenType::INT) {
            advance();
            // if(token.val.at(1) == 'r') {
            //     return std::shared_ptr<IntNode>(new IntNode(token.line, std::stoi(token.val)));
            // }
            return std::shared_ptr<IntNode>(new IntNode(token.line, std::stoi(token.val)));
        }
        else if (current.type == TokenType::CHAR) {
            std::wstring w(1, 0);
            std::memcpy(&w, &current.val, sizeof(wchar_t));
            advance();
            return std::shared_ptr<CharNode>(new CharNode(token.line, (int16_t)(w.at(0))));
        }
        else if (current.type == TokenType::STRING) {
            advance();
            return std::shared_ptr<StringNode>(new StringNode(token.line, token.val));
        }
        else if (current.type == TokenType::IDENTIFIER) {
            advance();
            return std::shared_ptr<IdentifierNode>(new IdentifierNode(token.line, token.val));
        }

        raise_error();
    }
} // namespace anthill
