#ifndef ANALYZER_H
#define ANALYZER_H

#include <string>
#include <memory>
#include "static_type.h"
#include "symbol_table.h"
#include "node.h"

namespace anthill {
    class Analyzer {
    public:
        std::string file;
        Analyzer(const std::string& file);
        std::shared_ptr<StaticType> visit(const std::shared_ptr<Node>& node, const std::shared_ptr<SymbolTable> symbol_table);
        std::shared_ptr<StaticType> visit_char_node(const std::shared_ptr<CharNode>& node, const std::shared_ptr<SymbolTable> symbol_table);
        std::shared_ptr<StaticType> visit_int_node(const std::shared_ptr<IntNode>& node, const std::shared_ptr<SymbolTable> symbol_table);
        std::shared_ptr<StaticType> visit_str_node(const std::shared_ptr<StrNode>& node, const std::shared_ptr<SymbolTable> symbol_table);
        std::shared_ptr<StaticType> visit_ident_node(const std::shared_ptr<IdentNode>& node, const std::shared_ptr<SymbolTable> symbol_table);
        std::shared_ptr<StaticType> visit_call_node(const std::shared_ptr<CallNode>& node, const std::shared_ptr<SymbolTable> symbol_table);
        std::shared_ptr<StaticType> visit_postfix_node(const std::shared_ptr<PostfixNode>& node, const std::shared_ptr<SymbolTable> symbol_table);
        std::shared_ptr<StaticType> visit_prefix_node(const std::shared_ptr<PrefixNode>& node, const std::shared_ptr<SymbolTable> symbol_table);
        std::shared_ptr<StaticType> visit_bin_op_node(const std::shared_ptr<BinOpNode>& node, const std::shared_ptr<SymbolTable> symbol_table);
        std::shared_ptr<StaticType> visit_assign_node(const std::shared_ptr<AssignNode>& node, const std::shared_ptr<SymbolTable> symbol_table);
        std::shared_ptr<StaticType> visit_var_def_node(const std::shared_ptr<VarDefNode>& node, const std::shared_ptr<SymbolTable> symbol_table);
        std::shared_ptr<StaticType> visit_block_node(const std::shared_ptr<BlockNode>& node, const std::shared_ptr<SymbolTable> symbol_table);
        std::shared_ptr<StaticType> visit_if_node(const std::shared_ptr<IfNode>& node, const std::shared_ptr<SymbolTable> symbol_table);
        std::shared_ptr<StaticType> visit_while_node(const std::shared_ptr<WhileNode>& node, const std::shared_ptr<SymbolTable> symbol_table);
        std::shared_ptr<StaticType> visit_for_node(const std::shared_ptr<ForNode>& node, const std::shared_ptr<SymbolTable> symbol_table);
        std::shared_ptr<StaticType> visit_continue_node(const std::shared_ptr<ContinueNode>& node, const std::shared_ptr<SymbolTable> symbol_table);
        std::shared_ptr<StaticType> visit_break_node(const std::shared_ptr<BreakNode>& node, const std::shared_ptr<SymbolTable> symbol_table);
        std::shared_ptr<StaticType> visit_func_def_node(const std::shared_ptr<FuncDefNode>& node, const std::shared_ptr<SymbolTable> symbol_table);
        std::shared_ptr<StaticType> visit_return_node(const std::shared_ptr<ReturnNode>& node, const std::shared_ptr<SymbolTable> symbol_table);
        std::shared_ptr<StaticType> visit_enum_node(const std::shared_ptr<EnumNode>& node, const std::shared_ptr<SymbolTable> symbol_table);
        std::shared_ptr<StaticType> visit_stmt_list_node(const std::shared_ptr<StmtListNode>& node, const std::shared_ptr<SymbolTable> symbol_table);

    };
}

#endif