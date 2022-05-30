#include <iostream>
#include <vector>

#include "shell.h"
#include "util.h"
// #include "word.h"
// #include "cpu.h"

int main()
{
    // cpu example:
    // termite::CPU cpu;
    
    // std::vector<termite::Word> program = {
    //     termite::Word("00000100001T"), // push 2 (1*3^1 - 1 * 3^0) to the stack
    //     termite::Word("00000100001T"), // push 2 (1*3^1 - 1 * 3^0) to the stack
    //     termite::Word("0001TT000000"), // pop top two trytes from the stack, then push their sum
    //     termite::Word("000011000001") // print top tryte from stack as a ternary number
    // };

    // cpu.executeProgram(program);

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