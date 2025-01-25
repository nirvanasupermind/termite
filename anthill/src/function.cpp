#include <cinttypes>
#include "static_type.h"
#include "function.h"

namespace anthill {
    Function::Function(const StaticType& type)
        : type(type), var_counter(0)  {
    }
} // namespace anthill