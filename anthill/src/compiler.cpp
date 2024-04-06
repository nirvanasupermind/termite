#include <iostream>
#include <cinttypes>
#include <memory>
#include <string>

#include "token.h"
#include "node.h"
#include "static_type.h"
#include "env.h"
#include "compiler.h"

namespace anthill {
    Compiler::Compiler(const std::string& filename)
        : filename(filename), assembly(std::string("")), var_addr_counter(0), label_counter(0) {
    }

    StaticType Compiler::visit(const std::shared_ptr<Node>& node, const std::shared_ptr<Env>& env) {
        switch (node->type()) {
        case NodeType::INT:
            return visit_int_node(std::dynamic_pointer_cast<IntNode>(node), env);
        case NodeType::CHAR:
            return visit_char_node(std::dynamic_pointer_cast<CharNode>(node), env);
        case NodeType::IDENTIFIER:
            return visit_identifier_node(std::dynamic_pointer_cast<IdentifierNode>(node), env);
        case NodeType::UNARY_OP:
            return visit_unary_op_node(std::dynamic_pointer_cast<UnaryOpNode>(node), env);
        case NodeType::BINARY_OP:
            return visit_binary_op_node(std::dynamic_pointer_cast<BinaryOpNode>(node), env);
        case NodeType::VAR_DEF:
            return visit_var_def_node(std::dynamic_pointer_cast<VarDefNode>(node), env);
        case NodeType::BLOCK:
            return visit_block_node(std::dynamic_pointer_cast<BlockNode>(node), env);
        case NodeType::IF:
            return visit_if_node(std::dynamic_pointer_cast<IfNode>(node), env);
        case NodeType::IF_ELSE:
            return visit_if_else_node(std::dynamic_pointer_cast<IfElseNode>(node), env);
        case NodeType::WHILE:
            return visit_while_node(std::dynamic_pointer_cast<WhileNode>(node), env);
        case NodeType::STMT_LIST:
            return visit_stmt_list_node(std::dynamic_pointer_cast<StmtListNode>(node), env);
        default:
            throw std::string(filename + ':' + std::to_string(node->line) + ": unknown node type " + node->type_str());
            break;
        }
    }

    void Compiler::movi_16trit(int8_t reg, int32_t val) {
        std::string reg_str = std::to_string(reg);
        int32_t abs_val = std::abs(val);
        if (std::abs(val) > 9841) {
            int32_t quo = val + 364;
            int32_t high_10_trits = quo / 729;
            int32_t low_6_trits = quo % 729 - 364;
            assembly += "movi r" + reg_str + ", " + std::to_string(high_10_trits) + ";\n";
            assembly += "lshi r" + reg_str + ", r" + reg_str + ", 6;\n";
            assembly += "addi r" + reg_str + ", r" + reg_str + ", " + std::to_string(low_6_trits) + ";\n";
        }
        else {
            assembly += "movi r" + reg_str + ", " + std::to_string(val) + ";\n";
        }
    }

    StaticType Compiler::visit_int_node(const std::shared_ptr<IntNode>& node, const std::shared_ptr<Env>& env) {
        movi_16trit(-13, node->val);
        return StaticType(BasicType::INT);
    }

    StaticType Compiler::visit_identifier_node(const std::shared_ptr<IdentifierNode>& node, const std::shared_ptr<Env>& env) {
        try {
            StaticType type = env->get_type(node->val);
            int32_t addr = env->get_addr(node->val);
            movi_16trit(-11, addr);
            assembly += "ld r-13, r-11, 0;\n";
            // if (type.size() == 1) {
            //     assembly += "lshi r-13, r-13, 8;\nrshi r-13, r-13, 8;\n";
            //     // Trick to remove the upper 8 trits
            // }
            return type;
        }
        catch (const std::string& e) {
            throw std::string(filename + ':' + std::to_string(node->line) + ": " + e);
        }

    }

    StaticType Compiler::visit_char_node(const std::shared_ptr<CharNode>& node,  const std::shared_ptr<Env>& env) {
        assembly += "movi r-13, " + std::to_string((int)node->val) + ";\n";
        return StaticType(BasicType::CHAR);
    }

    StaticType Compiler::visit_unary_op_node(const std::shared_ptr<UnaryOpNode>& node, const std::shared_ptr<Env>& env) {
        switch (node->op.type) {
        case TokenType::PLUS: {
            StaticType type = visit(node->node, env);
            if (!(type.basic_type == BasicType::INT && type.pointer_levels == 0)) {
                throw std::string(filename + ':' + std::to_string(node->line) + ": invalid operand '" + type.str() + " for unary minus");
            }
            return StaticType(BasicType::INT);
        }
        case TokenType::MINUS: {
            StaticType type = visit(node->node, env);
            if (!(type.basic_type == BasicType::INT && type.pointer_levels == 0)) {
                throw std::string(filename + ':' + std::to_string(node->line) + ": invalid operand '" + type.str() + " for unary minus");
            }
            assembly += "muli r-13, r-13, -1;\n";
            return StaticType(BasicType::INT);
        }
        default:
            break;
        }
    }

