#include <iostream>
#include <string>
#include <vector>

#include "os.h"

namespace termite
{
    void OS::executeCommand(const std::vector<std::string> &command)
    {
        std::string tag = command.at(0);

        if(tag == "test")
        {
            std::cout << "test" << '\n';
            return;
        }
        
        if(tag == "exit")
        {
            std::exit(0);
            return;
        }

    }
}