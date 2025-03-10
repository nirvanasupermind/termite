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
        std::shared_ptr<StaticType> visit_postfix_node(const std::shared_ptr<PostfixNode>&node, const std::shared_ptr<SymbolTable> symbol_table);
    };
}

#endif