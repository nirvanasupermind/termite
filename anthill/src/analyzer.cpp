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

   std::shared_ptr<StaticType> Analyzer::visit(const std::shared_ptr<Node>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
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

   std::shared_ptr<StaticType> Analyzer::visit_char_node(const std::shared_ptr<CharNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::CHAR));
   }

   std::shared_ptr<StaticType> Analyzer::visit_int_node(const std::shared_ptr<IntNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::INT));
   }

   std::shared_ptr<StaticType> Analyzer::visit_str_node(const std::shared_ptr<StrNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      return  std::make_shared<NonFuncType>(NonFuncType(BasicType::CHAR, 1));
   }

   std::shared_ptr<StaticType> Analyzer::visit_ident_node(const std::shared_ptr<IdentNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      return symbol_table->get(node->tok.val);
   }

   std::shared_ptr<StaticType> Analyzer::visit_call_node(const std::shared_ptr<CallNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      std::shared_ptr<StaticType> callee_type = visit(node->callee, symbol_table);
      if (!callee_type->is_func()) {
         error(file, node->callee->line, "cannot call a non-function");
      }
      return std::static_pointer_cast<FuncType>(callee_type)->return_type;
   }

   std::shared_ptr<StaticType> Analyzer::visit_postfix_node(const std::shared_ptr<PostfixNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      std::shared_ptr<StaticType> node_type = visit(node->node, symbol_table);

      if (node_type->to_str() == "void") {
         error(file, node->node->line, "cannot perform postfix unary operations on a value of type void");
      }

      return node_type;
   }

   std::shared_ptr<StaticType> Analyzer::visit_prefix_node(const std::shared_ptr<PrefixNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      std::shared_ptr<StaticType> node_type = visit(node->node, symbol_table);

      if (node_type->to_str() == "void") {
         error(file, node->node->line, "cannot perform prefix unary operations on a value of type void");
      }

      return node_type;
   }


   std::shared_ptr<StaticType> Analyzer::visit_bin_op_node(const std::shared_ptr<BinOpNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      std::shared_ptr<StaticType> left_type = visit(node->left_node, symbol_table);
      std::shared_ptr<StaticType> right_type = visit(node->right_node, symbol_table);

      if (left_type->to_str() == "void") {
         error(file, node->left_node->line, "cannot perform binary operations on a value of type void");
      }

      if (right_type->to_str() == "void") {
         error(file, node->right_node->line, "cannot perform binary operations on a value of type void");
      }

      if (left_type->to_str() == "char" && right_type->to_str() == "char") {
         return left_type;
      }
      else if (left_type->to_str() == "char") {
         return right_type;
      }
      else {
         return left_type;
      }
   }

   std::shared_ptr<StaticType> Analyzer::visit_assign_node(const std::shared_ptr<AssignNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      if (node->left_node->get_type() != NodeType::IDENT) {
         error(file, node->left_node->line, "cannot assign to non-identifier");
      }

      return visit(node->left_node, symbol_table);
   }

   std::shared_ptr<StaticType> Analyzer::visit_var_def_node(const std::shared_ptr<VarDefNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      if (node->name.val == "void") {
         error(file, node->name.line, "cannot define variable of type void");
      }
      symbol_table->def(node->name.val, visit(node->val, symbol_table));
      return  std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));;
   }

   std::shared_ptr<StaticType> Analyzer::visit_block_node(const std::shared_ptr<BlockNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      std::shared_ptr<SymbolTable> block_symbol_table = std::make_shared<SymbolTable>(SymbolTable(symbol_table));
      visit(node->stmt_list, block_symbol_table);
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }

   std::shared_ptr<StaticType> Analyzer::visit_if_node(const std::shared_ptr<IfNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      visit(node->cond, symbol_table);
      visit(node->body, symbol_table);
      visit(node->else_body, symbol_table);
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }

   std::shared_ptr<StaticType> Analyzer::visit_while_node(const std::shared_ptr<WhileNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      visit(node->cond, symbol_table);
      visit(node->body, symbol_table);
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }

   std::shared_ptr<StaticType> Analyzer::visit_for_node(const std::shared_ptr<ForNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      visit(node->init, symbol_table);
      visit(node->cond, symbol_table);
      visit(node->update, symbol_table);
      visit(node->body, symbol_table);
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }

   std::shared_ptr<StaticType> Analyzer::visit_continue_node(const std::shared_ptr<ContinueNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }

   std::shared_ptr<StaticType> Analyzer::visit_break_node(const std::shared_ptr<BreakNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }


   std::shared_ptr<StaticType> Analyzer::visit_func_def_node(const std::shared_ptr<FuncDefNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      std::shared_ptr<SymbolTable> func_symbol_table = std::make_shared<SymbolTable>(SymbolTable(symbol_table));  
      std::shared_ptr<TypeNode> return_type_node = std::static_pointer_cast<TypeNode>(node->return_type);
      std::shared_ptr<NonFuncType> return_type = std::make_shared<NonFuncType>(str_to_basic_type(return_type_node->base_type.val), return_type_node->num_pointers);
      std::vector<std::shared_ptr<NonFuncType> > arg_static_types;
      for(int i = 0; i < node->arg_names.size(); i++) {
         std::shared_ptr<TypeNode> type_node = std::static_pointer_cast<TypeNode>(node->arg_types.at(i));
         std::shared_ptr<NonFuncType> type = std::make_shared<NonFuncType>(NonFuncType(str_to_basic_type(type_node->base_type.val), type_node->num_pointers));
         arg_static_types.push_back(type);
         func_symbol_table->def(node->arg_names.at(i).val, type);
      }
      std::shared_ptr<StaticType> func_type = std::make_shared<FuncType>(FuncType(return_type, arg_static_types));
      symbol_table->def(node->name.val, func_type);
      visit(node->body, func_symbol_table);
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }

}
