#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include "token.h"
#include "lexer.h"
#include "node.h"
#include "parser.h"
#include "static_type.h"
#include "error.h"
#include "generator.h"

namespace anthill {
   std::vector<std::string> arg_regs{ "di","si","dx","cx" };
   Generator::Generator(const std::string& file, const std::shared_ptr<SymbolTable>& global_scope)
      : file(file), global_scope(global_scope) {

   }

   int Generator::alloc_label() {
      return label_id++;
   }

   void Generator::set_var(const std::shared_ptr<StaticType>& var_type, const std::string& addr) {
      // if (var_type->to_str() == "char") {
      //    std::string inc_addr = std::to_string(std::stoi(addr) + 1);
      //    if (addr.find('(') != std::string::npos) {
      //       std::string disp = addr.substr(0, addr.find('('));
      //       std::string reg = addr.substr(addr.find('(') + 1, addr.find(')') - addr.find('(') - 1);
      //       inc_addr = std::to_string(std::stoi(disp) + 1) + "(" + reg + ")";
      //    }
      //    asm_stream << "push " + inc_addr + "\n";
      //    asm_stream << "mov %ax," + addr + "\n";
      //    asm_stream << "pop " + inc_addr + "\n";
      // }
      // else {
      asm_stream << "mov %ax," + addr + "\n";
      // }
   }

   std::string Generator::alloc_addr(const std::shared_ptr<NonFuncType>& type, const std::shared_ptr<SymbolTable>& symbol_table, bool always_global) {
      std::cout << "dbg51 " << addr_counter << '\n';
      std::string result = std::to_string(addr_counter);
      addr_counter += type->size();
      std::cout << "dbg54 " << addr_counter << '\n';
      return result;
      // if (symbol_table->is_func && !always_global) {
      //    func_addr_counter += type->size();
      //    std::string result = "-" + std::to_string(func_addr_counter) + "(%bp)";
      //    // std::cout << "dbg51 " << func_addr_counter << '\n';
      //    return result;
      // }
      // else {
      //    std::cout << "dbg51 " << addr_counter << '\n';
      //    std::string result = std::to_string(addr_counter);
      //    addr_counter += type->size();
      //    std::cout << "dbg54 " << addr_counter << '\n';
      //    return result;
      // }
   }

   void Generator::trunc_to_8_trits() {
      // asm_stream << "xor $0nDDDD, %ax\n";
   }

   std::shared_ptr<StaticType> Generator::visit(const std::shared_ptr<Node>& node, const std::shared_ptr<SymbolTable>& symbol_table, bool no_gen) {
      switch (node->get_type()) {
      case NodeType::CHAR:
         return visit_char_node(std::static_pointer_cast<CharNode>(node), symbol_table);
      case NodeType::NUM:
         return visit_num_node(std::static_pointer_cast<NumNode>(node), symbol_table);
      case NodeType::STR:
         return visit_str_node(std::static_pointer_cast<StrNode>(node), symbol_table);
      case NodeType::IDENT:
         return visit_ident_node(std::static_pointer_cast<IdentNode>(node), symbol_table, no_gen);
      case NodeType::CAST:
         return visit_cast_node(std::static_pointer_cast<CastNode>(node), symbol_table);
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
      case NodeType::WHILE:
         return visit_while_node(std::static_pointer_cast<WhileNode>(node), symbol_table);
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
      case NodeType::INCLUDE:
         return visit_include_node(std::static_pointer_cast<IncludeNode>(node), symbol_table);
      case NodeType::STMT_LIST:
         return visit_stmt_list_node(std::static_pointer_cast<StmtListNode>(node), symbol_table);
      default:
         error(file, node->line, "unknown node type");
      }
   }

