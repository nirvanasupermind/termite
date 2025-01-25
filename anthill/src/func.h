#ifndef FUNC_H
#define FUNC_H

#include <cinttypes>
#include <string>
#include <memory>
#include <map>
#include "static_type.h"

namespace anthill {
    class Func {
    public:
        StaticType type;
        int32_t var_counter = 0;
        Func(const StaticType& type);
    };
} // namespace anthill

#endif