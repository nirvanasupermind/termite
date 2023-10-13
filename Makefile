default:
	# clang++ src/teremu/*.cpp -o /usr/local/bin/teremu -std=c++11
	clang++ src/terasm/*.cpp test/main.cpp -o test/main -std=c++11