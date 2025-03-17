#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include "static_type.h"
#include "symbol_table.h"
#include "token.h"
#include "node.h"
#include "error.h"
#include "generator.h"

namespace anthill {
   Generator::Generator(const std::string& file)
      : file(file) {

   }

   int Generator::alloc_label() {
      return label_id++;
   }


   int Generator::alloc_addr() {
      return (addr_counter += 2);
   }

   std::shared_ptr<StaticType> Generator::visit(const std::shared_ptr<Node>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
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
         case NodeType::PREFIX:
         return visit_prefix_node(std::static_pointer_cast<PrefixNode>(node), symbol_table);
         case NodeType::BIN_OP:
         return visit_bin_op_node(std::static_pointer_cast<BinOpNode>(node), symbol_table);
         case NodeType::ASSIGN:
         return visit_assign_node(std::static_pointer_cast<AssignNode>(node), symbol_table);
         case NodeType::VAR_DEF:
         return visit_var_def_node(std::static_pointer_cast<VarDefNode>(node), symbol_table);
         case NodeType::BLOCK:
         return visit_block_node(std::static_pointer_cast<BlockNode>(node), symbol_table);
         case NodeType::IF:
         return visit_if_node(std::static_pointer_cast<IfNode>(node), symbol_table);
         case NodeType::WHILE: {
         return visit_while_node(std::static_pointer_cast<WhileNode>(node), symbol_table);
         }
         case NodeType::FOR:
         return visit_for_node(std::static_pointer_cast<ForNode>(node), symbol_table);
         case NodeType::CONTINUE:
         return visit_continue_node(std::static_pointer_cast<ContinueNode>(node), symbol_table);
         case NodeType::BREAK:
         return visit_break_node(std::static_pointer_cast<BreakNode>(node), symbol_table);
         case NodeType::FUNC_DEF:
         return visit_func_def_node(std::static_pointer_cast<FuncDefNode>(node), symbol_table);
         case NodeType::RETURN:
         return visit_return_node(std::static_pointer_cast<ReturnNode>(node), symbol_table);
         case NodeType::ENUM:
         return visit_enum_node(std::static_pointer_cast<EnumNode>(node), symbol_table);
         case NodeType::STMT_LIST:
         return visit_stmt_list_node(std::static_pointer_cast<StmtListNode>(node), symbol_table);
      }
   }

   std::shared_ptr<StaticType> Generator::visit_char_node(const std::shared_ptr<CharNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      asm_stream << "mov $" << (int)(node->tok.val.front()) << ",%ax\n";
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::CHAR));
   }

   std::shared_ptr<StaticType> Generator::visit_int_node(const std::shared_ptr<IntNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      asm_stream << "mov $" << std::stoi(node->tok.val) << ",%ax\n";
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::INT));
   }

   std::shared_ptr<StaticType> Generator::visit_str_node(const std::shared_ptr<StrNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      return  std::make_shared<NonFuncType>(NonFuncType(BasicType::CHAR, 1));
   }

   std::shared_ptr<StaticType> Generator::visit_ident_node(const std::shared_ptr<IdentNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      asm_stream << "mov " << symbol_table->get_addr(node->tok.val) << ",%ax\n";
      return symbol_table->get_type(node->tok.val);
   }

   std::shared_ptr<StaticType> Generator::visit_call_node(const std::shared_ptr<CallNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      std::shared_ptr<StaticType> callee_type = visit(node->callee, symbol_table);
      if (!callee_type->is_func()) {
         error(file, node->callee->line, "cannot call a non-function");
      }
      return std::static_pointer_cast<FuncType>(callee_type)->return_type;
   }

   std::shared_ptr<StaticType> Generator::visit_postfix_node(const std::shared_ptr<PostfixNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      std::shared_ptr<StaticType> node_type = visit(node->node, symbol_table);

      if (node_type->to_str() == "void") {
         error(file, node->node->line, "cannot perform postfix unary operations on a value of type void");
      }

      return node_type;
   }

   std::shared_ptr<StaticType> Generator::visit_prefix_node(const std::shared_ptr<PrefixNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      std::shared_ptr<StaticType> node_type = visit(node->node, symbol_table);

      if (node_type->to_str() == "void") {
         error(file, node->node->line, "cannot perform prefix unary operations on a value of type void");
      }

      return node_type;
   }


   std::shared_ptr<StaticType> Generator::visit_bin_op_node(const std::shared_ptr<BinOpNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      std::shared_ptr<StaticType> left_type = visit(node->left_node, symbol_table);
      std::shared_ptr<StaticType> right_type;

      switch (node->op_tok.type) {
         case TokenType::AMPER: {
            asm_stream << "push %ax\n";
            right_type = visit(node->right_node, symbol_table);
            asm_stream << "pop %cx\n";
            asm_stream << "and %cx,%ax\n";
            break;
         }
         case TokenType::PIPE: {
            visit(node->left_node, symbol_table);
            asm_stream << "push %ax\n";
            right_type = visit(node->right_node, symbol_table);
            asm_stream << "pop %cx\n";
            asm_stream << "or %cx,%ax\n";
            break;
         }
         case TokenType::CARET: {
            visit(node->left_node, symbol_table);
            asm_stream << "push %ax\n";
            right_type = visit(node->right_node, symbol_table);
            asm_stream << "pop %cx\n";
            asm_stream << "xor %cx,%ax\n";
            break;
         }
         case TokenType::LSHIFT: {
            visit(node->left_node, symbol_table);
            asm_stream << "push %ax\n";
            right_type = visit(node->right_node, symbol_table);
            asm_stream << "pop %cx\n";
            asm_stream << "mov %ax,%dx\n";
            asm_stream << "mov %cx,%ax\n";
            asm_stream << "mov %dx,%cx\n";
            asm_stream << "shl %cx,%ax\n";
            break;
         }
         case TokenType::RSHIFT: {
            visit(node->left_node, symbol_table);
            asm_stream << "push %ax\n";
            right_type = visit(node->right_node, symbol_table);
            asm_stream << "pop %cx\n";
            asm_stream << "mov %ax,%dx\n";
            asm_stream << "mov %cx,%ax\n";
            asm_stream << "mov %dx,%cx\n";
            asm_stream << "shr %cx,%ax\n";
            break;
         }
         case TokenType::LOGAND: {
            visit(node->left_node, symbol_table);
            asm_stream << "push %ax\n";
            right_type = visit(node->right_node, symbol_table);
            asm_stream << "pop %cx\n";
            asm_stream << "and %cx,%ax\n";
            break;
         }
         case TokenType::PLUS: {
            visit(node->left_node, symbol_table);
            asm_stream << "push %ax\n";
            right_type = visit(node->right_node, symbol_table);
            asm_stream << "pop %cx\n";
            asm_stream << "add %cx,%ax\n";
            break;
         }
         case TokenType::MINUS: {
            visit(node->left_node, symbol_table);
            asm_stream << "push %ax\n";
            right_type = visit(node->right_node, symbol_table);
            asm_stream << "pop %cx\n";
            asm_stream << "mov %ax,%dx\n";
            asm_stream << "mov %cx,%ax\n";
            asm_stream << "mov %dx,%cx\n";
            asm_stream << "sub %cx,%ax\n";
            break;
         }
         case TokenType::STAR: {
            visit(node->left_node, symbol_table);
            asm_stream << "push %ax\n";
            right_type = visit(node->right_node, symbol_table);
            asm_stream << "pop %cx\n";
            asm_stream << "mul %cx,%ax\n";
            break;
         }
         case TokenType::SLASH: {
            visit(node->left_node, symbol_table);
            asm_stream << "push %ax\n";
            right_type = visit(node->right_node, symbol_table);
            asm_stream << "pop %cx\n";
            asm_stream << "mov %ax,%dx\n";
            asm_stream << "mov %cx,%ax\n";
            asm_stream << "mov %dx,%cx\n";
            asm_stream << "div %cx,%ax\n";
            break;
         }
         case TokenType::MOD: {
            visit(node->left_node, symbol_table);
            asm_stream << "push %ax\n";
            right_type = visit(node->right_node, symbol_table);
            asm_stream << "pop %cx\n";
            asm_stream << "mov %ax,%dx\n";
            asm_stream << "mov %cx,%ax\n";
            asm_stream << "mov %dx,%cx\n";
            asm_stream << "mod %cx,%ax\n";
            break;
         }
         case TokenType::EQUAL: {
            visit(node->left_node, symbol_table);
            asm_stream << "push %ax\n";
            right_type = visit(node->right_node, symbol_table);
            asm_stream << "pop %cx\n";
            asm_stream << "cmp %ax,%cx\n";
            asm_stream << "mov $1,%ax\n";
            int label = alloc_label();
            asm_stream << "je _L" + std::to_string(label) + "\n";
            asm_stream << "mov $0,%ax\n";
            asm_stream << "_L" + std::to_string(label) + ":\n";
            break;
         }
         case TokenType::NOTEQ: {
            visit(node->left_node, symbol_table);
            asm_stream << "push %ax\n";
            right_type = visit(node->right_node, symbol_table);
            asm_stream << "pop %cx\n";
            asm_stream << "cmp %ax,%cx\n";
            asm_stream << "mov $1,%ax\n";
            int label = alloc_label();
            asm_stream << "jne _L" + std::to_string(label) + "\n";
            asm_stream << "mov $0,%ax\n";
            asm_stream << "_L" + std::to_string(label) + ":\n";
            break;
         }
         case TokenType::LESS: {
            visit(node->left_node, symbol_table);
            asm_stream << "push %ax\n";
            right_type = visit(node->right_node, symbol_table);
            asm_stream << "pop %cx\n";
            asm_stream << "cmp %ax,%cx\n";
            asm_stream << "mov $1,%ax\n";
            int label = alloc_label();
            asm_stream << "jl _L" + std::to_string(label) + "\n";
            asm_stream << "mov $0,%ax\n";
            asm_stream << "_L" + std::to_string(label) + ":\n";
            break;
         }
         case TokenType::LTEQ: {
            visit(node->left_node, symbol_table);
            asm_stream << "push %ax\n";
            right_type = visit(node->right_node, symbol_table);
            asm_stream << "pop %cx\n";
            asm_stream << "cmp %ax,%cx\n";
            asm_stream << "mov $1,%ax\n";
            int label = alloc_label();
            asm_stream << "jle _L" + std::to_string(label) + "\n";
            asm_stream << "mov $0,%ax\n";
            asm_stream << "_L" + std::to_string(label) + ":\n";
            break;
         }
         case TokenType::GREATER: {
            visit(node->left_node, symbol_table);
            asm_stream << "push %ax\n";
            right_type = visit(node->right_node, symbol_table);
            asm_stream << "pop %cx\n";
            asm_stream << "cmp %ax,%cx\n";
            asm_stream << "mov $1,%ax\n";
            int label = alloc_label();
            asm_stream << "jg _L" + std::to_string(label) + "\n";
            asm_stream << "mov $0,%ax\n";
            asm_stream << "_L" + std::to_string(label) + ":\n";
            break;
         }
         case TokenType::GTEQ: {
            visit(node->left_node, symbol_table);
            asm_stream << "push %ax\n";
            right_type = visit(node->right_node, symbol_table);
            asm_stream << "pop %cx\n";
            asm_stream << "cmp %ax,%cx\n";
            asm_stream << "mov $1,%ax\n";
            int label = alloc_label();
            asm_stream << "jge _L" + std::to_string(label) + "\n";
            asm_stream << "mov $0,%ax\n";
            asm_stream << "_L" + std::to_string(label) + ":\n";
            break;
         }
      }

      
      if (left_type->to_str() == "void") {
         error(file, node->left_node->line, "cannot perform binary operations on a value of type void");
      }

      if (right_type->to_str() == "void") {
         error(file, node->right_node->line, "cannot perform binary operations on a value of type void");
      }

      if (left_type->to_str() == "char" && right_type->to_str() == "char") {
         asm_stream << "and $0n4444, %ax\n";
         return left_type;
      }
      else if (left_type->to_str() == "char") {
         return right_type;
      }
      else {
         return left_type;
      }
   }

   std::shared_ptr<StaticType> Generator::visit_assign_node(const std::shared_ptr<AssignNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      if (node->left_node->get_type() != NodeType::IDENT) {
         error(file, node->left_node->line, "cannot assign to non-identifier");
      }
      int32_t addr = symbol_table->get_addr(std::static_pointer_cast<IdentNode>(node->left_node)->tok.val);
      visit(node->right_node, symbol_table);
      asm_stream << "mov %ax," + std::to_string(addr) + "\n";
      return visit(node->left_node, symbol_table);
   }

   std::shared_ptr<StaticType> Generator::visit_var_def_node(const std::shared_ptr<VarDefNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      if (node->type->to_str() == "void") {
         error(file, node->name.line, "cannot define variable of type void");
      }
      int addr = alloc_addr();
      symbol_table->def_type(node->name.val, visit(node->val, symbol_table));
      symbol_table->def_addr(node->name.val, addr);
      asm_stream << "mov %ax," + std::to_string(addr) + "\n";
      return  std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));;
   }

   std::shared_ptr<StaticType> Generator::visit_block_node(const std::shared_ptr<BlockNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      std::shared_ptr<SymbolTable> block_symbol_table = std::make_shared<SymbolTable>(SymbolTable(symbol_table));
      visit(node->stmt_list, block_symbol_table);
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }

   std::shared_ptr<StaticType> Generator::visit_if_node(const std::shared_ptr<IfNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      int label = alloc_label();
      int label2 = alloc_label();
      visit(node->cond, symbol_table);
      asm_stream << "cmp $1, %ax\n";
      asm_stream << "jne _L" + std::to_string(label) + "\n";
      visit(node->body, symbol_table);
      asm_stream << "jmp _L" + std::to_string(label2) + "\n";
      asm_stream << "_L" + std::to_string(label) + ":\n";
      if(node->else_body) {
         visit(node->else_body, symbol_table);
      }
      asm_stream << "_L" + std::to_string(label2) + ":\n";
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }

   std::shared_ptr<StaticType> Generator::visit_while_node(const std::shared_ptr<WhileNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      int label = alloc_label();
      int label2 = alloc_label();
      asm_stream << "jmp _L" + std::to_string(label2) + "\n";
      asm_stream << "_L" + std::to_string(label) + ":\n";;
      visit(node->body, symbol_table);
      asm_stream << "_L" + std::to_string(label2) + ":\n";;
      visit(node->cond, symbol_table);
      asm_stream << "cmp $1, %ax\n";
      asm_stream << "je _L" + std::to_string(label) + "\n";
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }

   std::shared_ptr<StaticType> Generator::visit_for_node(const std::shared_ptr<ForNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      visit(node->init, symbol_table);
      visit(node->cond, symbol_table);
      visit(node->update, symbol_table);
      visit(node->body, symbol_table);
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }

   std::shared_ptr<StaticType> Generator::visit_continue_node(const std::shared_ptr<ContinueNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }

   std::shared_ptr<StaticType> Generator::visit_break_node(const std::shared_ptr<BreakNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }

   std::shared_ptr<StaticType> Generator::visit_func_def_node(const std::shared_ptr<FuncDefNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      std::shared_ptr<SymbolTable> func_symbol_table = std::make_shared<SymbolTable>(SymbolTable(symbol_table));
      std::shared_ptr<TypeNode> return_type_node = std::static_pointer_cast<TypeNode>(node->return_type);
      std::shared_ptr<NonFuncType> return_type = std::make_shared<NonFuncType>(str_to_basic_type(return_type_node->base_type.val), return_type_node->num_pointers);
      std::vector<std::shared_ptr<NonFuncType> > arg_static_types;
      for (int i = 0; i < node->arg_names.size(); i++) {
         std::shared_ptr<TypeNode> type_node = std::static_pointer_cast<TypeNode>(node->arg_types.at(i));
         std::shared_ptr<NonFuncType> type = std::make_shared<NonFuncType>(NonFuncType(str_to_basic_type(type_node->base_type.val), type_node->num_pointers));
         arg_static_types.push_back(type);
         func_symbol_table->def_type(node->arg_names.at(i).val, type);
         func_symbol_table->def_addr(node->arg_names.at(i).val, alloc_addr());
      }
      std::shared_ptr<StaticType> func_type = std::make_shared<FuncType>(FuncType(return_type, arg_static_types));
      symbol_table->def_type(node->name.val, func_type);
      symbol_table->def_addr(node->name.val, alloc_addr());
      visit(node->body, func_symbol_table);
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }

   std::shared_ptr<StaticType> Generator::visit_return_node(const std::shared_ptr<ReturnNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }

   std::shared_ptr<StaticType> Generator::visit_enum_node(const std::shared_ptr<EnumNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      for (int i = 0; i < node->items.size(); i++) {
         symbol_table->def_type(node->items.at(i).val, std::make_shared<NonFuncType>(NonFuncType(BasicType::INT)));
         symbol_table->def_addr(node->items.at(i).val, alloc_addr());
      }
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }

   std::shared_ptr<StaticType> Generator::visit_stmt_list_node(const std::shared_ptr<StmtListNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      for (int i = 0; i < node->stmts.size(); i++) {
         visit(node->stmts.at(i), symbol_table);
      }
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }
}
