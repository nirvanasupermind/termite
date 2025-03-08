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

    std::shared_ptr<Node> Parser::basic_expr(const SymbolTable& symbol_table, const TokenType& terminator) {
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
            std::shared_ptr<Node> result = expr(symbol_table, terminator);
            eat(TokenType::RPAREN);
            return result;
        }
        else {
            syntax_error();
        }
    }

    std::shared_ptr<Node> Parser::call_expr(const SymbolTable& symbol_table, const TokenType& terminator) {
        std::shared_ptr<Node> result = basic_expr(symbol_table, terminator);
        while (current.type == TokenType::LPAREN && current.type != terminator) {
            advance();
            std::vector<std::shared_ptr<Node> > args;
            if(current.type == TokenType::RPAREN) {
                advance();
            } else {
            while (current.type != TokenType::RPAREN) {
                args.push_back(expr());
            if(current.type == TokenType::RPAREN) {
                advance();
                break;
            } else {
                eat(TokenType::COMMA);
            }   
            }
            }
            result = std::make_shared<CallNode>(CallNode(result->line, result, args));
        }
        return result;
    }

    std::shared_ptr<Node> Parser::postfix_expr(const SymbolTable& symbol_table, const TokenType& terminator) {
        std::shared_ptr<Node> result = call_expr(symbol_table, terminator);
        while ((current.type == TokenType::INCR || current.type == TokenType::DECR) && current.type != terminator) {
            result = std::make_shared<PostfixNode>(PostfixNode(result->line, result, current));
            advance();
        }
        return result;
    }

    std::shared_ptr<Node> Parser::prefix_expr(const SymbolTable& symbol_table, const TokenType& terminator) {
        Token tok = current;
        if (tok.type == TokenType::PLUS || tok.type == TokenType::MINUS || tok.type == TokenType::NOT || tok.type == TokenType::AMPER || tok.type == TokenType::STAR) {
            advance();
            return std::make_shared<PrefixNode>(PrefixNode(tok.line, tok, postfix_expr(symbol_table, terminator)));
        }
        else {
            return postfix_expr(symbol_table, terminator);
        }
    }

    std::shared_ptr<Node> Parser::bin_op_expr(const SymbolTable& symbol_table, const std::function<std::shared_ptr<Node>(const TokenType&) >& func, const std::vector<TokenType>& types, const TokenType& terminator) {
        std::shared_ptr<Node> left = func(symbol_table, terminator);
        while (std::find(types.begin(), types.end(), current.type) != types.end() && current.type != terminator) {
            Token op_tok = current;
            advance();
            std::shared_ptr<Node> right = func(symbol_table, terminator);
            left = std::make_shared<BinOpNode>(BinOpNode(left->line, left, op_tok, right));
        }
        return left;
    }

    std::shared_ptr<Node> Parser::term(const SymbolTable& symbol_table, const TokenType& terminator) {
        return bin_op_expr([this](const SymbolTable& symbol_table, const TokenType& terminator) { return prefix_expr(symbol_table, terminator); }, { TokenType::STAR, TokenType::SLASH, TokenType::MOD });
    }

    std::shared_ptr<Node> Parser::factor(const SymbolTable& symbol_table, const TokenType& terminator) {
        return bin_op_expr([this](const SymbolTable& symbol_table, const TokenType& terminator) { return term(symbol_table, terminator); }, { TokenType::PLUS, TokenType::MINUS });
    }

    std::shared_ptr<Node> Parser::shift_expr(const SymbolTable& symbol_table, const TokenType& terminator) {
        return bin_op_expr([this](const SymbolTable& symbol_table, const TokenType& terminator) { return factor(symbol_table, terminator); }, { TokenType::LSHIFT, TokenType::RSHIFT });
    }

    std::shared_ptr<Node> Parser::cmp_expr(const SymbolTable& symbol_table, const TokenType& terminator) {
        return bin_op_expr([this](const SymbolTable& symbol_table, const TokenType& terminator) { return shift_expr(symbol_table, terminator); }, { TokenType::LESS, TokenType::LTEQ, TokenType::GREATER, TokenType::GTEQ });
    }

    std::shared_ptr<Node> Parser::eq_expr(const SymbolTable& symbol_table, const TokenType& terminator) {
        return bin_op_expr([this](const SymbolTable& symbol_table, const TokenType& terminator) { return cmp_expr(symbol_table, terminator); }, { TokenType::EQUAL, TokenType::NOTEQ });
    }

    std::shared_ptr<Node> Parser::and_expr(const SymbolTable& symbol_table, const TokenType& terminator) {
        return bin_op_expr([this](const SymbolTable& symbol_table, const TokenType& terminator) { return eq_expr(symbol_table, terminator); }, { TokenType::AMPER });
    }

    std::shared_ptr<Node> Parser::xor_expr(const SymbolTable& symbol_table, const TokenType& terminator) {
        return bin_op_expr([this](const SymbolTable& symbol_table, const TokenType& terminator) { return and_expr(symbol_table, terminator); }, { TokenType::CARET });
    }

    std::shared_ptr<Node> Parser::or_expr(const SymbolTable& symbol_table, const TokenType& terminator) {
        return bin_op_expr([this](const SymbolTable& symbol_table, const TokenType& terminator) { return xor_expr(symbol_table, terminator); }, { TokenType::PIPE });
    }

    std::shared_ptr<Node> Parser::logand_expr(const SymbolTable& symbol_table, const TokenType& terminator) {
        return bin_op_expr([this](const SymbolTable& symbol_table, const TokenType& terminator) { return or_expr(symbol_table, terminator); }, { TokenType::LOGAND });
    }

    std::shared_ptr<Node> Parser::logor_expr(const SymbolTable& symbol_table, const TokenType& terminator) {
        return bin_op_expr([this](const SymbolTable& symbol_table, const TokenType& terminator) { return logand_expr(symbol_table, terminator); }, { TokenType::LOGOR });
    }

    std::shared_ptr<Node> Parser::assign_expr(const SymbolTable& symbol_table, const TokenType& terminator) {
        // return bin_op_expr([this](const SymbolTable& symbol_table, const TokenType& terminator) { return logor_expr(symbol_table, terminator); }, { TokenType::ASSIGN
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

        std::shared_ptr<Node> left = logor_expr(symbol_table, terminator);
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
            std::shared_ptr<Node> right = assign_expr(symbol_table, terminator);
            left = std::make_shared<AssignNode>(AssignNode(left->line, left, op_tok, right));
        }
        return left;
    }

    std::shared_ptr<Node> Parser::expr(const SymbolTable& symbol_table, const TokenType& terminator) {
        return assign_expr(symbol_table, terminator);
    }

    std::shared_ptr<Node> Parser::expr_stmt(const SymbolTable& symbol_table, const TokenType& terminator) {
        std::shared_ptr<Node> result = expr(symbol_table, terminator);
        eat(TokenType::SEMI);
        return result;
    }

    std::shared_ptr<Node> Parser::type(const SymbolTable& symbol_table, const TokenType& terminator) {
        int line = current.line;
        Token base_type = current;
        int num_pointers = 0;
        advance();
        while(current.type == TokenType::STAR) {
            num_pointers++;
            advance();
        }
        return std::make_shared<TypeNode>(TypeNode(line, base_type, num_pointers));
    }

    std::shared_ptr<Node> Parser::var_or_func_def_stmt(const SymbolTable& symbol_table, const TokenType& terminator) {
        std::shared_ptr<Node> my_type = type(symbol_table, terminator);
        Token name = eat(TokenType::IDENT);
        if(current.type == TokenType::LPAREN) {
            std::vector<std::shared_ptr<Node> > arg_types;
            std::vector<Token> arg_names;
            advance();
            if(current.type == TokenType::RPAREN) {
                advance();
            } else {
            while(current.type == TokenType::INT || current.type == TokenType::CHAR || current.type == TokenType::VOID) {
                arg_types.push_back(type());
                arg_names.push_back(eat(TokenType::IDENT));

                if(current.type == TokenType::RPAREN) {
                    advance();
                    break;
                } else {
                eat(TokenType::COMMA);
                }
               
            }
            }
            std::shared_ptr<Node> body = block_stmt();
            return std::make_shared<FuncDefNode>(FuncDefNode(my_type->line, my_type, name, arg_types, arg_names, body));
        } else {
        eat(TokenType::ASSIGN);
        std::shared_ptr<Node> val = expr_stmt(symbol_table, terminator);
        return std::make_shared<VarDefNode>(VarDefNode(my_type->line, my_type, name, val));
        }
    }

    std::shared_ptr<Node> Parser::block_stmt(const SymbolTable& symbol_table, const TokenType& terminator) {
        int line = current.line;
        eat(TokenType::LBRACE);
        std::shared_ptr<Node> my_stmt_list = stmt_list(TokenType::RBRACE);
        eat(TokenType::RBRACE);
        return std::make_shared<BlockNode>(BlockNode(line, my_stmt_list));
    }

    
    std::shared_ptr<Node> Parser::if_stmt(const SymbolTable& symbol_table, const TokenType& terminator) {
        int line = current.line;
        advance();
        eat(TokenType::LPAREN);
        std::shared_ptr<Node> cond = expr(symbol_table, terminator);
        eat(TokenType::RPAREN);
        std::shared_ptr<Node> body = block_stmt(symbol_table, terminator);
        std::shared_ptr<Node> else_body;
        if(current.type == TokenType::ELSE) {
            advance();
            else_body = block_stmt(symbol_table, terminator);
        }
        return std::make_shared<IfNode>(IfNode(line, cond, body, else_body));
    }


        
    std::shared_ptr<Node> Parser::while_stmt(const SymbolTable& symbol_table, const TokenType& terminator) {
        int line = current.line;
        advance();
        eat(TokenType::LPAREN);
        std::shared_ptr<Node> cond = expr(symbol_table, terminator);
        eat(TokenType::RPAREN);
        std::shared_ptr<Node> body = block_stmt(symbol_table, terminator);
        return std::make_shared<WhileNode>(WhileNode(line, cond, body));
    }

    std::shared_ptr<Node> Parser::for_stmt(const SymbolTable& symbol_table, const TokenType& terminator) {
        int line = current.line;
        advance();
        eat(TokenType::LPAREN);
        std::shared_ptr<Node> init = stmt(symbol_table, terminator);
        std::shared_ptr<Node> cond = expr_stmt(symbol_table, terminator);
        std::shared_ptr<Node> update = expr(symbol_table, terminator);
        eat(TokenType::RPAREN);
        std::shared_ptr<Node> body = block_stmt(symbol_table, terminator);
        return std::make_shared<ForNode>(ForNode(line, init, cond, update, body));
    }

    std::shared_ptr<Node> Parser::continue_stmt(const SymbolTable& symbol_table, const TokenType& terminator) {
        int line = current.line;
        advance();
        eat(TokenType::SEMI);
        return std::make_shared<ContinueNode>(ContinueNode(line));
    }
    

    std::shared_ptr<Node> Parser::break_stmt(const SymbolTable& symbol_table, const TokenType& terminator) {
        int line = current.line;
        advance();
        eat(TokenType::SEMI);
        return std::make_shared<BreakNode>(BreakNode(line));
    }
    
    std::shared_ptr<Node> Parser::return_stmt(const SymbolTable& symbol_table, const TokenType& terminator) {
        int line = current.line;
        advance();
        std::shared_ptr<Node> body = expr_stmt(symbol_table, terminator);
        return std::make_shared<ReturnNode>(ReturnNode(line, body));
    }

    std::shared_ptr<Node> Parser::enum_stmt(const SymbolTable& symbol_table, const TokenType& terminator) {
        int line = current.line;
        advance();
        Token name = eat(TokenType::IDENT);
        eat(TokenType::LBRACE);
        std::vector<Token> items;
        while(current.type != terminator) {
            items.push_back(eat(TokenType::IDENT));
            if(current.type == TokenType::RBRACE) {
                advance();
                eat(TokenType::SEMI);
                break;
            } else {
                eat(TokenType::COMMA);
            }
        }
        return std::make_shared<EnumNode>(EnumNode(line, name, items));
    }
    
    std::shared_ptr<Node> Parser::stmt(const SymbolTable& symbol_table, const TokenType& terminator) {
        if(current.type == TokenType::INT || current.type == TokenType::CHAR || current.type == TokenType::VOID) {
            return var_or_func_def_stmt(symbol_table, terminator);
        } else if(current.type == TokenType::LBRACE) {
            return block_stmt(symbol_table, terminator);
        } else if(current.type == TokenType::IF) {
            return if_stmt(symbol_table, terminator);
        }  else if(current.type == TokenType::WHILE) {
            return while_stmt(symbol_table, terminator);
        } else if(current.type == TokenType::FOR) {
            return for_stmt(symbol_table, terminator);
        } else if(current.type == TokenType::CONTINUE) {
            return continue_stmt(symbol_table, terminator);
        } else if(current.type == TokenType::BREAK) {
            return break_stmt(symbol_table, terminator);
        } else if(current.type == TokenType::RETURN) {
            return return_stmt(symbol_table, terminator);
        } else if(current.type == TokenType::ENUM) {
            return enum_stmt(symbol_table, terminator);
        } else {
            return expr_stmt(symbol_table, terminator);
        }
    }

    std::shared_ptr<Node> Parser::stmt_list(const SymbolTable& symbol_table, const TokenType& terminator) {
        int line = current.line;
        std::vector<std::shared_ptr<Node> > stmts;
        while (current.type != terminator) {
            stmts.push_back(stmt());
        }
        return std::make_shared<StmtListNode>(line, stmts);
    }
}