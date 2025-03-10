#include <string>
#include <memory>
#include <vector>
#include "static_type.h"
#include "symbol_table.h"
#include "token.h"
#include "node.h"
#include "error.h"
#include "analyzer.h"

namespace anthill {
   Analyzer::Analyzer(const std::string& file)
      : file(file) {

   }

   std::shared_ptr<StaticType> Analyzer::visit(const std::shared_ptr<Node>& node, const std::shared_ptr<SymbolTable> symbol_table) {
      switch (node->get_type()) {
      case NodeType::CHAR:
         return visit_char_node(std::static_pointer_cast<CharNode>(node), symbol_table);
      case NodeType::INT:
         return visit_int_node(std::static_pointer_cast<IntNode>(node), symbol_table);

         case NodeType::STR:
         return visit_str_node(std::static_pointer_cast<StrNode>(node), symbol_table);
         case NodeType::IDENT:
         return visit_ident_node(std::static_pointer_cast<IdentNode>(node), symbol_table);
         case NodeType::CALL:
         return visit_call_node(std::static_pointer_cast<CallNode>(node), symbol_table);
         case NodeType::POSTFIX:
         return visit_postfix_node(std::static_pointer_cast<PostfixNode>(node), symbol_table);
      }
   }

   std::shared_ptr<StaticType> Analyzer::visit_char_node(const std::shared_ptr<CharNode>& node, const std::shared_ptr<SymbolTable> symbol_table) {
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::CHAR));
   }

   std::shared_ptr<StaticType> Analyzer::visit_int_node(const std::shared_ptr<IntNode>& node, const std::shared_ptr<SymbolTable> symbol_table) {
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::INT));
   }

   std::shared_ptr<StaticType> Analyzer::visit_str_node(const std::shared_ptr<StrNode>& node, const std::shared_ptr<SymbolTable> symbol_table) {
      return  std::make_shared<NonFuncType>(NonFuncType(BasicType::CHAR, 1));
   }

   std::shared_ptr<StaticType> Analyzer::visit_ident_node(const std::shared_ptr<IdentNode>& node, const std::shared_ptr<SymbolTable> symbol_table) {
      return symbol_table->get(node->tok.val);
   }

   std::shared_ptr<StaticType> Analyzer::visit_call_node(const std::shared_ptr<CallNode>& node, const std::shared_ptr<SymbolTable> symbol_table) {
      std::shared_ptr<StaticType> callee_type = visit(node->callee, symbol_table);
      if (!callee_type->is_func()) {
         error(file, node->callee->line, "cannot call a non-function");
      }
      return std::static_pointer_cast<FuncType>(callee_type)->return_type;
   }

   std::shared_ptr<StaticType> Analyzer::visit_postfix_node(const std::shared_ptr<PostfixNode>& node, const std::shared_ptr<SymbolTable> symbol_table) {
      std::shared_ptr<StaticType> node_type = visit(node->node, symbol_table);
      if(node_type->is_func()) {
         error(file, node->node->line, "cannot perform postfix unary operations on a function");   
      }

      if(node_type->to_str() == "void") {
         error(file, node->node->line, "cannot perform postfix unary operations on a value of type void");
      }

      return node_type;
   }

}
