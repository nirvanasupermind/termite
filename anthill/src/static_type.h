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
        StaticType(const BasicType& basic_type = BasicType::VOID, int pointer_levels = 0);
        std::string to_str() const;
    };
}

#endif