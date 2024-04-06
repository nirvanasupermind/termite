#include <string>
#include "static_type.h"

namespace anthill {
    StaticType::StaticType()
        : basic_type(BasicType::VOID), pointer_levels(0) {
    }

    StaticType::StaticType(BasicType basic_type, int pointer_levels)
        : basic_type(basic_type), pointer_levels(pointer_levels) {

    }
    
    std::string StaticType::str() const {
        std::string result;
        switch(basic_type) {
        case BasicType::VOID:
            result = "void";
            break;
        case BasicType::CHAR:
            result = "char";
            break;
        case BasicType::INT:
            result = "int";
            break;
        default:
            break;
        }
        for(int i = 0; i < pointer_levels; i++) {
            result += "*";
        }
        return result;
    }

    int8_t StaticType::size() const {
        if(basic_type == BasicType::CHAR && pointer_levels == 0) {
            return 1;
        } else {
            return 2;
        }
    }
}