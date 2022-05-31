#include <iostream>
#include <vector>

#include "os.h"
#include "util.h"
// #include "word.h"
// #include "cpu.h"

int main()
{
    std::cout << "Termite version 0.0" << '\n';
    std::cout << "Copyright (c) 2022 nirvanasupermind" << '\n';
    std::cout << "Licensed under the MIT License" << "\n\n";

    termite::OS os;

    os.addSystemFiles();

    while (true)
    {
        std::string inp;
        std::cout << "$ ";
        std::getline(std::cin, inp);

        if (std::cin.bad())
        {
            std::cerr << "IO error\n";
            break;
        }
        else if (std::cin.eof())
        {
            break;
        }

        termite::trim(inp);
        
        std::vector<std::string> command = termite::splitString(inp, ' ');
        
        if(command.size() == 0 || command.front() == "")
        {
            continue;
        }

        try
        {
            os.executeCommand(command);
        }
        catch(const std::string &e)
        {
            std::cerr << e << '\n';
            // return 0;
        }
        catch(const std::out_of_range &e)
        {
            std::cerr << "encountered std::out_of_range: " << e.what() << ", you may be missing an argument to a command" << '\n';
        }
    }

    return 0;
}