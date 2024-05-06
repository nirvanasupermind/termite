#include <iostream>
#include <string>
#include <vector>
#include "../src/token.h"
#include "../src/lexer.h"
#include "../src/node.h"
#include "../src/parser.h"
#include "../src/compiler.h"
#include "../src/env.h"

int main() {
    std::string str = "int x = 1; while(x < 100) { x = x * 2; } ";
    try {
        anthill::Lexer lexer("sample", str);
        anthill::Parser parser("sample", lexer.generate_tokens());
        anthill::Compiler compiler("sample");
        std::shared_ptr<anthill::Env> global_env(new anthill::Env({}, {}));
        compiler.visit(parser.parse(), global_env);
        std::cout << compiler.assembly << '\n';

        // std::shared_ptr<anthill::BinaryOpNode> binary_op_node((anthill::BinaryOpNode*)(result.get()));
        // std::cout << binary_op_node->node_a->str() << '\n';
        // std::cout << ((anthill::BinaryOpNode*)binary_op_node->node_a.get())->node_a->str() << '\n';
        // std::cout << ((anthill::BinaryOpNode*)binary_op_node->node_a.get())->node_b->str() << '\n';
        // std::cout << binary_op_node->node_b->str() << '\n';
    }
    catch (const std::string& e) {
        std::cerr << e << '\n';
    }
    return 0;
} 