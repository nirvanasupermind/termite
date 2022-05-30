#include <iostream>
#include <vector>

#include "shell.h"
#include "util.h"
// #include "word.h"
// #include "cpu.h"

int main()
{
    std::cout << "Termite version 0.0" << '\n';
    std::cout << "Cpyright (c) 2022 nirvanasupermind" << "\n\n";

    termite::Shell shell;

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
            shell.executeCommand(command);
        }
        catch(const std::string &e)
        {
            std::cerr << e << '\n';
            // return 0;
        }
    }

    return 0;
}