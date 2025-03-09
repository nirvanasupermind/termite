#include "analyzer.h"
namespace anthill {
    StaticType Analyzer::visit(const std::shared_ptr<Node>& node, const std::shared_ptr<SymbolTable> symbol_table) {
        switch(node->get_type()) {
            case NodeType::CHAR:
                return visit_char_node(std::static_pointer_cast<CharNode>(node), symbol_table);
                case NodeType::INT:
                return visit_int_node(std::static_pointer_cast<IntNode>(node), symbol_table);
        }
    }

    StaticType Analyzer::visit_char_node(const std::shared_ptr<CharNode>& node, const std::shared_ptr<SymbolTable> symbol_table) {
       return StaticType(BasicType::CHAR);
    }

    StaticType Analyzer::visit_int_node(const std::shared_ptr<IntNode>& node, const std::shared_ptr<SymbolTable> symbol_table) {
        return StaticType(BasicType::INT);
     }

     StaticType Analyzer::visit_str_node(const std::shared_ptr<StrNode>& node, const std::shared_ptr<SymbolTable> symbol_table) {
        return StaticType(BasicType::CHAR, 1);
     }
 
     StaticType Analyzer::visit_ident_node(const std::shared_ptr<IdentNode>& node, const std::shared_ptr<SymbolTable> symbol_table) {
        return symbol_table->get(node->tok.val);
     }
     
     StaticType Analyzer::visit_call_node(const std::shared_ptr<CallNode>& node, const std::shared_ptr<SymbolTable> symbol_table) {
        return visit(node->callee);
     }

}
