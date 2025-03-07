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

    StrNode::StrNode(int line, const Token& tok)
        : tok(tok) {
        this->line = line;

    }

    std::string StrNode::to_str() const {
        return tok.to_str();
    }


    NodeType StrNode::get_type() const {
        return NodeType::STR;
    }

    IdentNode::IdentNode(int line, const Token& tok)
        : tok(tok) {
        this->line = line;
    }

    std::string IdentNode::to_str() const {
        return tok.to_str();
    }


    NodeType IdentNode::get_type() const {
        return NodeType::IDENT;
    }

    PostfixNode::PostfixNode(int line, const std::shared_ptr<Node>& node, const Token& op_tok)
        : node(node), op_tok(op_tok) {
        this->line = line;
    }

    std::string PostfixNode::to_str() const {
        return "(" + op_tok.to_str() + "," + node->to_str() + ")";
    }

    NodeType PostfixNode::get_type() const {
        return NodeType::POSTFIX;
    }

    PrefixNode::PrefixNode(int line, const Token& op_tok, const std::shared_ptr<Node>& node)
        : op_tok(op_tok), node(node) {
        this->line = line;
    }

    std::string PrefixNode::to_str() const {
        return "(" + node->to_str() + "," + op_tok.to_str() + ")";
    }

    NodeType PrefixNode::get_type() const {
        return NodeType::PREFIX;
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


    AssignNode::AssignNode(int line, const std::shared_ptr<Node>& left_node, const Token& op_tok, const std::shared_ptr<Node>& right_node)
        : left_node(left_node), op_tok(op_tok), right_node(right_node) {
        this->line = line;
    }

    std::string AssignNode::to_str() const {
        return "(" + left_node->to_str() + "," + op_tok.to_str() + "," + right_node->to_str() + ")";
    }

    NodeType AssignNode::get_type() const {
        return NodeType::ASSIGN;
    }


    TypeNode::TypeNode(int line, const Token& base_type, int num_pointers)
        : base_type(base_type), num_pointers(num_pointers) {
        this->line = line;
    }

    std::string TypeNode::to_str() const {
        return "(" + base_type.to_str() + "," + std::to_string(num_pointers) + ")";
    }

    NodeType TypeNode::get_type() const {
        return NodeType::TYPE;
    }

    VarDefNode::VarDefNode(int line, const std::shared_ptr<Node>& type, const Token& name, const std::shared_ptr<Node>& val)
        : type(type), name(name), val(val) {
        this->line = line;
    }

    std::string VarDefNode::to_str() const {
        return "(" + type->to_str() + "," + name.to_str() + "," + val->to_str() + ")";
    }

    NodeType VarDefNode::get_type() const {
        return NodeType::VAR_DEF;
    }

    BlockNode::BlockNode(int line, const std::shared_ptr<Node>& stmt_list)
        : stmt_list(stmt_list) {
        this->line = line;
    }

    std::string BlockNode::to_str() const {
        return stmt_list->to_str();
    }

    NodeType BlockNode::get_type() const {
        return NodeType::BLOCK;
    }


    IfNode::IfNode(int line, const std::shared_ptr<Node>& cond, const std::shared_ptr<Node>& body, const std::shared_ptr<Node>& else_body)
        : cond(cond), body(body), else_body(else_body) {
        this->line = line;
    }

    std::string IfNode::to_str() const {
        if (else_body) {
            return "(" + cond->to_str() + "," + body->to_str() + "," + else_body->to_str() + ")";
        }
        else {
            return "(" + cond->to_str() + "," + body->to_str() + ")";
        }
    }

    NodeType IfNode::get_type() const {
        return NodeType::IF;
    }



    WhileNode::WhileNode(int line, const std::shared_ptr<Node>& cond, const std::shared_ptr<Node>& body)
        : cond(cond), body(body) {
        this->line = line;
    }

    std::string WhileNode::to_str() const {
        return "(" + cond->to_str() + "," + body->to_str() + ")";
    }

    NodeType WhileNode::get_type() const {
        return NodeType::WHILE;
    }

    EnumNode::EnumNode(int line, const std::vector<Token>& items)
        : items(items) {
        this->line = line;
    }

    std::string EnumNode::to_str() const {
        std::string result = "(";
        for (int i = 0; i < items.size(); i++) {
            result = result + items.at(i).to_str();
            if (i == items.size() - 1) {
                result = result + ")";
            }
            else {
                result = result + ",";
            }
        }
        return result;
    }

    NodeType EnumNode::get_type() const {
        return NodeType::ENUM;
    }


    StmtListNode::StmtListNode(int line, const std::vector<std::shared_ptr<Node> >& stmts)
        : stmts(stmts) {
        this->line = line;
    }

    std::string StmtListNode::to_str() const {
        std::string result = "(";
        for (int i = 0; i < stmts.size(); i++) {
            result = result + stmts.at(i)->to_str();
            if (i == stmts.size() - 1) {
                result = result + ")";
            }
            else {
                result = result + ",";
            }
        }
        return result;
    }

    NodeType StmtListNode::get_type() const {
        return NodeType::STMT_LIST;
    }

}