    StaticType Compiler::visit_binary_op_node(const std::shared_ptr<BinaryOpNode>& node, const std::shared_ptr<Env>& env) {
        switch (node->op.type) {
        case TokenType::PLUS: {
            StaticType a_type = visit(node->node_a, env);
            assembly += "mov r-12, r-13;\n";
            StaticType b_type = visit(node->node_b, env);
            assembly += "add r-13, r-12, r-13;\n";
            if(a_type.str() == "char" && b_type.str() == "char") {
                assembly += "lshi r-13, r-13, 8;\nrshi r-13, r-13, 8;\n";
                return StaticType(BasicType::CHAR);
            } else {
                return StaticType(BasicType::INT);
            }
        }
        case TokenType::MINUS: {
            StaticType a_type = visit(node->node_a, env);
            assembly += "mov r-12, r-13;\n";
            StaticType b_type = visit(node->node_b, env);
            assembly += "sub r-13, r-12, r-13;\n";
            if(a_type.str() == "char" && b_type.str() == "char") {
                assembly += "lshi r-13, r-13, 8;\nrshi r-13, r-13, 8;\n";
                return StaticType(BasicType::CHAR);
            } else {
                return StaticType(BasicType::INT);
            }
        }
        case TokenType::MUL: {
            StaticType a_type = visit(node->node_a, env);
            assembly += "mov r-12, r-13;\n";
            StaticType b_type = visit(node->node_b, env);
            assembly += "mul r-13, r-12, r-13;\n";
            if(a_type.str() == "char" && b_type.str() == "char") {
                assembly += "lshi r-13, r-13, 8;\nrshi r-13, r-13, 8;\n";
                return StaticType(BasicType::CHAR);
            } else {
                return StaticType(BasicType::INT);
            }
        }
        case TokenType::DIV: {
            StaticType a_type = visit(node->node_a, env);
            assembly += "mov r-12, r-13;\n";
            StaticType b_type = visit(node->node_b, env);
            assembly += "div r-13, r-12, r-13;\n";
            if(a_type.str() == "char" && b_type.str() == "char") {
                assembly += "lshi r-13, r-13, 8;\nrshi r-13, r-13, 8;\n";
                return StaticType(BasicType::CHAR);
            } else {
                return StaticType(BasicType::INT);
            }
        }
        case TokenType::MOD: {
            StaticType a_type = visit(node->node_a, env);
            assembly += "mov r-12, r-13;\n";
            StaticType b_type = visit(node->node_b, env);
            assembly += "div r-13, r-12, r-13;\n";
            if(a_type.str() == "char" && b_type.str() == "char") {
                assembly += "lshi r-13, r-13, 8;\nrshi r-13, r-13, 8;\n";
                return StaticType(BasicType::CHAR);
            } else {
                return StaticType(BasicType::INT);
            }
        }
        case TokenType::EQ: {
            if (node->node_a->type() != NodeType::IDENTIFIER) {
                throw std::string(filename + ':' + std::to_string(node->line) + ": cannot assign to " + node->type_str() + " node");
            }
            std::string name = std::dynamic_pointer_cast<IdentifierNode>(node->node_a)->val;
            StaticType b_type = visit(node->node_b, env);
            env->check_type(name, b_type);
            movi_16trit(-11, env->get_addr(name));
            assembly += "st r-13, r-11, 0;\n";
            env->types[name] = b_type;
        return StaticType(BasicType::VOID);
            
        }
        case TokenType::AND: {
            StaticType a_type = visit(node->node_a, env);
            assembly += "mov r-12, r-13;\n";
            StaticType b_type = visit(node->node_b, env);
            assembly += "and r-13, r-12, r-13;\n";
            if(a_type.str() == "char" && b_type.str() == "char") {
                assembly += "lshi r-13, r-13, 8;\n";
                assembly += "rshi r-13, r-13, 8;\n";
                return StaticType(BasicType::CHAR);
            } else {
                return StaticType(BasicType::INT);
            }
        }
        case TokenType::OR: {
            StaticType a_type = visit(node->node_a, env);
            assembly += "mov r-12, r-13;\n";
            StaticType b_type = visit(node->node_b, env);
            assembly += "or r-13, r-12, r-13;\n";
            if(a_type.str() == "char" && b_type.str() == "char") {
                assembly += "lshi r-13, r-13, 8;\n";
                assembly += "rshi r-13, r-13, 8;\n";
                return StaticType(BasicType::CHAR);
            } else {
                return StaticType(BasicType::INT);
            }
        }
        case TokenType::XOR: {
            StaticType a_type = visit(node->node_a, env);
            assembly += "mov r-12, r-13;\n";
            StaticType b_type = visit(node->node_b, env);
            assembly += "xor r-13, r-12, r-13;\n";
            if(a_type.str() == "char" && b_type.str() == "char") {
                assembly += "lshi r-13, r-13, 8;\n";
                assembly += "rshi r-13, r-13, 8;\n";
                return StaticType(BasicType::CHAR);
            } else {
                return StaticType(BasicType::INT);
            }
        }
        case TokenType::EE: {
            visit(node->node_a, env);
            assembly += "mov r-12, r-13;\n";
            visit(node->node_b, env);
            assembly += "cmp r-12, r-13;\nmovi r-13, 1;\nbeq 2;\nmovi r-13, -1;\n";
            return StaticType(BasicType::CHAR);
        }
        case TokenType::NE: {
            visit(node->node_a, env);
            assembly += "mov r-12, r-13;\n";
            visit(node->node_b, env);
            assembly += "cmp r-12, r-13;\nmovi r-13, 1;\nbne 2;\nmovi r-13, -1;\n";
            return StaticType(BasicType::CHAR);
        }
         case TokenType::LT: {
            visit(node->node_a, env);
            assembly += "mov r-12, r-13;\n";
            visit(node->node_b, env);
            assembly += "cmp r-12, r-13;\nmovi r-13, 1;\nblt 2;\nmovi r-13, -1;\n";
            return StaticType(BasicType::CHAR);
        }
        case TokenType::LE: {
            visit(node->node_a, env);
            assembly += "mov r-12, r-13;\n";
            visit(node->node_b, env);
            assembly += "cmp r-12, r-13;\nmovi r-13, 1;\nble 2;\nmovi r-13, -1;\n";
            return StaticType(BasicType::CHAR);
        }
        case TokenType::GT: {
            visit(node->node_a, env);
            assembly += "mov r-12, r-13;\n";
            visit(node->node_b, env);
            assembly += "cmp r-12, r-13;\nmovi r-13, 1;\nbgt 2;\nmovi r-13, -1;\n";
            return StaticType(BasicType::CHAR);
        }
        case TokenType::GE: {
            visit(node->node_a, env);
            assembly += "mov r-12, r-13;\n";
            visit(node->node_b, env);
            assembly += "cmp r-12, r-13;\nmovi r-13, 1;\nbge 2;\nmovi r-13, -1;\n";
            return StaticType(BasicType::CHAR);
        }
        default:
            break;
        }
    }

