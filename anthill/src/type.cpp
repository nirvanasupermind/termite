#include <string>
#include <memory>
#include <map>

#include "type.h"
namespace anthill {
    Type::Type(const BasicType& basic_type, int pointer_levels)
        : basic_type(basic_type), pointer_levels(pointer_levels) {
        
    }

    std::string Type::to_str() const {
        std::string result = "void";
        if(basic_type == BasicType::CHAR) {
            result = "char";
        } else if(basic_type == BasicType::INT) {
            result = "int";
        } 

        for(int i = 0; i < pointer_levels; i++) {
            result = result + "*";
        }

        return result;
    }
}

