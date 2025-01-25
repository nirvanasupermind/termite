#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include "token.h"
#include "node.h"
#include "func.h"
#include "env.h"
#include "compiler.h"

namespace anthill {
    Compiler::Compiler(const std::string& filename)
        : filename(filename) {
    }


    StaticType Compiler::visit(const std::shared_ptr<Node>& node, const std::shared_ptr<Env>& env) {
        switch (node->type()) {
        case NodeType::INT:
            return visit_int_node(std::dynamic_pointer_cast<IntNode>(node), env);
        case NodeType::CHAR:
            return visit_char_node(std::dynamic_pointer_cast<CharNode>(node), env);
        // case NodeType::STRING:
        //     return visit_string_node(std::dynamic_pointer_cast<StringNode>(node), env);
        case NodeType::IDENTIFIER:
            return visit_identifier_node(std::dynamic_pointer_cast<IdentifierNode>(node), env);
        case NodeType::CAST:
            return visit_cast_node(std::dynamic_pointer_cast<CastNode>(node), env);
        case NodeType::CALL:
            return visit_call_node(std::dynamic_pointer_cast<CallNode>(node), env);
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
        case NodeType::FOR:
            return visit_for_node(std::dynamic_pointer_cast<ForNode>(node), env);
        case NodeType::FUNC_DEF:
            return visit_func_def_node(std::dynamic_pointer_cast<FuncDefNode>(node), env);
        case NodeType::RETURN:
            return visit_return_node(std::dynamic_pointer_cast<ReturnNode>(node), env);
        case NodeType::PRINT:
            return visit_print_node(std::dynamic_pointer_cast<PrintNode>(node), env);
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
            movi_16trit(reg, high_10_trits);
            assembly += "lshi r" + reg_str + ", r" + reg_str + ", 6;\n";
            assembly += "addi r" + reg_str + ", r" + reg_str + ", " + std::to_string(low_6_trits) + ";\n";
        }
        else {
            assembly += "movi r" + reg_str + ", " + std::to_string(val) + ";\n";
        }
    }


    StaticType Compiler::parse_type(const std::shared_ptr<Node>& node) {
        if (node->type() == NodeType::POINTER_TYPE) {
            StaticType type = parse_type(std::dynamic_pointer_cast<PointerTypeNode>(node)->base_type);
            return StaticType(type.basic_type, type.pointer_levels + 1);
        }
        else {
            std::string name = std::dynamic_pointer_cast<IdentifierNode>(node)->val;
            if (name == "void") {
                return StaticType(BasicType::VOID);
            }
            else if (name == "int") {
                return StaticType(BasicType::INT);
            }
            else if (name == "char") {
                return StaticType(BasicType::CHAR);
            }
            else {
                throw std::string(filename + ':' + std::to_string(node->line) + ": unknown type " + name);
            }
        }
    }

    StaticType Compiler::visit_int_node(const std::shared_ptr<IntNode>& node, const std::shared_ptr<Env>& env) {
        movi_16trit(-13, node->val);
        return StaticType(BasicType::INT);
    }


    StaticType Compiler::visit_char_node(const std::shared_ptr<CharNode>& node, const std::shared_ptr<Env>& env) {
        assembly += "movi r-13, " + std::to_string((int)node->val) + ";\n";
        return StaticType(BasicType::CHAR);
    }