    StaticType Compiler::visit_var_def_node(const std::shared_ptr<VarDefNode>& node, const std::shared_ptr<Env>& env) {
        if(env->addrs.count(node->name)) {
            throw std::string(filename + ':' + std::to_string(node->line) + ": cannot redefine variable '" + node->name + "'");
        }

        StaticType val_type = visit(node->val, env);
        movi_16trit(-11, var_addr_counter);
        assembly += "st r-13, r-11, 0;\n";
        env->types[node->name] = val_type;
        env->addrs[node->name] = var_addr_counter;
        var_addr_counter += val_type.size();
        return StaticType(BasicType::VOID);
    }

    StaticType Compiler::visit_block_node(const std::shared_ptr<BlockNode>& node, const std::shared_ptr<Env>& env) {
        std::shared_ptr<Env> block_env(new Env({}, {}, env));
        visit(node->stmt_list, block_env);
        return StaticType(BasicType::VOID);
    }

    StaticType Compiler::visit_if_node(const std::shared_ptr<IfNode>& node, const std::shared_ptr<Env>& env) {
        visit(node->cond, env);
        std::string endif_label = "endif" + std::to_string(label_counter);
        label_counter++;
        assembly += "cmpi r-13, -1;\nbne " + endif_label + ";\n";
        visit(node->body, env);
        assembly += endif_label + ":\n";
        return StaticType(BasicType::VOID);
    }

    StaticType Compiler::visit_if_else_node(const std::shared_ptr<IfElseNode>& node, const std::shared_ptr<Env>& env) {
        visit(node->cond, env);
        std::string endif_label = "endif" + std::to_string(label_counter);
        label_counter++;
        assembly += "cmpi r-13, -1;\nbne " + endif_label + ";\n";
        visit(node->if_body, env);
        assembly += endif_label + ":\n";
        visit(node->else_body, env);
        return StaticType(BasicType::VOID);
    }

    StaticType Compiler::visit_while_node(const std::shared_ptr<WhileNode>& node, const std::shared_ptr<Env>& env) {
        std::string while_label = "while" + std::to_string(label_counter);
        label_counter++;
        assembly += while_label + ":\n";
        visit(node->body, env);
        visit(node->cond, env);
        assembly += "\ncmpi r-13, -1;\nbne " + while_label + ";\n";
        return StaticType(BasicType::VOID);
    }

    StaticType Compiler::visit_stmt_list_node(const std::shared_ptr<StmtListNode>& node, const std::shared_ptr<Env>& env) {
        for (int i = 0; i < node->stmts.size(); i++) {
            visit(node->stmts.at(i), env);
        }

        return StaticType(BasicType::VOID);
    }
} // namespace anthill