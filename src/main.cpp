#include <iostream>
#include <vector>

#include "os.h"
#include "util.h"

int main()
{
    termite::OS os;

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

        std::vector<std::string> command = termite::splitString(inp, ' ');

        try
        {
            os.executeCommand(command);
        }
        catch(const std::string &e)
        {
            std::cerr << e << '\n';
            return 0;
        }
    }

    return 0;
}