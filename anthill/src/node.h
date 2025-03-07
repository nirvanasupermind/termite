#ifndef NODE_H
#define NODE_H

#include <string>
#include <memory>
#include <vector>
#include "token.h"

namespace anthill {
    enum class NodeType {
        CHAR,
        INT,
        STR,
        IDENT,
        POSTFIX,
        PREFIX,
        BIN_OP,
        ASSIGN,
        TYPE,
        VAR_DEF,
        BLOCK,
        IF,
        WHILE,
        FOR,
        RETURN,
        ENUM,
        STMT_LIST
    };
    class Node {
    public:
        int line;
        virtual std::string to_str() const = 0;
        virtual NodeType get_type() const = 0;
    };

    class CharNode : public Node {
    public:
        Token tok;
        CharNode(int line, const Token& tok);
        std::string to_str() const;
        NodeType get_type() const;
    };

    class IntNode : public Node {
    public:
        Token tok;
        IntNode(int line, const Token& tok);
        std::string to_str() const;
        NodeType get_type() const;
    };



    class StrNode : public Node {
    public:
        Token tok;
        StrNode(int line, const Token& tok);
        std::string to_str() const;
        NodeType get_type() const;
    };


    class IdentNode : public Node {
    public:
        Token tok;
        IdentNode(int line, const Token& tok);
        std::string to_str() const;
        NodeType get_type() const;
    };

    class PostfixNode : public Node {
    public:
        std::shared_ptr<Node> node;
        Token op_tok;
        PostfixNode(int line, const std::shared_ptr<Node>& node, const Token& op_tok);
        std::string to_str() const;
        NodeType get_type() const;
    };

    class PrefixNode : public Node {
    public:
        Token op_tok;
        std::shared_ptr<Node> node;
        PrefixNode(int line, const Token& top_ok, const std::shared_ptr<Node>& node);
        std::string to_str() const;
        NodeType get_type() const;
    };

    class BinOpNode : public Node {
    public:
        std::shared_ptr<Node> left_node;
        Token op_tok;
        std::shared_ptr<Node> right_node;
        BinOpNode(int line, const std::shared_ptr<Node>& left_node, const Token& op_tok, const std::shared_ptr<Node>& right_node);
        std::string to_str() const;
        NodeType get_type() const;
    };

    class AssignNode : public Node {
    public:
        std::shared_ptr<Node> left_node;
        Token op_tok;
        std::shared_ptr<Node> right_node;
        AssignNode(int line, const std::shared_ptr<Node>& left_node, const Token& op_tok, const std::shared_ptr<Node>& right_node);
        std::string to_str() const;
        NodeType get_type() const;
    };


    class TypeNode : public Node {
    public:
        Token base_type;
        int num_pointers;
        TypeNode(int line, const Token& base_type, int num_pointers);
        std::string to_str() const;
        NodeType get_type() const;
    };

    class VarDefNode : public Node {
    public:
        std::shared_ptr<Node> type;
        Token name;
        std::shared_ptr<Node> val;
        VarDefNode(int line, const std::shared_ptr<Node>& type, const Token& name, const std::shared_ptr<Node>& val);
        std::string to_str() const;
        NodeType get_type() const;
    };


    class BlockNode : public Node {
    public:
        std::shared_ptr<Node> stmt_list;
        BlockNode(int line, const std::shared_ptr<Node>& stmt_list);
        std::string to_str() const;
        NodeType get_type() const;
    };


    class IfNode : public Node {
    public:
        std::shared_ptr<Node> cond;
        std::shared_ptr<Node> body;
        std::shared_ptr<Node> else_body;
        IfNode(int line, const std::shared_ptr<Node>& cond, const std::shared_ptr<Node>& body, const std::shared_ptr<Node>& else_body);
        std::string to_str() const;
        NodeType get_type() const;
    };


    class WhileNode : public Node {
    public:
        std::shared_ptr<Node> cond;
        std::shared_ptr<Node> body;
        WhileNode(int line, const std::shared_ptr<Node>& cond, const std::shared_ptr<Node>& body);
        std::string to_str() const;
        NodeType get_type() const;
    };


    class ForNode : public Node {
        public:
        std::shared_ptr<Node> init;
        std::shared_ptr<Node> cond;
        std::shared_ptr<Node> update;
        std::shared_ptr<Node> body;
            ForNode(int line, const std::shared_ptr<Node>& init, const std::shared_ptr<Node>& cond, const std::shared_ptr<Node>& update, const std::shared_ptr<Node>& body);
            std::string to_str() const;
            NodeType get_type() const;
        };
    

    class ReturnNode : public Node {
        public:
        std::shared_ptr<Node> body;
            ReturnNode(int line, const std::shared_ptr<Node>& body);
            std::string to_str() const;
            NodeType get_type() const;
        };

    class EnumNode : public Node {
    public:
        Token name;
        std::vector<Token> items;
        EnumNode(int line, const Token& name, const std::vector<Token>& items);
        std::string to_str() const;
        NodeType get_type() const;
    };

    class StmtListNode : public Node {
    public:
        std::vector<std::shared_ptr<Node> > stmts;
        StmtListNode(int line, const std::vector<std::shared_ptr<Node> >& stmts);
        std::string to_str() const;
        NodeType get_type() const;
    };

}

#endif