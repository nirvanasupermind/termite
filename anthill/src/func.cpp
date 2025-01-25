#include <cinttypes>
#include "static_type.h"
#include "func.h"

namespace anthill {
    Func::Func(const StaticType& type)
        : type(type), var_counter(0)  {
    }
} // namespace anthill