    StaticType Compiler::visit_identifier_node(const std::shared_ptr<IdentifierNode>& node, const std::shared_ptr<Env>& env) {
        try {
            StaticType type = env->get_type(node->val);
            int32_t offset = env->get_offset(node->val);
            // std::cout << "line 104" << node->val << ' ' << addr << '\n';
            assembly += "ld r-13, r-9, " + std::to_string(-offset) + ";\n";
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



    StaticType Compiler::visit_cast_node(const std::shared_ptr<CastNode>& node, const std::shared_ptr<Env>& env) {
        StaticType src_type = visit(node->val, env);
        StaticType cast_type = parse_type(node->cast_type);
        if (src_type.str() != "char" && cast_type.str() == "char") {
            assembly += "lshi r-13, r-13, 8;\nrshi r-13, r-13, 8;\n";
        }
        return cast_type;
    }

    StaticType Compiler::visit_call_node(const std::shared_ptr<CallNode>& node, const std::shared_ptr<Env>& env) {
        for (int i = 0; i < node->args.size(); i++) {
            visit(node->args.at(i), env);
            assembly += "mov r" + std::to_string(i - 8) + ", r-13;\n";
        }

        if (node->func->type() == NodeType::IDENTIFIER) {
            std::shared_ptr<IdentifierNode> identifier_node = std::static_pointer_cast<IdentifierNode>(node->func);
            return env->funcs.at(identifier_node->val).return_type;
        }
        else {
            return StaticType(BasicType::VOID);
        }
    }




    StaticType Compiler::visit_unary_op_node(const std::shared_ptr<UnaryOpNode>& node, const std::shared_ptr<Env>& env) {
        switch (node->op.type) {
        case TokenType::PLUS: {
            StaticType type = visit(node->node, env);
            return type;
        }
        case TokenType::MINUS: {
            StaticType type = visit(node->node, env);
            assembly += "muli r-13, r-13, -1;\n";
            return type;
        }
        case TokenType::MUL: {
            StaticType type = visit(node->node, env);
            // if (type.pointer_levels == 0) {
            //     throw std::string(filename + ':' + std::to_string(node->line) + ": type '" + type.str() + " is not a pointer");
            // }
            assembly += "ld r-13, r-13, 0;\n";
            return StaticType(BasicType::INT);
        }
        case TokenType::AND: {
            if (node->node->type() != NodeType::IDENTIFIER) {
                throw std::string(filename + ':' + std::to_string(node->line) + ": cannot assign to " + node->type_str() + " node");
            }
            std::string name = std::dynamic_pointer_cast<IdentifierNode>(node->node)->val;
            assembly += "sub r-13, r-9, " + std::to_string(env->get_offset(name)) + ";\n";
            // movi_16trit(-13, env->get_addr(name));
            return StaticType(env->get_type(name).basic_type, env->get_type(name).pointer_levels + 1);
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
            if (a_type.str() == "char" && b_type.str() == "char") {
                assembly += "lshi r-13, r-13, 8;\nrshi r-13, r-13, 8;\n";
                return StaticType(BasicType::CHAR);
            }
            else {
                return StaticType(BasicType::INT);
            }
        }
        case TokenType::MINUS: {
            StaticType a_type = visit(node->node_a, env);
            assembly += "mov r-12, r-13;\n";
            StaticType b_type = visit(node->node_b, env);
            assembly += "sub r-13, r-12, r-13;\n";
            if (a_type.str() == "char" && b_type.str() == "char") {
                assembly += "lshi r-13, r-13, 8;\nrshi r-13, r-13, 8;\n";
                return StaticType(BasicType::CHAR);
            }
            else {
                return StaticType(BasicType::INT);
            }
        }
        case TokenType::MUL: {
            StaticType a_type = visit(node->node_a, env);
            assembly += "mov r-12, r-13;\n";
            StaticType b_type = visit(node->node_b, env);
            assembly += "mul r-13, r-12, r-13;\n";
            if (a_type.str() == "char" && b_type.str() == "char") {
                assembly += "lshi r-13, r-13, 8;\nrshi r-13, r-13, 8;\n";
                return StaticType(BasicType::CHAR);
            }
            else {
                return StaticType(BasicType::INT);
            }
        }
        case TokenType::DIV: {
            StaticType a_type = visit(node->node_a, env);
            assembly += "mov r-12, r-13;\n";
            StaticType b_type = visit(node->node_b, env);
            assembly += "div r-13, r-12, r-13;\n";
            if (a_type.str() == "char" && b_type.str() == "char") {
                assembly += "lshi r-13, r-13, 8;\nrshi r-13, r-13, 8;\n";
                return StaticType(BasicType::CHAR);
            }
            else {
                return StaticType(BasicType::INT);
            }
        }
        case TokenType::MOD: {
            StaticType a_type = visit(node->node_a, env);
            assembly += "mov r-12, r-13;\n";
            StaticType b_type = visit(node->node_b, env);
            assembly += "div r-13, r-12, r-13;\n";
            if (a_type.str() == "char" && b_type.str() == "char") {
                assembly += "lshi r-13, r-13, 8;\nrshi r-13, r-13, 8;\n";
                return StaticType(BasicType::CHAR);
            }
            else {
                return StaticType(BasicType::INT);
            }
        }
        case TokenType::EQ: {
            if (node->node_a->type() == NodeType::UNARY_OP) {
                std::shared_ptr<UnaryOpNode> unary_op_node = std::dynamic_pointer_cast<UnaryOpNode>(node->node_a);
                if (unary_op_node->op.type != TokenType::MUL) {
                    throw std::string(filename + ':' + std::to_string(node->line) + ": cannot assign to UNARY_OP node with operator "
                        + unary_op_node->op.str());
                }
                visit(unary_op_node->node, env);
                assembly += "mov r-10, r-13;\n";
                visit(node->node_b, env);
                assembly += "st r-13, r-10, 0;\n";
                return StaticType(BasicType::VOID);
            }
            else {
                if (node->node_a->type() != NodeType::IDENTIFIER) {
                    throw std::string(filename + ':' + std::to_string(node->line) + ": cannot assign to " + node->type_str() + " node");
                }
                std::string name = std::dynamic_pointer_cast<IdentifierNode>(node->node_a)->val;
                StaticType b_type = visit(node->node_b, env);
                // env->check_type(name, b_type);
                assembly += "st r-13, r-9, " + std::to_string(env->get_offset(name)) + ";\n";
                env->var_types[name] = b_type;
                return StaticType(BasicType::VOID);
            }

        }
        case TokenType::AND: {
            StaticType a_type = visit(node->node_a, env);
            assembly += "mov r-12, r-13;\n";
            StaticType b_type = visit(node->node_b, env);
            assembly += "and r-13, r-12, r-13;\n";
            if (a_type.str() == "char" && b_type.str() == "char") {
                assembly += "lshi r-13, r-13, 8;\n";
                assembly += "rshi r-13, r-13, 8;\n";
                return StaticType(BasicType::CHAR);
            }
            else {
                return StaticType(BasicType::INT);
            }
        }
        case TokenType::OR: {
            StaticType a_type = visit(node->node_a, env);
            assembly += "mov r-12, r-13;\n";
            StaticType b_type = visit(node->node_b, env);
            assembly += "or r-13, r-12, r-13;\n";
            if (a_type.str() == "char" && b_type.str() == "char") {
                assembly += "lshi r-13, r-13, 8;\n";
                assembly += "rshi r-13, r-13, 8;\n";
                return StaticType(BasicType::CHAR);
            }
            else {
                return StaticType(BasicType::INT);
            }
        }
        case TokenType::XOR: {
            StaticType a_type = visit(node->node_a, env);
            assembly += "mov r-12, r-13;\n";
            StaticType b_type = visit(node->node_b, env);
            assembly += "xor r-13, r-12, r-13;\n";
            if (a_type.str() == "char" && b_type.str() == "char") {
                assembly += "lshi r-13, r-13, 8;\n";
                assembly += "rshi r-13, r-13, 8;\n";
                return StaticType(BasicType::CHAR);
            }
            else {
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
        if (env->var_types.count(node->name)) {
            throw std::string(filename + ':' + std::to_string(node->line) + ": cannot redefine variable '" + node->name + "'");
        }
        StaticType val_type = visit(node->val, env);
        assembly += "st r-13, r-9, -" + std::to_string(env->parent_func->var_counter) + ";\n";
        env->var_types[node->name] = val_type;
        env->parent_func->var_counter += val_type.size();
        // std::cout << val_type.str() << '\n';
        // std::cout << parse_type(node->var_type).str() << '\n';
        // StaticType parsed_var_type = parse_type(node->var_type);
        // if(!env->check_type(node->name, parsed_var_type)) {
        //     throw std::string(filename + ':' + std::to_string(node->line) + ": cannot convert " + val_type.str() + " to " + parsed_var_type.str());
        // }
        return StaticType(BasicType::VOID);
    }

    StaticType Compiler::visit_block_node(const std::shared_ptr<BlockNode>& node, const std::shared_ptr<Env>& env) {
        std::shared_ptr<Env> block_env(new Env(env, env->parent_func));
        visit(node->stmt_list, block_env);
        return StaticType(BasicType::VOID);
    }

    StaticType Compiler::visit_if_node(const std::shared_ptr<IfNode>& node, const std::shared_ptr<Env>& env) {
        visit(node->cond, env);
        std::string endif_label = "_endif" + std::to_string(label_counter);
        label_counter++;
        assembly += "cmpi r-13, -1;\nbeq ";
        size_t old_assembly_size = assembly.size();
        visit(node->body, env);
        size_t new_assembly_size = assembly.size();
        int branch_count = 0;
        for (int i = old_assembly_size; i < new_assembly_size; i++) {
            if (assembly.at(i) == ';') {
                branch_count++;
            }
        }
        assembly = assembly.substr(0, old_assembly_size) + std::to_string(branch_count * 2) + ";\n" + assembly.substr(old_assembly_size, new_assembly_size);
        return StaticType(BasicType::VOID);
    }

    StaticType Compiler::visit_if_else_node(const std::shared_ptr<IfElseNode>& node, const std::shared_ptr<Env>& env) {
        visit(node->cond, env);
        std::string endif_label = "_endif" + std::to_string(label_counter);
        label_counter++;
        assembly += "cmpi r-13, -1;\nbeq ";
        size_t old_assembly_size = assembly.size();
        visit(node->if_body, env);
        size_t new_assembly_size = assembly.size();
        int branch_count = 0;
        for (int i = old_assembly_size; i < new_assembly_size; i++) {
            if (assembly.at(i) == ';') {
                branch_count++;
            }
        }
        assembly = assembly.substr(0, old_assembly_size) + std::to_string(branch_count * 2) + ";\n" + assembly.substr(old_assembly_size, new_assembly_size);
        assembly += endif_label + ":\n";
        visit(node->else_body, env);
        return StaticType(BasicType::VOID);
    }

    StaticType Compiler::visit_while_node(const std::shared_ptr<WhileNode>& node, const std::shared_ptr<Env>& env) {
        std::string while_label = "_while" + std::to_string(label_counter);
        label_counter++;
        assembly += "mov r-11, r-13;\n" + while_label + ":\nmov r-13, r-11;\n";
        visit(node->body, env);
        assembly += "mov r-11, r-13;\n";
        visit(node->cond, env);
        assembly += "cmpi r-13, -1;\nbne " + while_label + ";\nmov r-13, r-11;\n";
        return StaticType(BasicType::VOID);
    }


    StaticType Compiler::visit_for_node(const std::shared_ptr<ForNode>& node, const std::shared_ptr<Env>& env) {
        std::string for_label = "_for" + std::to_string(label_counter);
        label_counter++;
        visit(node->init, env);
        assembly += "mov r-11, r-13;\n" + for_label + ":\nmov r-13, r-11;\n";
        visit(node->body, env);
        assembly += "mov r-11, r-13;\n";
        visit(node->update, env);
        visit(node->cond, env);
        assembly += "cmpi r-13, -1;\nbne " + for_label + ";\nmov r-13, r-11;\n";
        return StaticType(BasicType::VOID);
    }


    StaticType Compiler::visit_func_def_node(const std::shared_ptr<FuncDefNode>& node, const std::shared_ptr<Env>& env) {
        assembly += node->name + ":\n";
        StaticType return_type = parse_type(node->return_type);
        std::vector<StaticType> arg_types;
        for (int i = 0; i < node->arg_types.size(); i++) {
            arg_types.push_back(parse_type(node->arg_types.at(i)));
        }
        Func func(return_type, arg_types);
        assembly += "push r-9;\n";
        assembly += "mov r-9, r12;\n";
        assembly += "subi r12, r12, 81;\n";
        std::shared_ptr<Env> func_env = std::make_shared<Env>(env, std::make_shared<Func>(func));

        for (int i = 0; i < node->arg_names.size(); i++) {
            if (func_env->var_types.count(node->name)) {
                throw std::string(filename + ':' + std::to_string(node->line) + ": cannot redefine variable '" + node->name + "'");
            }
            StaticType val_type = arg_types.at(i);
            assembly += "st r" + std::to_string(i - 8) + ", r-9, -" + std::to_string(env->parent_func->var_counter) + ";\n";
            func_env->var_types[node->name] = val_type;
            func.var_counter += val_type.size();
        }

        assembly += "addi r12, r12, 81;\n";
        assembly += "pop r-9;\n";
        assembly += "ret;\n";
        return StaticType(BasicType::VOID);
    }


    StaticType Compiler::visit_return_node(const std::shared_ptr<ReturnNode>& node, const std::shared_ptr<Env>& env) {
        visit(node->val, env);
        if (main_flag) {
            assembly += "sys 0;\n";
        }
        else {
            assembly += "ret;\n";
        }
        return StaticType(BasicType::VOID);
    }

    StaticType Compiler::visit_print_node(const std::shared_ptr<PrintNode>& node, const std::shared_ptr<Env>& env) {
        visit(node->val, env);
        assembly += "sys 1;\n";
        return StaticType(BasicType::VOID);
    }

    StaticType Compiler::visit_stmt_list_node(const std::shared_ptr<StmtListNode>& node, const std::shared_ptr<Env>& env) {
        for (int i = 0; i < node->stmts.size(); i++) {
            visit(node->stmts.at(i), env);
        }

        return StaticType(BasicType::VOID);
    }

}