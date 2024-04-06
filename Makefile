default:
	clang++ src/core/*.cpp src/teremu/*.cpp -o /usr/local/bin/teremu -std=c++11
	clang++ src/core/*.cpp src/terasm/*.cpp -o /usr/local/bin/terasm -std=c++11
	clang++ anthill/src/*.cpp anthill/test/main.cpp -o anthill/test/test -std=c++11