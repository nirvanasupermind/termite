#include <string>
#include <memory>
#include <map>

#include "static_type.h"
namespace anthill {
    StaticType::StaticType(const BasicType& basic_type, int pointer_levels, const std::vector<std::shared_ptr<StaticType> >& arg_types)
        : basic_type(basic_type), pointer_levels(pointer_levels), arg_types(arg_types) {
        
    }

    std::string StaticType::to_str() const {
        std::string result = "void";
        if(basic_type == BasicType::CHAR) {
            result = "char";
        } else if(basic_type == BasicType::INT) {
            result = "int";
        } 

        for(int i = 0; i < pointer_levels; i++) {
            result = result + "*";
        }

        if(arg_types.size()) {
            result = result + "(";
            for(int i = 0; i < arg_types.size(); i++) {
                result = result + arg_types.at(i)->to_str();
                if(i == arg_types.size() - 1) {
                    result = result + ")";
                } else {
                    result = result + ",";
                }
            }   
        }

        return result;
    }
}

