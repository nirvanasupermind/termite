clang++ src/core/*.cpp src/teremu/cpu.cpp test/teremu_unit_test.cpp -o test/teremu_unit_test -O3 -std=c++11
clang++ src/core/*.cpp src/terasm/token.cpp src/terasm/lexer.cpp src/terasm/assembler.cpp test/terasm_unit_test.cpp -o test/terasm_unit_test -O3 -std=c++11
test/teremu_unit_test
test/terasm_unit_test