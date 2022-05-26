#ifndef DECODER_H
#define DECODER_H

#include <string>
#include <exception>

#include "tryte.h"
#include "word.h"
#include "instr.h"

namespace termite
{
    // Words executed by the virtual CPU contain two trytes, one for the 
    class DecodeError : public std::exception
    {
    public:
        std::string msg;

        DecodeError(std::string msg)
            : msg(msg)
        {
        }

        virtual ~DecodeError() noexcept {}

        const char *what() const noexcept;
    };

    InstrOp decodeOp(const Tryte &op);

    Instr decodeInstr(const Word &instr);
}

#endif