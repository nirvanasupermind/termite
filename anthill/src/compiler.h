#ifndef COMPILER_H
#define COMPILER_H

#include <cinttypes>
#include <memory>
#include <string>

#include "node.h"
#include "env.h"

namespace anthill {
    const int32_t MOVI_LIMIT = 9841;
    class Compiler {
    public:
        std::string filename;
        std::string assembly;
        int32_t var_addr_counter;
        int32_t label_counter;
        Compiler(const std::string& filename);
        void movi_16trit(int8_t reg, int32_t val);
        StaticType parse_type(const std::shared_ptr<Node>& node);
        StaticType visit(const std::shared_ptr<Node>& node,  const std::shared_ptr<Env>& env);
        StaticType visit_int_node(const std::shared_ptr<IntNode>& node, const std::shared_ptr<Env>& env);
        StaticType visit_char_node(const std::shared_ptr<CharNode>& node, const std::shared_ptr<Env>& env);
        StaticType visit_string_node(const std::shared_ptr<StringNode>& node, const std::shared_ptr<Env>& env);
        StaticType visit_identifier_node(const std::shared_ptr<IdentifierNode>& node, const std::shared_ptr<Env>& env);
        StaticType visit_cast_node(const std::shared_ptr<CastNode>& node, const std::shared_ptr<Env>& env);
        StaticType visit_call_node(const std::shared_ptr<CallNode>& node, const std::shared_ptr<Env>& env);
        StaticType visit_unary_op_node(const std::shared_ptr<UnaryOpNode>& node, const std::shared_ptr<Env>& env);
        StaticType visit_binary_op_node(const std::shared_ptr<BinaryOpNode>& node, const std::shared_ptr<Env>& env);
        StaticType visit_var_def_node(const std::shared_ptr<VarDefNode>& node, const std::shared_ptr<Env>& env);
        StaticType visit_block_node(const std::shared_ptr<BlockNode>& node, const std::shared_ptr<Env>& env);
        StaticType visit_if_node(const std::shared_ptr<IfNode>& node, const std::shared_ptr<Env>& env);
        StaticType visit_if_else_node(const std::shared_ptr<IfElseNode>& node, const std::shared_ptr<Env>& env);
        StaticType visit_while_node(const std::shared_ptr<WhileNode>& node, const std::shared_ptr<Env>& env);
        StaticType visit_for_node(const std::shared_ptr<ForNode>& node, const std::shared_ptr<Env>& env);
        StaticType visit_func_def_node(const std::shared_ptr<FuncDefNode>& node, const std::shared_ptr<Env>& env);
        StaticType visit_return_node(const std::shared_ptr<ReturnNode>& node, const std::shared_ptr<Env>& env);
        StaticType visit_print_node(const std::shared_ptr<PrintNode>& node, const std::shared_ptr<Env>& env);
        StaticType visit_stmt_list_node(const std::shared_ptr<StmtListNode>& node, const std::shared_ptr<Env>& env);
        StaticType visit_node(const std::shared_ptr<BlockNode>& node, const std::shared_ptr<Env>& env);

    };

} // namespace anthill

#endif // PARSER_H