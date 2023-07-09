ifeq ($(OS),Windows_NT)
    SOURCE := src\teremu\*.cpp
    TARGET := C:\Program Files\ter
else
    SOURCE := src/teremu/*.cpp
    TARGET := /usr/local/bin/teremu
endif

default:
	clang++ $(SOURCE) -o $(TARGET) -std=c++11