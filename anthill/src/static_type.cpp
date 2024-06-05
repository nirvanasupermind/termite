#include <string>
#include "static_type.h"

namespace anthill {
    StaticType::StaticType()
        : basic_type(BasicType::VOID), pointer_levels(0) {
    }

    StaticType::StaticType(BasicType basic_type, int pointer_levels)
        : basic_type(basic_type), pointer_levels(pointer_levels) {

    }

    StaticType::StaticType(BasicType basic_type, int pointer_levels, const std::vector<StaticType>& func_arg_types)
        : basic_type(basic_type), pointer_levels(pointer_levels), func_arg_types(func_arg_types) {

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

        if(func_arg_types.size() > 0) {
            result += "(";
            for(int i = 0; i < func_arg_types.size(); i++) {
                result += func_arg_types.at(i).str() + ", ";
            }
            result = result.substr(0, result.size() - 2) + ")";
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