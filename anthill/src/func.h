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
        StaticType return_type;
        std::vector<StaticType> arg_types;
        int32_t var_counter = 0;
        Func(const StaticType& return_type, const std::vector<StaticType>& arg_types);
    };
} // namespace anthill

#endif