#include <iostream>
#include <string>
#include "error.h"

namespace anthill {
    void cleanup() {
        
    }

    void error(const std::string& file, int line, const std::string& msg) {
        std::cerr << "error: " << file << ":" << line << ": " << msg << '\n';
        if(++error_count > 10) {
            error_count = 0;
            fatal(file, line, "too many errors");
        }
    }

    void fatal(const std::string& file, int line, const std::string& msg) {
        error(file, line, msg);
        error(file, line, "fatal error, stop");
        std::exit(EXIT_FAILURE);
    }
}