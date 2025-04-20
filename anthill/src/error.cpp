#include <iostream>
#include <string>
#include "error.h"

namespace anthill {
    // void cleanup() {
        
    // }

    void error(const std::string& file, int line, const std::string& msg) {
        throw std::string("error: " + file + ":" + std::to_string(line) + ": " + msg);
    }
}