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
        for (int i = 0; i < tokens.size(); i++) {
            std::cout << "dbg23 " << tokens.at(i).to_str() << '\n';
        }
        error(file, current.line, std::string("invalid syntax near '") + current.val + "'");
    }

    Token Parser::eat(const TokenType& type) {
        Token result = current;
        if (current.type != type) {
            syntax_error();
        }
        advance();
        std::cerr << "eat expected " << (int)type << " got " << current.to_str() << "\n";
        return result;
    }

    std::shared_ptr<Node> Parser::parse() {
        std::shared_ptr<Node> result = stmt_list();
        if (current.type != TokenType::XEOF) {
            syntax_error();
        }
        return result;
    }

    std::shared_ptr<Node> Parser::basic_expr(const TokenType& terminator) {
        Token tok = current;
        if (tok.type == TokenType::NUMLIT) {
            advance();
            return std::make_shared<NumNode>(NumNode(tok.line, tok));
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
            if (current.type == TokenType::INT || current.type == TokenType::FLOAT || current.type == TokenType::CHAR || current.type == TokenType::VOID) {
                std::shared_ptr<Node> type_ = type(terminator);
                eat(TokenType::RPAREN);
                std::shared_ptr<Node> val = expr(terminator);
                return std::make_shared<CastNode>(CastNode(tok.line, type_, val));
            }
            else {
                std::shared_ptr<Node> result = expr(terminator);
                eat(TokenType::RPAREN);
                return result;
            }
        }
        else {
            syntax_error();
        }
    }

    std::shared_ptr<Node> Parser::call_expr(const TokenType& terminator) {
        std::shared_ptr<Node> result = basic_expr(terminator);
        while (current.type == TokenType::LPAREN && current.type != terminator) {
            advance();
            std::vector<std::shared_ptr<Node> > args;
            if (current.type == TokenType::RPAREN) {
                advance();
            }
            else {
                while (current.type != TokenType::RPAREN) {
                    args.push_back(expr(TokenType::RPAREN));
                    if (current.type == TokenType::RPAREN) {
                        advance();
                        break;
                    }
                    else {
                        eat(TokenType::COMMA);
                    }
                }
            }
            result = std::make_shared<CallNode>(CallNode(result->line, result, args));
        }
        return result;
    }

    std::shared_ptr<Node> Parser::postfix_expr(const TokenType& terminator) {
        std::shared_ptr<Node> result = call_expr(terminator);
        while ((current.type == TokenType::INCR || current.type == TokenType::DECR) && current.type != TokenType::SEMI && current.type != terminator) {
            if (current.type == TokenType::INCR) {
                std::shared_ptr<Node> int_node = std::make_shared<NumNode>(NumNode(result->line, Token(result->line, TokenType::INT, "1")));
                Token plus = Token(result->line, TokenType::PLUS, "+");
                std::shared_ptr<Node> bin_op_node = std::make_shared<BinOpNode>(BinOpNode(result->line, result, plus, int_node));
                Token assign = Token(result->line, TokenType::ASSIGN, "=");
                result = std::make_shared<AssignNode>(AssignNode(result->line, result, assign, bin_op_node));
            }
            else if (current.type == TokenType::DECR) {
                std::shared_ptr<Node> int_node = std::make_shared<NumNode>(NumNode(result->line, Token(result->line, TokenType::INT, "1")));
                Token minus = Token(result->line, TokenType::MINUS, "-");
                std::shared_ptr<Node> bin_op_node = std::make_shared<BinOpNode>(BinOpNode(result->line, result, minus, int_node));
                Token assign = Token(result->line, TokenType::ASSIGN, "=");
                result = std::make_shared<AssignNode>(AssignNode(result->line, result, assign, bin_op_node));
            }
            advance();
        }
        return result;
    }

    std::shared_ptr<Node> Parser::prefix_expr(const TokenType& terminator) {
        Token tok = current;
        if (tok.type == TokenType::PLUS || tok.type == TokenType::MINUS || tok.type == TokenType::NOT || tok.type == TokenType::AMPER || tok.type == TokenType::STAR) {
            advance();
            return std::make_shared<PrefixNode>(PrefixNode(tok.line, tok, prefix_expr(terminator)));
        }
        else {
            return postfix_expr(terminator);
        }
    }

    std::shared_ptr<Node> Parser::bin_op_expr(const std::function<std::shared_ptr<Node>(const TokenType&) >& func, const std::vector<TokenType>& types, const TokenType& terminator) {
        std::shared_ptr<Node> left = func(terminator);
        while (std::find(types.begin(), types.end(), current.type) != types.end() && current.type != terminator) {
            Token op_tok = current;
            advance();
            std::shared_ptr<Node> right = func(terminator);
            left = std::make_shared<BinOpNode>(BinOpNode(left->line, left, op_tok, right));
        }
        return left;
    }

    std::shared_ptr<Node> Parser::term(const TokenType& terminator) {
        return bin_op_expr([this](const TokenType& terminator) { return prefix_expr(terminator); }, { TokenType::STAR, TokenType::SLASH, TokenType::MOD }, terminator);
    }

    std::shared_ptr<Node> Parser::factor(const TokenType& terminator) {
        return bin_op_expr([this](const TokenType& terminator) { return term(terminator); }, { TokenType::PLUS, TokenType::MINUS }, terminator);
    }

    std::shared_ptr<Node> Parser::shift_expr(const TokenType& terminator) {
        return bin_op_expr([this](const TokenType& terminator) { return factor(terminator); }, { TokenType::LSHIFT, TokenType::RSHIFT }, terminator);
    }

    std::shared_ptr<Node> Parser::cmp_expr(const TokenType& terminator) {
        return bin_op_expr([this](const TokenType& terminator) { return shift_expr(terminator); }, { TokenType::LESS, TokenType::LTEQ, TokenType::GREATER, TokenType::GTEQ }, terminator);
    }

    std::shared_ptr<Node> Parser::eq_expr(const TokenType& terminator) {
        return bin_op_expr([this](const TokenType& terminator) { return cmp_expr(terminator); }, { TokenType::EQUAL, TokenType::NOTEQ }, terminator);
    }

    std::shared_ptr<Node> Parser::and_expr(const TokenType& terminator) {
        return bin_op_expr([this](const TokenType& terminator) { return eq_expr(terminator); }, { TokenType::AMPER }, terminator);
    }

    std::shared_ptr<Node> Parser::xor_expr(const TokenType& terminator) {
        return bin_op_expr([this](const TokenType& terminator) { return and_expr(terminator); }, { TokenType::CARET }, terminator);
    }

    std::shared_ptr<Node> Parser::or_expr(const TokenType& terminator) {
        return bin_op_expr([this](const TokenType& terminator) { return xor_expr(terminator); }, { TokenType::PIPE }, terminator);
    }

    std::shared_ptr<Node> Parser::logand_expr(const TokenType& terminator) {
        return bin_op_expr([this](const TokenType& terminator) { return or_expr(terminator); }, { TokenType::LOGAND }, terminator);
    }

    std::shared_ptr<Node> Parser::logor_expr(const TokenType& terminator) {
        return bin_op_expr([this](const TokenType& terminator) { return logand_expr(terminator); }, { TokenType::LOGOR }, terminator);
    }

    std::shared_ptr<Node> Parser::assign_expr(const TokenType& terminator) {
        // return bin_op_expr([this](const TokenType& terminator) { return logor_expr(terminator); }, { TokenType::ASSIGN
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

        std::shared_ptr<Node> left = logor_expr(terminator);
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
            std::shared_ptr<Node> right = assign_expr(terminator);
            if (op_tok.type != TokenType::ASSIGN) {
                TokenType bin_op_type;
                switch (op_tok.type) {
                case TokenType::ASAND:
                    bin_op_type = TokenType::AMPER;
                    break;
                case TokenType::ASOR:
                    bin_op_type = TokenType::PIPE;
                    break;
                case TokenType::ASXOR:
                    bin_op_type = TokenType::CARET;
                case TokenType::ASLSHIFT:
                    bin_op_type = TokenType::LSHIFT;
                    break;
                case TokenType::ASRSHIFT:
                    bin_op_type = TokenType::RSHIFT;
                    break;
                case TokenType::ASPLUS:
                    bin_op_type = TokenType::PLUS;
                    break;
                case TokenType::ASMINUS:
                    bin_op_type = TokenType::MINUS;
                    break;
                case TokenType::ASMUL: {
                    bin_op_type = TokenType::STAR;
                    break;
                }
                case TokenType::ASDIV:
                    bin_op_type = TokenType::SLASH;
                    break;
                case TokenType::ASMOD:
                    bin_op_type = TokenType::MOD;
                    break;
                }

                Token op = Token(left->line, bin_op_type, std::string(1, op_tok.val[0]));
                std::cout << "dbg255 " << op_tok.val[0] << '\n';
                std::cout << "dbg256 " << op.to_str() << '\n';
                std::shared_ptr<Node> bin_op_node = std::make_shared<BinOpNode>(BinOpNode(left->line, left, op, right));
                Token assign = Token(left->line, TokenType::ASSIGN, "=");
                left = std::make_shared<AssignNode>(AssignNode(left->line, left, assign, bin_op_node));
                std::cout << "dbg257 " << left->to_str() << '\n';
            }
            else {
                left = std::make_shared<AssignNode>(AssignNode(left->line, left, op_tok, right));
            }
        }
        return left;
    }

    std::shared_ptr<Node> Parser::expr(const TokenType& terminator) {
        return assign_expr(terminator);
    }

    std::shared_ptr<Node> Parser::expr_stmt(const TokenType& terminator) {
        std::shared_ptr<Node> result = expr(TokenType::SEMI);
        eat(TokenType::SEMI);
        return result;
    }

    // std::shared_ptr<Node> Parser::expr_stmt(const TokenType& terminator) {
    //     std::shared_ptr<Node> result = expr(terminator);
    //     eat(TokenType::SEMI);
    //     return result;
    // }

    std::shared_ptr<Node> Parser::type(const TokenType& terminator) {
        int line = current.line;
        Token base_type = current;
        int num_pointers = 0;
        advance();
        while (current.type == TokenType::STAR) {
            num_pointers++;
            advance();
        }
        return std::make_shared<TypeNode>(TypeNode(line, base_type, num_pointers));
    }

    std::shared_ptr<Node> Parser::var_or_func_def_stmt(const TokenType& terminator) {
        std::shared_ptr<Node> my_type = type(terminator);
        Token name = eat(TokenType::IDENT);
        if (current.type == TokenType::LPAREN) {
            std::vector<std::shared_ptr<Node> > arg_types;
            std::vector<Token> arg_names;
            advance();
            if (current.type == TokenType::RPAREN) {
                advance();
            }
            else {
                while (current.type == TokenType::INT || current.type == TokenType::FLOAT || current.type == TokenType::CHAR || current.type == TokenType::VOID) {
                    arg_types.push_back(type());
                    arg_names.push_back(eat(TokenType::IDENT));

                    if (current.type == TokenType::RPAREN) {
                        advance();
                        break;
                    }
                    else {
                        eat(TokenType::COMMA);
                    }

                }
            }
            std::shared_ptr<Node> body = block_stmt();
            return std::make_shared<FuncDefNode>(FuncDefNode(my_type->line, my_type, name, arg_types, arg_names, body));
        }
        else {
            eat(TokenType::ASSIGN);
            std::shared_ptr<Node> val = expr_stmt(terminator);
            return std::make_shared<VarDefNode>(VarDefNode(my_type->line, my_type, name, val));
        }
    }

    std::shared_ptr<Node> Parser::block_stmt(const TokenType& terminator) {
        int line = current.line;
        eat(TokenType::LBRACE);
        std::shared_ptr<Node> my_stmt_list = stmt_list(TokenType::RBRACE);
        eat(TokenType::RBRACE);
        return std::make_shared<BlockNode>(BlockNode(line, my_stmt_list));
    }

    std::shared_ptr<Node> Parser::if_stmt(const TokenType& terminator) {
        int line = current.line;
        advance();
        eat(TokenType::LPAREN);
        std::shared_ptr<Node> cond = expr(TokenType::RPAREN);
        eat(TokenType::RPAREN);
        std::shared_ptr<Node> body = block_stmt(terminator);
        std::shared_ptr<Node> else_body;
        if (current.type == TokenType::ELSE) {
            advance();
            else_body = block_stmt(terminator);
        }
        return std::make_shared<IfNode>(IfNode(line, cond, body, else_body));
    }

    std::shared_ptr<Node> Parser::while_stmt(const TokenType& terminator) {
        int line = current.line;
        advance();
        eat(TokenType::LPAREN);
        std::shared_ptr<Node> cond = expr(TokenType::RPAREN);
        eat(TokenType::RPAREN);
        std::shared_ptr<Node> body = block_stmt(terminator);
        return std::make_shared<WhileNode>(WhileNode(line, cond, body));
    }

    std::shared_ptr<Node> Parser::for_stmt(const TokenType& terminator) {
        int line = current.line;
        advance();
        eat(TokenType::LPAREN);
        std::shared_ptr<Node> init = stmt(TokenType::SEMI);
        std::shared_ptr<Node> cond = expr_stmt(TokenType::SEMI);
        eat(TokenType::SEMI);
        std::shared_ptr<Node> update = expr(TokenType::RPAREN);
        eat(TokenType::RPAREN);
        std::shared_ptr<Node> body = block_stmt(terminator);
        return std::make_shared<ForNode>(ForNode(line, init, cond, update, body));
    }

    std::shared_ptr<Node> Parser::continue_stmt(const TokenType& terminator) {
        int line = current.line;
        advance();
        eat(TokenType::SEMI);
        return std::make_shared<ContinueNode>(ContinueNode(line));
    }


    std::shared_ptr<Node> Parser::break_stmt(const TokenType& terminator) {
        int line = current.line;
        advance();
        eat(TokenType::SEMI);
        return std::make_shared<BreakNode>(BreakNode(line));
    }

    std::shared_ptr<Node> Parser::return_stmt(const TokenType& terminator) {
        int line = current.line;
        advance(); // return

        std::shared_ptr<Node> body = expr(TokenType::SEMI);
        eat(TokenType::SEMI);

        return std::make_shared<ReturnNode>(ReturnNode(line, body));
    }

    // std::shared_ptr<Node> Parser::return_stmt(const TokenType& terminator) {
    //     int line = current.line;
    //     advance(); // eat return

    //     std::shared_ptr<Node> body = expr(TokenType::SEMI);
    //     eat(TokenType::SEMI);

    //     return std::make_shared<ReturnNode>(ReturnNode(line, body));
    // }

    // std::shared_ptr<Node> Parser::return_stmt(const TokenType& terminator) {
    //     int line = current.line;
    //     advance();
    //     std::shared_ptr<Node> body = expr_stmt(terminator);
    //     return std::make_shared<ReturnNode>(ReturnNode(line, body));
    // }

    std::shared_ptr<Node> Parser::enum_stmt(const TokenType& terminator) {
        int line = current.line;
        advance();
        Token name = eat(TokenType::IDENT);
        eat(TokenType::LBRACE);
        std::vector<Token> items;
        while (current.type != terminator) {
            items.push_back(eat(TokenType::IDENT));
            if (current.type == TokenType::RBRACE) {
                advance();
                eat(TokenType::SEMI);
                break;
            }
            else {
                eat(TokenType::COMMA);
            }
        }
        return std::make_shared<EnumNode>(EnumNode(line, name, items));
    }

    std::shared_ptr<Node> Parser::include_stmt(const TokenType& terminator) {
        int line = current.line;
        advance();
        Token path = eat(TokenType::STRLIT);
        return std::make_shared<IncludeNode>(IncludeNode(line, path));
    }

    std::shared_ptr<Node> Parser::stmt(const TokenType& terminator) {
        if (current.type == TokenType::INT || current.type == TokenType::FLOAT || current.type == TokenType::CHAR || current.type == TokenType::VOID) {
            return var_or_func_def_stmt(terminator);
        }
        else if (current.type == TokenType::LBRACE) {
            return block_stmt(terminator);
        }
        else if (current.type == TokenType::IF) {
            return if_stmt(terminator);
        }
        else if (current.type == TokenType::WHILE) {
            return while_stmt(terminator);
        }
        else if (current.type == TokenType::FOR) {
            return for_stmt(terminator);
        }
        else if (current.type == TokenType::CONTINUE) {
            return continue_stmt(terminator);
        }
        else if (current.type == TokenType::BREAK) {
            return break_stmt(terminator);
        }
        else if (current.type == TokenType::RETURN) {
            return return_stmt(terminator);
        }
        else if (current.type == TokenType::ENUM) {
            return enum_stmt(terminator);
        }
        else if (current.type == TokenType::INCLUDE) {
            return include_stmt(terminator);
        }
        else {
            return expr_stmt(terminator);
        }
    }

    std::shared_ptr<Node> Parser::stmt_list(const TokenType& terminator) {
        int line = current.line;
        std::vector<std::shared_ptr<Node>> stmts;

        while (current.type != terminator && current.type != TokenType::XEOF) {
            stmts.push_back(stmt(terminator));
        }

        std::cout << "dbg494 RUNNING NEW PARSER stmt_list terminator="
            << (int)terminator << "\n";

        return std::make_shared<StmtListNode>(line, stmts);
    }

    // std::shared_ptr<Node> Parser::stmt_list(const TokenType& terminator) {
    //     int line = current.line;
    //     std::vector<std::shared_ptr<Node> > stmts;
    //     while (current.type != terminator) {
    //         stmts.push_back(stmt(terminator));
    //     }
    //     return std::make_shared<StmtListNode>(line, stmts);
    // }
}