#ifndef DECODER_H
#define DECODER_H

#include <string>

#include "tryte.h"
#include "word.h"
#include "op.h"

namespace termite
{
    Op decode_op(const Tryte &opcode);
} // namespace termite

#endif