   std::shared_ptr<StaticType> Generator::visit_char_node(const std::shared_ptr<CharNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      asm_stream << "mov $" << (int)(node->tok.val.front()) << ",%ax\n";
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::CHAR));
   }

   std::shared_ptr<StaticType> Generator::visit_num_node(const std::shared_ptr<NumNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      if (node->tok.val.find('.') != std::string::npos) {
         // FLOATING POINT CODE
         double double_val = std::stod(node->tok.val);
         double exponent = std::floor(std::log(double_val) / std::log(3.0));
         double significand = double_val / std::pow(3.0, exponent);
         std::string addr = "$" + alloc_addr(std::make_shared<NonFuncType>(BasicType::FLOAT), symbol_table, true);

         std::cout << "dbg125" << significand << '\n';
         std::cout << "dbg126" << exponent << '\n';

         // int packed_float = exponent * 531441 + (int)significand;

         asm_stream << "mov " << addr << ",%ax\n";
         asm_stream << "mov $" << (int)(std::round(significand * 4782969.0)) << ",0(%ax)\n";
         asm_stream << "mov $" << (int)(std::round(exponent)) << ",2(%ax)\n";

         return std::make_shared<NonFuncType>(NonFuncType(BasicType::FLOAT));
      }
      else {
         // INTEGER CODE
         asm_stream << "mov $" << std::stoi(node->tok.val) << ",%ax\n";
         return std::make_shared<NonFuncType>(NonFuncType(BasicType::INT));
      }
   }

   std::shared_ptr<StaticType> Generator::visit_str_node(const std::shared_ptr<StrNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      std::string addr;
      const std::string& s = node->tok.val;
      for (int i = 0; i <= s.size(); i++) {
         std::string ch_addr = alloc_addr(std::make_shared<NonFuncType>(NonFuncType(BasicType::CHAR)), symbol_table, true);
         if (i == 0) {
            std::cout << "dbg130 " << ch_addr << '\n';
            addr = ch_addr;
         }
         if (i == s.size()) {
            asm_stream << "mov $0" << ",%ax\n";
         }
         else {
            asm_stream << "mov $" << (int)(s.at(i)) << ",%ax\n";
         }
         set_var(std::make_shared<NonFuncType>(NonFuncType(BasicType::CHAR)), ch_addr);
      }

      asm_stream << "mov $" + addr + ",%ax\n";
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::CHAR, 1));
   }


   //    std::shared_ptr<StaticType> Generator::visit_str_node(
   //     const std::shared_ptr<StrNode>& node,
   //     const std::shared_ptr<SymbolTable>& symbol_table
   // ) {
   //     // Literal contents, e.g. "Hello world!"
   //     const std::string &s = node->tok.val;
   //     const int len = static_cast<int>(s.size());

   //     // For Option A, treat char as occupying a FULL word in memory.
   //     // i.e. NonFuncType(BasicType::CHAR).size() should be the same as int (1 word).
   //     auto charType = std::make_shared<NonFuncType>(NonFuncType(BasicType::CHAR));

   //     std::string firstAddr;  // address of s[0]

   //     // Emit each character as a full-word value
   //     for (int i = 0; i < len; ++i) {
   //         std::string addr;
   //         if (i == 0) {
   //             firstAddr = alloc_addr(charType, global_scope);
   //             addr = firstAddr;
   //         } else {
   //             addr = alloc_addr(charType, global_scope);
   //         }

   //         unsigned char ch = static_cast<unsigned char>(s[i]);
   //         // Store this character directly into the word at 'addr'
   //         asm_stream << "mov $" << static_cast<int>(ch) << "," << addr << "\n";
   //     }

   //     // Emit the terminating '\0' as a full word
   //     {
   //         std::string termAddr = alloc_addr(charType, global_scope);
   //         asm_stream << "mov $0," << termAddr << "\n";
   //     }

   //     // Load the address of the first character into %ax
   //     if (firstAddr.find('(') != std::string::npos) {
   //         // Handle something like "disp(%reg)"
   //         std::string disp = firstAddr.substr(0, firstAddr.find('('));
   //         std::string reg  = firstAddr.substr(
   //             firstAddr.find('(') + 1,
   //             firstAddr.find(')') - firstAddr.find('(') - 1
   //         );
   //         asm_stream << "mov $" << disp << ",%ax\n";
   //         asm_stream << "add " << reg << ",%ax\n";
   //     } else {
   //         // Simple absolute address like "0", "2", "4", ...
   //         asm_stream << "mov $" << firstAddr << ",%ax\n";
   //     }

   //     // The type of a string literal expression is char*
   //     return std::make_shared<NonFuncType>(NonFuncType(BasicType::CHAR, 1));
   // }

      // std::shared_ptr<StaticType> Generator::visit_str_node(const std::shared_ptr<StrNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      //    // alloc_addr(std::make_shared<NonFuncType>(NonFuncType(BasicType::CHAR, symbol_table)));
      //    std::string start_addr = alloc_addr(std::make_shared<NonFuncType>(NonFuncType(BasicType::CHAR)), global_scope);
      //    for (int i = 0; i <= node->tok.val.size(); i++) {
      //       std::string addr;
      //       if (i == 0) {
      //          addr = start_addr;
      //       }
      //       else {
      //          addr = alloc_addr(std::make_shared<NonFuncType>(NonFuncType(BasicType::CHAR)), global_scope);
      //       }
      //       std::string inc_addr = std::to_string(std::stoi(addr) + 1);
      //       if (addr.find('(') != std::string::npos) {
      //          std::string disp = addr.substr(0, addr.find('('));
      //          std::string reg = addr.substr(addr.find('(') + 1, addr.find(')') - addr.find('(') - 1);
      //          inc_addr = std::to_string(std::stoi(disp) + 1) + "(" + reg + ")";
      //       }
      //       if (i == node->tok.val.size()) {
      //          asm_stream << "push " + inc_addr + "\n";
      //          asm_stream << "mov $0," << addr << '\n';
      //          asm_stream << "pop " + inc_addr + "\n";
      //       }
      //       else {
      //          asm_stream << "mov $" << (int)(node->tok.val.at(i)) << "," << addr << '\n';
      //       }
      //    }
      //    if(start_addr.find('(') != std::string::npos) {
      //       std::string disp = start_addr.substr(0, start_addr.find('('));
      //       std::string reg = start_addr.substr(start_addr.find('(') + 1, start_addr.find(')') - start_addr.find('(') - 1);
      //       asm_stream << "mov $" + disp + ",%ax\n";
      //       asm_stream << "add " + reg + ",%ax\n"; 
      //    } else {
      //    asm_stream << "mov $" + start_addr + ",%ax\n";
      //    }
      //    return  std::make_shared<NonFuncType>(NonFuncType(BasicType::CHAR, 1));
      // }

   std::shared_ptr<StaticType> Generator::visit_ident_node(const std::shared_ptr<IdentNode>& node, const std::shared_ptr<SymbolTable>& symbol_table, bool no_gen) {
      try {
         if (!no_gen) {
            asm_stream << "mov " << symbol_table->get_addr(node->tok.val) << ",%ax\n";
         }
         return symbol_table->get_type(node->tok.val);
      }
      catch (const std::string& e) {
         error(file, node->line, e);
      }
   }

   std::shared_ptr<StaticType> Generator::visit_cast_node(const std::shared_ptr<CastNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      if (node->type->to_str() == "void") {
         error(file, node->type->line, "cannot cast to type void");
      }
      std::shared_ptr<NonFuncType> cast_type = NonFuncType::parse_type(node->type->to_str());
      std::shared_ptr<StaticType> val_type = visit(node->val, symbol_table);
      if (val_type->is_func()) {
         error(file, node->type->line, "cannot cast a function");
      }
      if (val_type->to_str() == "void") {
         error(file, node->type->line, "cannot cast a value of type void");
      }
      if (val_type->to_str() != "char" && node->type->to_str() == "char") {
         trunc_to_8_trits();
      }

      return cast_type;
   }

   std::shared_ptr<StaticType> Generator::visit_call_node(const std::shared_ptr<CallNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      if (node->callee->get_type() != NodeType::IDENT) {
         error(file, node->callee->line, "cannot call a non-identifier expression");
      }

      std::string func_name = std::static_pointer_cast<IdentNode>(node->callee)->tok.val;
      std::cout << "dbg301" << func_name << '\n';
      if (func_name == "__asm__") {
         if (node->args.size() > 1) {
            error(file, node->callee->line, "cannot use __asm__ with multiple arguments");
         }
         asm_stream << std::static_pointer_cast<StrNode>(node->args.at(0))->tok.val;
         return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
      }
      else {
         std::shared_ptr<StaticType> callee_type = visit(node->callee, symbol_table, true);
         if (!callee_type->is_func()) {
            error(file, node->callee->line, "cannot call a non-function");
         }
         std::shared_ptr<FuncType> func_type = std::static_pointer_cast<FuncType>(callee_type);
         if (node->args.size() != func_type->arg_types.size()) {
            error(file, node->callee->line, "expected " + std::to_string(func_type->arg_types.size()) + " arguments to function '" + func_name + "', got " + std::to_string(node->args.size()));
         }
         for (int i = 0; i < node->args.size(); i++) {
            std::shared_ptr<StaticType> arg_type = visit(node->args.at(i), symbol_table);
            asm_stream << "mov %ax,%" << arg_regs[i] << '\n';
            if (arg_type->to_str() != "char" && func_type->arg_types.at(i)->to_str() == "char") {
               asm_stream << "and %" << arg_regs[i] << "," << func_type->arg_types.at(i) << '\n';
            }
         }
         asm_stream << "call " << func_name << '\n';
         return func_type->return_type;
      }
   }

   std::shared_ptr<StaticType> Generator::visit_postfix_node(const std::shared_ptr<PostfixNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      std::shared_ptr<StaticType> node_type = visit(node->node, symbol_table);

      // if (node_type->to_str() == "void") {
      //    error(file, node->node->line, "cannot perform postfix unary operations on a value of type void");
      // }


      // switch (node->op_tok.type) {
      //    case TokenType::INCR: {
      //       std::shared_ptr<StaticType> node_type =  visit(node->node, symbol_table, true);
      //       if (node->node->get_type() == NodeType::PREFIX) {
      //          visit(std::static_pointer_cast<PrefixNode>(node->node)->node, symbol_table);

      //       }

      //       break;
      //    }
      //    }

      return node_type;
   }

   std::shared_ptr<StaticType> Generator::visit_prefix_node(const std::shared_ptr<PrefixNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      std::shared_ptr<StaticType> node_type = visit(node->node, symbol_table);


      if (node_type->is_func()) {
         error(file, node->node->line, "cannot perform prefix unary operations on a function");
      }

      if (node_type->to_str() == "void") {
         error(file, node->node->line, "cannot perform prefix unary operations on a value of type void");
      }

      switch (node->op_tok.type) {
      case TokenType::AMPER: {
         if (node->node->get_type() == NodeType::IDENT) {
            std::string addr = symbol_table->get_addr(std::static_pointer_cast<IdentNode>(node->node)->tok.val);
            if (addr.find('(') != std::string::npos) {
               std::string disp = addr.substr(0, addr.find('('));
               std::string reg = addr.substr(addr.find('(') + 1, addr.find(')') - addr.find('(') - 1);
               asm_stream << "mov $" << disp << ",%ax\n";
               asm_stream << "add " << reg << ",%ax\n";
            }
            else {
               asm_stream << "mov $" << addr << ",%ax\n";
            }
         }
         else {
            error(file, node->node->line, "cannot find the address of a non-identifier expression");
         }
         std::shared_ptr<NonFuncType> non_func_type = std::static_pointer_cast<NonFuncType>(node_type);
         return std::make_shared<NonFuncType>(non_func_type->basic_type, non_func_type->pointer_levels + 1);
      }
      case TokenType::STAR: {
         asm_stream << "mov 0(%ax),%ax\n";
         // if (node_type->to_str() == "char*") {
         //    trunc_to_8_trits();
         // }
         std::shared_ptr<NonFuncType> non_func_type = std::static_pointer_cast<NonFuncType>(node_type);
         std::cout << "dbg260 " << non_func_type->to_str() << '\n';
         if (non_func_type->pointer_levels == 0) {
            error(file, node->node->line, "cannot dereference a non-pointer");
         }
         if (non_func_type->to_str() == "void*") {
            error(file, node->node->line, "cannot dereference a void pointer");
         }
         return std::make_shared<NonFuncType>(non_func_type->basic_type, non_func_type->pointer_levels - 1);
      }
      case TokenType::MINUS: {
         asm_stream << "neg %ax\n";
         break;
      }
      case TokenType::PLUS: {
         break;
      }
      }


      return node_type;
   }


   std::shared_ptr<StaticType> Generator::visit_bin_op_node(const std::shared_ptr<BinOpNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      std::shared_ptr<StaticType> temp = visit(node->left_node, symbol_table);
      if (temp->is_func()) {
         error(file, node->left_node->line, "cannot perform binary operations on a function");
      }
      std::shared_ptr<NonFuncType> left_type = std::static_pointer_cast<NonFuncType>(temp);
      std::shared_ptr<NonFuncType> right_type;

      if (left_type->to_str() == "void") {
         error(file, node->right_node->line, "cannot perform binary operations on a value of type void");
      }

      // if (left_type->to_str() == "void*") {
      //    error(file, node->right_node->line, "cannot perform binary operations on a void pointer");
      // }

      if (left_type->to_str() == "float") {
         switch (node->op_tok.type) {
         case TokenType::PLUS: {
            asm_stream << "fld %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->to_str() != "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);
            asm_stream << "fld %ax\n";
            asm_stream << "fadd\n";
            asm_stream << "fstp %ax\n";
            break;
         }
         case TokenType::MINUS: {
            asm_stream << "fld %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->to_str() != "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);
            asm_stream << "fld %ax\n";
            asm_stream << "fsub\n";
            asm_stream << "fstp %ax\n";
            break;
         }
         case TokenType::STAR: {
            asm_stream << "fld %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->to_str() != "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);
            asm_stream << "fld %ax\n";
            asm_stream << "fmul\n";
            asm_stream << "fstp %ax\n";
            break;
         }
         case TokenType::SLASH: {
            asm_stream << "fld %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->to_str() != "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);
            asm_stream << "fld %ax\n";
            asm_stream << "fdiv\n";
            asm_stream << "fstp %ax\n";
            break;
         }
         case TokenType::EQUAL: {
            asm_stream << "fld %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->to_str() != "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);
            asm_stream << "fld %ax\n";
            asm_stream << "fcmp\n";
            asm_stream << "mov $1,%ax\n";
            int label = alloc_label();
            asm_stream << "je _L" + std::to_string(label) + "\n";
            asm_stream << "mov $-1,%ax\n";
            asm_stream << "_L" + std::to_string(label) + ":\n";
            break;
         }
         case TokenType::NOTEQ: {
            asm_stream << "fld %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->to_str() != "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);
            asm_stream << "fld %ax\n";
            asm_stream << "fcmp\n";
            asm_stream << "mov $1,%ax\n";
            int label = alloc_label();
            asm_stream << "jne _L" + std::to_string(label) + "\n";
            asm_stream << "mov $-1,%ax\n";
            asm_stream << "_L" + std::to_string(label) + ":\n";
            break;
         }
         case TokenType::LESS: {
            asm_stream << "fld %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->to_str() != "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);
            asm_stream << "fld %ax\n";
            asm_stream << "fcmp\n";
            asm_stream << "mov $1,%ax\n";
            int label = alloc_label();
            asm_stream << "jl _L" + std::to_string(label) + "\n";
            asm_stream << "mov $-1,%ax\n";
            asm_stream << "_L" + std::to_string(label) + ":\n";
            break;
         }
         case TokenType::LTEQ: {
            asm_stream << "fld %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->to_str() != "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);
            asm_stream << "fld %ax\n";
            asm_stream << "fcmp\n";
            asm_stream << "mov $1,%ax\n";
            int label = alloc_label();
            asm_stream << "jle _L" + std::to_string(label) + "\n";
            asm_stream << "mov $-1,%ax\n";
            asm_stream << "_L" + std::to_string(label) + ":\n";
            break;
         }
         case TokenType::GREATER: {
            asm_stream << "fld %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->to_str() != "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);
            asm_stream << "fld %ax\n";
            asm_stream << "fcmp\n";
            asm_stream << "mov $1,%ax\n";
            int label = alloc_label();
            asm_stream << "jg _L" + std::to_string(label) + "\n";
            asm_stream << "mov $-1,%ax\n";
            asm_stream << "_L" + std::to_string(label) + ":\n";
            break;
         }
         case TokenType::GTEQ: {
            asm_stream << "fld %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->to_str() != "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);
            asm_stream << "fld %ax\n";
            asm_stream << "fcmp\n";
            asm_stream << "mov $1,%ax\n";
            int label = alloc_label();
            asm_stream << "jge _L" + std::to_string(label) + "\n";
            asm_stream << "mov $-1,%ax\n";
            asm_stream << "_L" + std::to_string(label) + ":\n";
            break;
         }

         }
      }
      else {
         switch (node->op_tok.type) {
         case TokenType::AMPER: {
            asm_stream << "push %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->is_func()) {
               error(file, node->right_node->line, "cannot perform binary operations on a function");
            }
            if (temp2->to_str() == "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);
            asm_stream << "pop %cx\n";
            asm_stream << "and %cx,%ax\n";
            break;
         }
         case TokenType::PIPE: {
            ;
            asm_stream << "push %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->is_func()) {
               error(file, node->right_node->line, "cannot perform binary operations on a function");
            }
            if (temp2->to_str() == "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);

            asm_stream << "pop %cx\n";
            asm_stream << "or %cx,%ax\n";
            break;
         }
         case TokenType::CARET: {
            ;
            asm_stream << "push %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->is_func()) {
               error(file, node->right_node->line, "cannot perform binary operations on a function");
            }
            if (temp2->to_str() == "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);
            asm_stream << "pop %cx\n";
            asm_stream << "xor %cx,%ax\n";
            break;
         }
         case TokenType::LSHIFT: {
            ;
            asm_stream << "push %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->is_func()) {
               error(file, node->right_node->line, "cannot perform binary operations on a function");
            }
            if (temp2->to_str() == "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);
            asm_stream << "pop %cx\n";
            asm_stream << "xchg %cx,%ax\n";
            asm_stream << "shl %cx,%ax\n";
            break;
         }
         case TokenType::RSHIFT: {
            ;
            asm_stream << "push %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->is_func()) {
               error(file, node->right_node->line, "cannot perform binary operations on a function");
            }
            if (temp2->to_str() == "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);
            asm_stream << "pop %cx\n";
            asm_stream << "xchg %cx,%ax\n";
            asm_stream << "shr %cx,%ax\n";
            break;
         }
         case TokenType::LOGAND: {
            ;
            asm_stream << "push %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->is_func()) {
               error(file, node->right_node->line, "cannot perform binary operations on a function");
            }
            if (temp2->to_str() == "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);
            asm_stream << "pop %cx\n";
            asm_stream << "and %cx,%ax\n";
            break;
         }
         case TokenType::PLUS: {
            ;
            asm_stream << "push %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->is_func()) {
               error(file, node->right_node->line, "cannot perform binary operations on a function");
            }
            if (temp2->to_str() == "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);
            asm_stream << "pop %cx\n";
            asm_stream << "add %cx,%ax\n";
            // if ((left_type->pointer_levels > 0 /* && left_type->to_str() != "char*" */ )
            //    || (right_type->pointer_levels > 0  /* && right_type->to_str() != "char*") */ )) {
            //    asm_stream << "add %cx,%ax\n";
            // }
            break;
         }
         case TokenType::MINUS: {
            ;
            asm_stream << "push %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->is_func()) {
               error(file, node->right_node->line, "cannot perform binary operations on a function");
            }
            if (temp2->to_str() == "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);
            asm_stream << "pop %cx\n";
            asm_stream << "xchg %cx,%ax\n";
            asm_stream << "sub %cx,%ax\n";
            // if ((left_type->pointer_levels > 0 /* && left_type->to_str() != "char*" */ )
            //    || (right_type->pointer_levels > 0 /* && right_type->to_str() != "char*") */) {
            //    asm_stream << "xchg %cx,%ax\n";
            //    asm_stream << "sub %cx,%ax\n";
            // }
            break;
         }
         case TokenType::STAR: {
            ;
            asm_stream << "push %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->is_func()) {
               error(file, node->right_node->line, "cannot perform binary operations on a function");
            }
            if (temp2->to_str() == "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);
            asm_stream << "pop %cx\n";
            asm_stream << "mul %cx\n";
            break;
         }
         case TokenType::SLASH: {
            ;
            asm_stream << "push %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->is_func()) {
               error(file, node->right_node->line, "cannot perform binary operations on a function");
            }
            if (temp2->to_str() == "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);
            asm_stream << "pop %cx\n";
            asm_stream << "xchg %cx,%ax\n";
            asm_stream << "div %cx\n";
            break;
         }
         case TokenType::MOD: {
            ;
            asm_stream << "push %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->is_func()) {
               error(file, node->right_node->line, "cannot perform binary operations on a function");
            }
            if (temp2->to_str() == "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);
            asm_stream << "pop %cx\n";
            asm_stream << "xchg %cx,%ax\n";
            asm_stream << "div %cx\n";
            asm_stream << "mov %dx,%ax\n";
            break;
         }
         case TokenType::EQUAL: {
            // ;
            asm_stream << "push %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->is_func()) {
               error(file, node->right_node->line, "cannot perform binary operations on a function");
            }
            if (temp2->to_str() == "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);
            asm_stream << "pop %cx\n";
            asm_stream << "cmp %ax,%cx\n";
            asm_stream << "mov $1,%ax\n";
            int label = alloc_label();
            asm_stream << "je _L" + std::to_string(label) + "\n";
            asm_stream << "mov $-1,%ax\n";
            asm_stream << "_L" + std::to_string(label) + ":\n";
            break;
         }
         case TokenType::NOTEQ: {
            // ;
            asm_stream << "push %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->is_func()) {
               error(file, node->right_node->line, "cannot perform binary operations on a function");
            }
            if (temp2->to_str() == "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);
            asm_stream << "pop %cx\n";
            asm_stream << "cmp %ax,%cx\n";
            asm_stream << "mov $1,%ax\n";
            int label = alloc_label();
            asm_stream << "jne _L" + std::to_string(label) + "\n";
            asm_stream << "mov $-1,%ax\n";
            asm_stream << "_L" + std::to_string(label) + ":\n";
            break;
         }
         case TokenType::LESS: {
            // ;
            asm_stream << "push %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->is_func()) {
               error(file, node->right_node->line, "cannot perform binary operations on a function");
            }
            if (temp2->to_str() == "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);
            asm_stream << "pop %cx\n";
            asm_stream << "cmp %ax,%cx\n";
            asm_stream << "mov $1,%ax\n";
            int label = alloc_label();
            asm_stream << "jl _L" + std::to_string(label) + "\n";
            asm_stream << "mov $-1,%ax\n";
            asm_stream << "_L" + std::to_string(label) + ":\n";
            break;
         }
         case TokenType::LTEQ: {
            // ;
            asm_stream << "push %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->is_func()) {
               error(file, node->right_node->line, "cannot perform binary operations on a function");
            }
            if (temp2->to_str() == "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);
            asm_stream << "pop %cx\n";
            asm_stream << "cmp %ax,%cx\n";
            asm_stream << "mov $1,%ax\n";
            int label = alloc_label();
            asm_stream << "jle _L" + std::to_string(label) + "\n";
            asm_stream << "mov $-1,%ax\n";
            asm_stream << "_L" + std::to_string(label) + ":\n";
            break;
         }
         case TokenType::GREATER: {
            // ;
            asm_stream << "push %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->is_func()) {
               error(file, node->right_node->line, "cannot perform binary operations on a function");
            }
            if (temp2->to_str() == "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);
            asm_stream << "pop %cx\n";
            asm_stream << "cmp %ax,%cx\n";
            asm_stream << "mov $1,%ax\n";
            int label = alloc_label();
            asm_stream << "jg _L" + std::to_string(label) + "\n";
            asm_stream << "mov $-1,%ax\n";
            asm_stream << "_L" + std::to_string(label) + ":\n";
            break;
         }
         case TokenType::GTEQ: {
            // ;
            asm_stream << "push %ax\n";
            std::shared_ptr<StaticType> temp2 = visit(node->right_node, symbol_table);
            if (temp2->is_func()) {
               error(file, node->right_node->line, "cannot perform binary operations on a function");
            }
            if (temp2->to_str() == "float") {
               error(file, node->right_node->line, "cannot perform binary operations on a mix of float and non-float types");
            }
            right_type = std::static_pointer_cast<NonFuncType>(temp2);
            asm_stream << "pop %cx\n";
            asm_stream << "cmp %ax,%cx\n";
            asm_stream << "mov $1,%ax\n";
            int label = alloc_label();
            asm_stream << "jge _L" + std::to_string(label) + "\n";
            asm_stream << "mov $-1,%ax\n";
            asm_stream << "_L" + std::to_string(label) + ":\n";
            break;
         }
         }
      }

      if ((left_type->pointer_levels > 0 || right_type->pointer_levels > 0) && !(node->op_tok.type == TokenType::PLUS || node->op_tok.type == TokenType::MINUS || node->op_tok.type == TokenType::EQUAL || node->op_tok.type == TokenType::NOTEQ)) {
         if (left_type->pointer_levels) {
            error(file, node->left_node->line, "cannot perform binary operations other than +, -, ==, != on a pointer");
         }
         else {
            error(file, node->right_node->line, "cannot perform binary operations other than +, -, ==, != on a pointer");
         }
      }

      if (left_type->pointer_levels > 0 && right_type->pointer_levels > 0) {
         error(file, node->left_node->line, "cannot perform binary operations when both operands are pointers");
      }

      if (right_type->is_func()) {
         error(file, node->left_node->line, "cannot perform binary operations on a function");
      }

      if (right_type->to_str() == "void") {
         error(file, node->right_node->line, "cannot perform binary operations on a value of type void");
      }


      if (left_type->to_str() == "float" || right_type->to_str() == "float") {
         return right_type;
      }

      if (left_type->to_str() == "char" && right_type->to_str() == "char") {
         trunc_to_8_trits();
         return left_type;
      }
      else if (left_type->to_str() == "char" || right_type->pointer_levels > 0) {
         return right_type;
      }
      else {
         return left_type;
      }
   }

   std::shared_ptr<StaticType> Generator::visit_assign_node(const std::shared_ptr<AssignNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      std::shared_ptr<StaticType> left_node_type = visit(node->left_node, symbol_table, true);
      if (node->left_node->get_type() == NodeType::PREFIX) {
         visit(std::static_pointer_cast<PrefixNode>(node->left_node)->node, symbol_table);
         asm_stream << "push %ax\n";
         visit(node->right_node, symbol_table);
         asm_stream << "pop %bx\n";
         set_var(left_node_type, "0(%bx)");
         return left_node_type;
      }
      else {
         std::string addr = symbol_table->get_addr(std::static_pointer_cast<IdentNode>(node->left_node)->tok.val);
         visit(node->right_node, symbol_table);
         set_var(left_node_type, addr);
         return left_node_type;
      }
   }

   std::shared_ptr<StaticType> Generator::visit_var_def_node(
      const std::shared_ptr<VarDefNode>& node,
      const std::shared_ptr<SymbolTable>& symbol_table
   ) {
      try {
         std::shared_ptr<NonFuncType> var_type =
            NonFuncType::parse_type(node->type->to_str());
         if (var_type->to_str() == "void") {
            error(file, node->name.line, "cannot define variable of type void");
         }

         // Evaluate initializer: result in %ax
         visit(node->val, symbol_table);

         // If this is a *function* scope variable, allocate stack space for it
         if (symbol_table->is_func) {
            // Reserve var_type->size() “words” on the stack
            asm_stream << "sub $" << var_type->size() << ",%sp\n";
         }

         // Now assign it a negative offset using alloc_addr
         std::string addr = alloc_addr(var_type, symbol_table);
         symbol_table->def_type(node->name.val, var_type);
         symbol_table->def_addr(node->name.val, addr);

         // Store %ax into that address
         set_var(var_type, addr);
      }
      catch (const std::string& e) {
         error(file, node->line, e);
      }
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }

   // std::shared_ptr<StaticType> Generator::visit_var_def_node(const std::shared_ptr<VarDefNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
   //    try {
   //       std::shared_ptr<NonFuncType> var_type = NonFuncType::parse_type(node->type->to_str());
   //       if (var_type->to_str() == "void") {
   //          error(file, node->name.line, "cannot define variable of type void");
   //       }
   //       visit(node->val, symbol_table);
   //       std::string addr = alloc_addr(var_type, symbol_table);
   //       symbol_table->def_type(node->name.val, var_type);
   //       symbol_table->def_addr(node->name.val, addr);
   //       set_var(var_type, addr);
   //    }
   //    catch (const std::string& e) {
   //       error(file, node->line, e);
   //    }
   //    return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   // }

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
      if (node->else_body) {
         visit(node->else_body, symbol_table);
      }
      asm_stream << "_L" + std::to_string(label2) + ":\n";
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }

   std::shared_ptr<StaticType> Generator::visit_while_node(const std::shared_ptr<WhileNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      int label = alloc_label();
      int label2 = alloc_label();
      asm_stream << "jmp _L" + std::to_string(label2) + "\n";
      asm_stream << "_L" + std::to_string(label) + ":\n";
      visit(node->body, symbol_table);
      asm_stream << "_L" + std::to_string(label2) + ":\n";
      visit(node->cond, symbol_table);
      asm_stream << "cmp $1, %ax\n";
      asm_stream << "je _L" + std::to_string(label) + "\n";
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }

   std::shared_ptr<StaticType> Generator::visit_for_node(const std::shared_ptr<ForNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      visit(node->init, symbol_table);
      int label = alloc_label();
      int label2 = alloc_label();
      asm_stream << "jmp _L" + std::to_string(label2) + "\n";
      asm_stream << "_L" + std::to_string(label) + ":\n";
      visit(node->body, symbol_table);
      visit(node->update, symbol_table);
      asm_stream << "_L" + std::to_string(label2) + ":\n";
      visit(node->cond, symbol_table);
      asm_stream << "cmp $1, %ax\n";
      asm_stream << "je _L" + std::to_string(label) + "\n";
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }

   std::shared_ptr<StaticType> Generator::visit_continue_node(const std::shared_ptr<ContinueNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }

   std::shared_ptr<StaticType> Generator::visit_break_node(const std::shared_ptr<BreakNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }

   // std::shared_ptr<StaticType> Generator::visit_func_def_node(
   //     const std::shared_ptr<FuncDefNode>& node,
   //     const std::shared_ptr<SymbolTable>& symbol_table
   // ) {
   //     current_func_name = node->name.val;

   //     // --- 1. Set up a temporary stream for this function's body ---
   //     std::stringstream func_stream;
   //     std::streambuf* old_buf = asm_stream.rdbuf(func_stream.rdbuf());

   //     // --- 2. Create function-local symbol table and reset frame size ---
   //     std::shared_ptr<SymbolTable> func_symbol_table =
   //         std::make_shared<SymbolTable>(SymbolTable(symbol_table));
   //     func_symbol_table->is_func = true;

   //     func_addr_counter = 0;  // total stack slots (words) used by this function

   //     try {
   //         // --- 3. Set up return type and argument types as before ---
   //         std::shared_ptr<TypeNode> return_type_node =
   //             std::static_pointer_cast<TypeNode>(node->return_type);
   //         std::shared_ptr<NonFuncType> return_type =
   //             std::make_shared<NonFuncType>(
   //                 NonFuncType(str_to_basic_type(return_type_node->base_type.val),
   //                             return_type_node->num_pointers));

   //         std::vector<std::shared_ptr<NonFuncType>> arg_static_types;

   //         // func_addr_counter counts stack usage for args + locals
   //         for (int i = 0; i < node->arg_names.size(); i++) {
   //             std::shared_ptr<TypeNode> type_node =
   //                 std::static_pointer_cast<TypeNode>(node->arg_types[i]);
   //             std::shared_ptr<NonFuncType> type =
   //                 std::make_shared<NonFuncType>(
   //                     NonFuncType(str_to_basic_type(type_node->base_type.val),
   //                                 type_node->num_pointers));

   //             // Allocate a stack slot for this argument in the function frame
   //             std::string addr = alloc_addr(type, func_symbol_table); // e.g. "-2(%bp)"

   //             arg_static_types.push_back(type);
   //             func_symbol_table->def_type(node->arg_names[i].val, type);
   //             func_symbol_table->def_addr(node->arg_names[i].val, addr);

   //             // Move argument from register into its stack slot
   //             asm_stream << "mov %" << arg_regs[i] << ",%ax\n";
   //             set_var(type, addr);
   //         }

   //         std::shared_ptr<StaticType> func_type =
   //             std::make_shared<FuncType>(FuncType(return_type, arg_static_types));

   //         std::cout << node->name.to_str() << '\n';
   //         symbol_table->def_type(node->name.val, func_type);
   //         symbol_table->def_addr(node->name.val, node->name.val);
   //     }
   //     catch (const std::string& e) {
   //         error(file, node->line, e);
   //     }

   //     // --- 4. Generate the function body into func_stream ---
   //     visit(node->body, func_symbol_table);

   //     // NOTE: We do NOT emit any "pop %bp" / "ret" in here anymore.
   //     // The fallthrough epilogue will be added after we restore asm_stream below.

   //     // --- 5. Restore the original asm_stream buffer ---
   //     asm_stream.rdbuf(old_buf);

   //     // --- 6. Now we know func_addr_counter; emit real function with prologue ---
   //     asm_stream << node->name.val << ":\n";
   //     asm_stream << "push %bp\nmov %sp,%bp\n";

   //     if (func_addr_counter > 0) {
   //         asm_stream << "sub $" << func_addr_counter << ",%sp\n";
   //     }

   //     // Emit the body that we buffered
   //     asm_stream << func_stream.str();

   //     // --- 7. Fallthrough epilogue ---
   //     // For non-main functions, early returns already emit their own epilogue
   //     // in visit_return_node for non-main, but we still keep a generic one here
   //     // for the "no explicit return" case.
   //     asm_stream << "pop %bp\n";
   //     asm_stream << "ret\n";

   //     return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   // }


   std::shared_ptr<StaticType> Generator::visit_func_def_node(const std::shared_ptr<FuncDefNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      current_func_name = node->name.val;
      // asm_stream << "call main\nmov %ax,%dx\nmov $0nDD,%ax\nint $0\n";
      // }
      asm_stream << node->name.val << ":\n";
      asm_stream << "push %bp\nmov %sp,%bp\nsub $729,%sp\n";
      std::shared_ptr<SymbolTable> func_symbol_table = std::make_shared<SymbolTable>(SymbolTable(symbol_table));
      func_symbol_table->is_func = true;

      try {
         // if(node->name.val == "main") {
         std::shared_ptr<TypeNode> return_type_node = std::static_pointer_cast<TypeNode>(node->return_type);
         std::shared_ptr<NonFuncType> return_type = std::make_shared<NonFuncType>(str_to_basic_type(return_type_node->base_type.val), return_type_node->num_pointers);
         std::vector<std::shared_ptr<NonFuncType> > arg_static_types;
         func_addr_counter = 0;
         // std::cout << "dbg414" << '\n';
         for (int i = 0; i < node->arg_names.size(); i++) {
            // std::cout << "dbg416" << '\n';
            std::shared_ptr<TypeNode> type_node = std::static_pointer_cast<TypeNode>(node->arg_types[i]);
            std::shared_ptr<NonFuncType> type = std::make_shared<NonFuncType>(NonFuncType(str_to_basic_type(type_node->base_type.val), type_node->num_pointers));
            std::string addr = alloc_addr(type, func_symbol_table);
            arg_static_types.push_back(type);
            func_symbol_table->def_type(node->arg_names[i].val, type);
            func_symbol_table->def_addr(node->arg_names[i].val, addr);
            asm_stream << "mov %" << arg_regs[i] << ",%ax\n";
            set_var(type, addr);
            // asm_stream << "mov %ax," << addr << "\n";
            // std::cout << "dbg425" << '\n';
         }
         std::shared_ptr<StaticType> func_type = std::make_shared<FuncType>(FuncType(return_type, arg_static_types));
         std::cout << node->name.to_str() << '\n';
         symbol_table->def_type(node->name.val, func_type);
         symbol_table->def_addr(node->name.val, node->name.val);
      }
      catch (const std::string& e) {
         error(file, node->line, e);
      }
      // std::cout << "dbg430" << '\n';
      visit(node->body, func_symbol_table);
      asm_stream << "mov %bp,%sp\n";
      asm_stream << "pop %bp\n";
      asm_stream << "ret\n";
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }

   std::shared_ptr<StaticType> Generator::visit_return_node(const std::shared_ptr<ReturnNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      visit(node->body, symbol_table);
      if (current_func_name == "main") {
         asm_stream << "mov %ax,%dx\n";
         asm_stream << "mov $0nDD,%ax\n";
         asm_stream << "int $0\n";
      }
      else {
         asm_stream << "mov %bp,%sp\n";
         asm_stream << "pop %bp\n";
         asm_stream << "ret\n";
      }
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }

   std::shared_ptr<StaticType> Generator::visit_enum_node(const std::shared_ptr<EnumNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      for (int i = 0; i < node->items.size(); i++) {
         std::shared_ptr<NonFuncType> int_type = std::make_shared<NonFuncType>(NonFuncType(BasicType::INT));
         std::string addr = alloc_addr(int_type, symbol_table);
         symbol_table->def_type(node->items.at(i).val, int_type);
         symbol_table->def_addr(node->items.at(i).val, addr);
         asm_stream << "mov $" << i << "," << addr << '\n';
      }
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }

   std::shared_ptr<StaticType> Generator::visit_include_node(const std::shared_ptr<IncludeNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      std::string file_path = node->path.val;
      std::ifstream file(file_path);

      if (!file) {
         std::cerr << "Error: Unable to open file " << file_path << std::endl;
         std::exit(1);
      }

      std::stringstream buffer;
      buffer << file.rdbuf();
      std::string str = buffer.str();

      anthill::Lexer lexer(file_path, str);
      std::vector<anthill::Token> tokens = lexer.generate_tokens();
      anthill::Parser parser(file_path, tokens);
      anthill::Generator gen(file_path, std::make_shared<anthill::SymbolTable>(anthill::SymbolTable()));
      gen.global_scope = global_scope;

      // inherit current counters so labels/addresses stay globally unique
      gen.label_id = label_id;
      gen.addr_counter = addr_counter;

      gen.visit(parser.parse(), gen.global_scope);
      asm_stream << gen.asm_stream.str();

      // propagate updated counters back
      label_id = gen.label_id;
      addr_counter = gen.addr_counter;
      // anthill::Generator gen(file_path, std::make_shared<anthill::SymbolTable>(anthill::SymbolTable()));
      // gen.global_scope = global_scope;
      // gen.visit(parser.parse(), gen.global_scope);
      // asm_stream << gen.asm_stream.str();
      // label_id = gen.label_id + 1;
      // addr_counter = gen.addr_counter + 4;

      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }

   std::shared_ptr<StaticType> Generator::visit_stmt_list_node(const std::shared_ptr<StmtListNode>& node, const std::shared_ptr<SymbolTable>& symbol_table) {
      // std::cout << "dbg462 " << node->stmts.size() << '\n';
      for (int i = 0; i < node->stmts.size(); i++) {
         // std::cout << "dbg464" << '\n';
         visit(node->stmts.at(i), symbol_table);
      }
      return std::make_shared<NonFuncType>(NonFuncType(BasicType::VOID));
   }
}
