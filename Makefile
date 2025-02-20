default:
	clang++ src/core/*.cpp src/teremu/*.cpp -o /usr/local/bin/teremu -O3 -std=c++11
	clang++ src/core/*.cpp src/terasm/*.cpp -o /usr/local/bin/terasm -O3 -std=c++11
	clang++ anthill/src/*.cpp anthill/test/main.cpp -o anthill/test/main -O3 -std=c++11