ifeq ($(OS),Windows_NT)
    SOURCE := src\ter\*.cpp
    TARGET := C:\Program Files\ter
else
    SOURCE := src/ter/*.cpp
    TARGET := /usr/local/bin/ter
endif

default:
	clang++ $(SOURCE) -o $(TARGET) -std=c++11