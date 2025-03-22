#include <iostream>
#include <string>
#include <vector>
#include "../src/token.h"
#include "../src/lexer.h"
#include "../src/node.h"
#include "../src/parser.h"
#include "../src/symbol_table.h"
#include "../src/generator.h"

// #include "../src/node.h"
// #include "../src/parser.h"
// #include "../src/compiler.h"
// #include "../src/env.h"

int main() {
    std::string str = "int fac(int x) { if(x == 0) { return 1; } else { return x * fac(x - 1); } } \n int main() { fac(5); return 0; }";
    try {
        anthill::Lexer lexer("temp", str);
        std::vector<anthill::Token> tokens = lexer.generate_tokens();
        anthill::Parser parser("temp", tokens);
        anthill::Generator gen("temp", std::make_shared<anthill::SymbolTable>(anthill::SymbolTable()));
        gen.visit(parser.parse(), gen.global_scope);
        std::cout << gen.asm_stream.str() << '\n';
     
        // anthill::Parser parser("sample", lexer.generate_tokens());
        // anthill::Compiler compiler("sample");
        // std::shared_ptr<anthill::Env> global_env(new anthill::Env({}, {}));
        // compiler.visit(parser.parse(), global_env);
        // std::cout << compiler.assembly << '\n';

        // // std::shared_ptr<anthill::BinaryOpNode> binary_op_node((anthill::BinaryOpNode*)(result.get()));
        // // std::cout << binary_op_node->node_a->str() << '\n';
        // // std::cout << ((anthill::BinaryOpNode*)binary_op_node->node_a.get())->node_a->str() << '\n';
        // // std::cout << ((anthill::BinaryOpNode*)binary_op_node->node_a.get())->node_b->str() << '\n';
        // // std::cout << binary_op_node->node_b->str() << '\n';
    }
    catch (const std::string& e) {
        std::cerr << e << '\n';
        
    }
    return 0;
} 