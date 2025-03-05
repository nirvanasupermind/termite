#include <string>
#include <memory>
#include <vector>
#include "token.h"
#include "node.h"

namespace anthill {
    CharNode::CharNode(int line, const Token& tok)
        : tok(tok) {
        this->line = line;
    }

    std::string CharNode::to_str() const {
        return tok.to_str();
    }

    NodeType CharNode::get_type() const {
        return NodeType::CHAR;
    }

    IntNode::IntNode(int line, const Token& tok)
        : tok(tok) {
            this->line = line;

    }

    std::string IntNode::to_str() const {
        return tok.to_str();
    }


    NodeType IntNode::get_type() const {
        return NodeType::INT;
    }


    UnaryOpNode::UnaryOpNode(int line, const Token& op_tok, const std::shared_ptr<Node>& node)
        : op_tok(op_tok), node(node) {
            this->line = line;
    }

    std::string UnaryOpNode::to_str() const {
        return "(" + op_tok.to_str() + "," + node->to_str() + ")";
    }


    NodeType UnaryOpNode::get_type() const {
        return NodeType::UNARY_OP;
    }


    BinOpNode::BinOpNode(int line, const std::shared_ptr<Node>& left_node, const Token& op_tok, const std::shared_ptr<Node>& right_node)
        : left_node(left_node), op_tok(op_tok), right_node(right_node) {
            this->line = line;

    }

    std::string BinOpNode::to_str() const {
        return "(" + left_node->to_str() + "," + op_tok.to_str() + "," + right_node->to_str() + ")";
    }

    NodeType BinOpNode::get_type() const {
        return NodeType::BIN_OP;
    }
}
