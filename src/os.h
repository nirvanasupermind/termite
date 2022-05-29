#ifndef OS_H
#define OS_H

#include <iostream>
#include <string>
#include <vector>

#include "tryte.h"
#include "word.h"
#include "cpu.h"

namespace termite
{
    class OS
    {
    public:
        CPU cpu;

        OS() = default;

        void executeCommand(const std::vector<std::string> &command);
    };
}

#endif