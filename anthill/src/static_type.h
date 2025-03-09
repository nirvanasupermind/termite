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
        std::vector<std::shared_ptr<StaticType> > arg_types;
        StaticType(const BasicType& basic_type = BasicType::VOID, int pointer_levels = 0, const std::vector<std::shared_ptr<StaticType> >& arg_types = {});
        std::string to_str() const;
    };
}

#endif