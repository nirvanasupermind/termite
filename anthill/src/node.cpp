#include <string>
#include <vector>
#include <memory>
#include <cstdint>
#include "token.h"
#include "node.h"

namespace anthill {
    std::string Node::type_str() const {
        switch (type()) {
        case NodeType::INT:
            return "INT";
        case NodeType::CHAR:
            return "CHAR";
        case NodeType::UNARY_OP:
            return "UNARY_OP";
        case NodeType::BINARY_OP:
            return "BINARY_OP";
        case NodeType::VAR_DEF:
            return "VAR_DEF";
        case NodeType::STMT_LIST:
            return "PROGRAM";
        default:
            return "UNKNOWN";
        }
    }

    IntNode::IntNode(int line, int32_t val)
        : val(val) {
        this->line = line;
    }

    NodeType IntNode::type() const {
        return NodeType::INT;
    }

    std::string IntNode::str() const {
        return std::to_string(val);
    }

    CharNode::CharNode(int line, int16_t val)
        : val(val) {
        this->line = line;
    }

    NodeType CharNode::type() const {
        return NodeType::CHAR;
    }


    std::string CharNode::str() const {
        return std::string() + '\'' + (char)val + '\'';
    }


    StringNode::StringNode(int line, const std::string& val)
        : val(val) {
        this->line = line;
    }

    NodeType StringNode::type() const {
        return NodeType::STRING;
    }

    std::string StringNode::str() const {
        return '"' + val + '"';
    }

    IdentifierNode::IdentifierNode(int line, const std::string& val)
        : val(val) {
        this->line = line;
    }

    NodeType IdentifierNode::type() const {
        return NodeType::IDENTIFIER;
    }

    std::string IdentifierNode::str() const {
        return val;
    }

    PointerTypeNode::PointerTypeNode(int line, const std::shared_ptr<Node>& base_type)
        : base_type(base_type) {
        this->line = line;
    }

    NodeType PointerTypeNode::type() const {
        return NodeType::POINTER_TYPE;
    }

    std::string PointerTypeNode::str() const {
        return base_type->str() + "*";
    }

    CallNode::CallNode(int line, const std::shared_ptr<Node>& func, const std::vector<std::shared_ptr<Node> >& args)
        : func(func), args(args) {
        this->line = line;
    }

    NodeType CallNode::type() const {
        return NodeType::CALL;
    }

    std::string CallNode::str() const {
        std::string result = "(" + func->str();
        for (int i = 0; i < args.size(); i++) {
            result = result + ' ' + args.at(i)->str();
        }
        result = result + ')';
        return result;
    }


    CastNode::CastNode(int line, const std::shared_ptr<Node>& cast_type, const std::shared_ptr<Node>& val)
        : cast_type(cast_type), val(val) {
        this->line = line;
    }

    NodeType CastNode::type() const {
        return NodeType::CAST;
    }

    std::string CastNode::str() const {
        return "(cast " + cast_type->str() + " " + val->str() + ")";
    }

    UnaryOpNode::UnaryOpNode(int line, const Token& op, const std::shared_ptr<Node>& node)
        : op(op), node(node) {
        this->line = line;
    }

    NodeType UnaryOpNode::type() const {
        return NodeType::UNARY_OP;
    }

    std::string UnaryOpNode::str() const {
        return '(' + op.val + ' ' + node->str() + ')';
    }

    BinaryOpNode::BinaryOpNode(int line, const Token& op, const std::shared_ptr<Node>& node_a, const std::shared_ptr<Node>& node_b)
        : op(op), node_a(node_a), node_b(node_b) {
        this->line = line;
    }

    NodeType BinaryOpNode::type() const {
        return NodeType::BINARY_OP;
    }

    std::string BinaryOpNode::str() const {
        return '(' + op.val + ' ' + node_a->str() + ' ' + node_b->str() + ')';
    }

    VarDefNode::VarDefNode(int line, const std::shared_ptr<Node>& var_type, const std::string& name, const std::shared_ptr<Node>& val)
        : var_type(var_type), name(name), val(val) {
        this->line = line;
    }

