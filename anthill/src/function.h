#ifndef FUNCTION_H
#define FUNCTION_H

#include <cinttypes>
#include <string>
#include <memory>
#include <map>
#include "static_type.h"

namespace anthill {
    class Function {
    public:
        StaticType type;
        int32_t var_counter = 0;
        Function(const StaticType& type);
    };
} // namespace anthill

#endif 