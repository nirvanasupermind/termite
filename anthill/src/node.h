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
        UNARY_OP,
        BIN_OP
    };
    class Node {
    public:
        int line;
        virtual std::string to_str() const = 0;
        virtual NodeType get_type() const = 0;
    };

    class CharNode: public Node {
        public:
            Token tok;
            CharNode(int line, const Token& tok);
            std::string to_str() const;
            NodeType get_type() const;
        };

    class IntNode: public Node {
    public:
    Token tok;
    IntNode(int line, const Token& tok);
        std::string to_str() const;
        NodeType get_type() const;
    };

    class UnaryOpNode: public Node {
        public:
            Token op_tok;
            std::shared_ptr<Node> node;
            UnaryOpNode(int line, const Token& tok, const std::shared_ptr<Node>& node);
            std::string to_str() const;
            NodeType get_type() const;
        };

    class BinOpNode: public Node {
    public:
    std::shared_ptr<Node> left_node;
    Token op_tok;
    std::shared_ptr<Node> right_node;
    BinOpNode(int line, const std::shared_ptr<Node>& left_node, const Token& op_tok, const std::shared_ptr<Node>& right_node);
    std::string to_str() const;
    NodeType get_type() const;    
};
        
}

#endif