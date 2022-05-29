#ifndef DECODER_H
#define DECODER_H

#include <string>
#include <exception>

#include "tryte.h"
#include "word.h"
#include "instr.h"

namespace termite
{
    InstrOp decodeOp(const Tryte &op);

    Instr decodeInstr(const Word &instr);
}

#endif