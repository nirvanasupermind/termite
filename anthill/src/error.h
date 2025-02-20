#ifndef ERROR_H
#define ERROR_H

#include <string>

namespace anthill {
    static int error_count;
    void cleanup();
    void error(const std::string& file, int line, const std::string& msg);
    void fatal(const std::string& file, int line, const std::string& msg);
}

#endif