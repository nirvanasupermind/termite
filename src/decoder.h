#ifndef DECODER_H
#define DECODER_H

#include <string>

#include "tryte.h"
#include "word.h"
#include "instr.h"

namespace termite
{
    InstrType decode_instr_type(const Tryte &tryte);

    Instr decode_instr(const Word &word);
} // namespace termite

#endif