    NodeType VarDefNode::type() const {
        return NodeType::VAR_DEF;
    }

    std::string VarDefNode::str() const {
        return '(' + var_type->str() + ' ' + name + ' ' + val->str() + ')';
    }

    BlockNode::BlockNode(int line, const std::shared_ptr<Node>& stmt_list)
        : stmt_list(stmt_list) {
        this->line = line;
    }

    NodeType BlockNode::type() const {
        return NodeType::BLOCK;
    }

    std::string BlockNode::str() const {
        return "(block " + stmt_list->str() + ")";
    }

    IfNode::IfNode(int line, const std::shared_ptr<Node>& cond, const std::shared_ptr<Node>& body)
        : cond(cond), body(body) {
        this->line = line;
    }

    NodeType IfNode::type() const {
        return NodeType::IF;
    }

    std::string IfNode::str() const {
        return "(if " + cond->str() + " " + body->str() + ")";
    }

    IfElseNode::IfElseNode(int line, const std::shared_ptr<Node>& cond, const std::shared_ptr<Node>& if_body, const std::shared_ptr<Node>& else_body)
        : cond(cond), if_body(if_body), else_body(else_body) {
        this->line = line;
    }

    NodeType IfElseNode::type() const {
        return NodeType::IF_ELSE;
    }

    std::string IfElseNode::str() const {
        return "(if-else " + cond->str() + " " + if_body->str() + " " + else_body->str() + ")";
    }

    WhileNode::WhileNode(int line, const std::shared_ptr<Node>& cond, const std::shared_ptr<Node>& body)
        : cond(cond), body(body) {
        this->line = line;
    }

    NodeType WhileNode::type() const {
        return NodeType::WHILE;
    }

    std::string WhileNode::str() const {
        return "(while " + cond->str() + " " + body->str() + ")";
    }

    ForNode::ForNode(int line, const std::shared_ptr<Node>& init, const std::shared_ptr<Node>& cond, const std::shared_ptr<Node>& update, const std::shared_ptr<Node>& body)
        : init(init), cond(cond), update(update), body(body) {
        this->line = line;
    }

    NodeType ForNode::type() const {
        return NodeType::FOR;
    }

    std::string ForNode::str() const {
        return "(for " + init->str() + " " + init->str() + " " + cond->str() + " " + update->str() + " " + body->str() + ")";
    }

    ReturnNode::ReturnNode(int line, const std::shared_ptr<Node>& val)
        : val(val) {
        this->line = line;
    }

    NodeType ReturnNode::type() const {
        return NodeType::RETURN;
    }

    std::string ReturnNode::str() const {
        return "(return " + val->str() + ")";
    }

    FuncDefNode::FuncDefNode(int line, const std::shared_ptr<Node>& return_type, const std::string& name,
        const std::vector<std::shared_ptr<Node> >& arg_types, const std::vector<std::string >& arg_names,
        const std::shared_ptr<Node>& body)
        : return_type(return_type), name(name), arg_types(arg_types), arg_names(arg_names), body(body) {
        this->line = line;
    }

    NodeType FuncDefNode::type() const {
        return NodeType::FUNC_DEF;
    }

    std::string FuncDefNode::str() const {
        std::string result = "(" + return_type->str() + ' ' + name + " (";
        for (int i = 0; i < arg_types.size(); i++) {
            result = result + "(" + arg_types.at(i)->str() + ' ' + arg_names.at(i) + ") ";
        }
        if(arg_types.size()) {
            result.pop_back();
        }
        result = result + ") " + body->str() + ')';
        return result;
    }


    StmtListNode::StmtListNode(int line, const std::vector<std::shared_ptr<Node> >& stmts)
        : stmts(stmts) {
        this->line = line;
    }


    NodeType StmtListNode::type() const {
        return NodeType::STMT_LIST;
    }

    std::string StmtListNode::str() const {
        std::string result = "(stmt-list";
        for (int i = 0; i < stmts.size(); i++) {
            result += ' ' + stmts.at(i)->str();
        }
        result += ')';
        return result;
    }
} // namespace anthill
