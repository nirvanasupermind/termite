#ifndef STATIC_TYPE_H
#define STATIC_TYPE_H

#include <string>

namespace anthill {
    enum class BasicType {
        VOID,
        INT,
        CHAR
    };

    class StaticType {
    public:
        BasicType basic_type;
        int pointer_levels;
        std::vector<StaticType> func_arg_types{}; 
        StaticType();
        StaticType(BasicType basic_type, int pointer_levels = 0);
        StaticType(BasicType basic_type, int pointer_levels, const std::vector<StaticType>& func_arg_types);
        std::string str() const;
        int8_t size() const;
    };

} // namespace anthill

#endif // STATIC_TYPE_H