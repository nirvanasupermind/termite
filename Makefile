default:
	clang++ src/core/*.cpp src/teremu/*.cpp -o /usr/local/bin/teremu -O3 -std=c++11
	clang++ anthill/src/*.cpp -o /usr/local/bin/anthillc -O3 -std=c++11