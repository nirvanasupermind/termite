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
        StaticType();
        StaticType(BasicType basic_type, int pointer_levels = 0);
        std::string str() const;
        int8_t size() const;
    };

} // namespace anthill

#endif // STATIC_TYPE_H