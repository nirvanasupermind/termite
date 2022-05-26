#ifndef WORD_H
#define WORD_H

#include <string>

#include "tryte.h"

namespace termite
{
    /**
     * @brief 
     * A word in stack-based programs executed by the virtual CPU.
     * Contains 2 trytes, the "hi" tryte representing the opcode, and the "lo" tryte representing any other information.
     */
    class Word
    {
    public:
        Tryte hi; 
        Tryte lo;

        // Word set to 0
        Word() = default;
                
        // Word set using hi and lo tryte
        Word(const Tryte &hi, const Tryte &lo);

        // Word set using string
        Word(const std::string &str);
   
        // String representation for debugging purposes
        std::string str() const;
    };
}

#endif