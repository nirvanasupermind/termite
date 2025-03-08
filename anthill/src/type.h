#ifndef TYPE_H
#define TYPE_H

#include <string>

namespace anthill {
    enum class BasicType {
        INT,
        CHAR,
        VOID,
        ERROR
    };

    class Type {
    public:
        BasicType basic_type;
        int pointer_levels;
        Type(const BasicType& basic_type, int pointer_levels = 0);
        std::string to_str() const;
    };
}

#endif