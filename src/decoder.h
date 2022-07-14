#ifndef DECODER_H
#define DECODER_H

#include <string>

#include "tryte.h"
#include "word.h"
#include "instr.h"

namespace termite
{
    Instr decode_instr(const Tryte &opcode);

} // namespace termite

#endif