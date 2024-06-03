#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <memory>
#include <cstdint>
#include "token.h"

namespace anthill {
    enum class NodeType {
        INT,
        CHAR,
        STRING,
        IDENTIFIER,
        POINTER_TYPE,
        CALL,
        CAST,
        UNARY_OP,
        BINARY_OP,
        VAR_DEF,
        BLOCK,
        IF,
        IF_ELSE,
        WHILE,
        FOR,
        FUNC_DEF,
        RETURN,
        PRINT,
        STMT_LIST
    };

    class Node {
    public:
        int line;
        virtual ~Node() = default;
        virtual NodeType type() const = 0;
        std::string type_str() const;
        virtual std::string str() const = 0;
    };

    class IntNode : public Node {
    public:
        int32_t val;
        IntNode(int line, int32_t val);
        NodeType type() const;
        std::string str() const;
    };

    class CharNode : public Node {
    public:
        int16_t val;
        CharNode(int line, int16_t val);
        NodeType type() const;
        std::string str() const;
    };

    class StringNode : public Node {
    public:
        std::string val;
        StringNode(int line, const std::string& val);
        NodeType type() const;
        std::string str() const;
    };

    class IdentifierNode : public Node {
    public:
        std::string val;
        IdentifierNode(int line, const std::string& val);
        NodeType type() const;
        std::string str() const;
    };

    class PointerTypeNode : public Node {
    public:
        std::shared_ptr<Node> base_type;
        PointerTypeNode(int line, const std::shared_ptr<Node>& base_type);
        NodeType type() const;
        std::string str() const;
    };

    class CastNode : public Node {
    public:
        std::shared_ptr<Node> cast_type;
        std::shared_ptr<Node> val;
        CastNode(int line, const std::shared_ptr<Node>& cast_type, const std::shared_ptr<Node>& val);
        NodeType type() const;
        std::string str() const;
    };

    class CallNode : public Node {
    public:
        std::shared_ptr<Node> func;
        std::vector<std::shared_ptr<Node> > args;
        CallNode(int line, const std::shared_ptr<Node>& func, const std::vector<std::shared_ptr<Node> >& args);
        NodeType type() const;
        std::string str() const;
    };

    class UnaryOpNode : public Node {
    public:
        Token op;
        std::shared_ptr<Node> node;
        UnaryOpNode(int line, const Token& op, const std::shared_ptr<Node>& node);
        NodeType type() const;
        std::string str() const;
    };


    class BinaryOpNode : public Node {
    public:
        Token op;
        std::shared_ptr<Node> node_a;
        std::shared_ptr<Node> node_b;
        BinaryOpNode(int line, const Token& op, const std::shared_ptr<Node>& node_a, const std::shared_ptr<Node>& node_b);
        NodeType type() const;
        std::string str() const;
    };

    class VarDefNode : public Node {
    public:
        std::shared_ptr<Node> var_type;
        std::string name;
        std::shared_ptr<Node> val;
        VarDefNode(int line, const std::shared_ptr<Node>& var_type, const std::string& name, const std::shared_ptr<Node>& val);
        NodeType type() const;
        std::string str() const;
    };

    class BlockNode : public Node {
    public:
        std::shared_ptr<Node> stmt_list;
        BlockNode(int line, const std::shared_ptr<Node>& stmt_list);
        NodeType type() const;
        std::string str() const;
    };

    class IfNode : public Node {
    public:
        std::shared_ptr<Node> cond;
        std::shared_ptr<Node> body;
        IfNode(int line, const std::shared_ptr<Node>& cond, const std::shared_ptr<Node>& body);
        NodeType type() const;
        std::string str() const;
    };

    class IfElseNode : public Node {
    public:
        std::shared_ptr<Node> cond;
        std::shared_ptr<Node> if_body;
        std::shared_ptr<Node> else_body;
        IfElseNode(int line, const std::shared_ptr<Node>& cond, const std::shared_ptr<Node>& if_body, const std::shared_ptr<Node>& else_body);
        NodeType type() const;
        std::string str() const;
    };

    class WhileNode : public Node {
    public:
        std::shared_ptr<Node> cond;
        std::shared_ptr<Node> body;
        WhileNode(int line, const std::shared_ptr<Node>& cond, const std::shared_ptr<Node>& body);
        NodeType type() const;
        std::string str() const;
    };

    class ForNode : public Node {
    public:
        std::shared_ptr<Node> init;
        std::shared_ptr<Node> cond;
        std::shared_ptr<Node> update;
        std::shared_ptr<Node> body;
        ForNode(int line, const std::shared_ptr<Node>& init, const std::shared_ptr<Node>& cond, const std::shared_ptr<Node>& update, const std::shared_ptr<Node>& body);
        NodeType type() const;
        std::string str() const;
    };

    class FuncDefNode : public Node {
    public:
        std::shared_ptr<Node> return_type;
        std::string name;
        std::vector<std::shared_ptr<Node> > arg_types;
        std::vector<std::string> arg_names;
        std::shared_ptr<Node> body;
        FuncDefNode(int line, const std::shared_ptr<Node>& return_type, const std::string& name, const std::vector<std::shared_ptr<Node> >& arg_types,
            const std::vector<std::string>& arg_names, const std::shared_ptr<Node>& body);
        NodeType type() const;
        std::string str() const;
    };

    class ReturnNode : public Node {
    public:
        std::shared_ptr<Node> val;
        ReturnNode(int line, const std::shared_ptr<Node>& val);
        NodeType type() const;
        std::string str() const;
    };

    class PrintNode : public Node {
    public:
        std::shared_ptr<Node> val;
        PrintNode(int line, const std::shared_ptr<Node>& val);
        NodeType type() const;
        std::string str() const;
    };

    class StmtListNode : public Node {
    public:
        std::vector<std::shared_ptr<Node> > stmts;
        StmtListNode(int line, const std::vector<std::shared_ptr<Node> >& stmts);
        NodeType type() const;
        std::string str() const;
    };

} // namespace anthill

#endif