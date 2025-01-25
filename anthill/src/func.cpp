#include <cinttypes>
#include "static_type.h"
#include "func.h"

namespace anthill {
    Func::Func(const StaticType& return_type, const std::vector<StaticType>& arg_types)
        : return_type(return_type), arg_types(arg_types), var_counter(0)  {
    }
} // namespace anthill