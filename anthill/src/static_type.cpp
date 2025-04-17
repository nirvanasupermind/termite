#include <string>
#include <memory>
#include <map>

#include "static_type.h"
namespace anthill {
    BasicType str_to_basic_type(const std::string& str) {
        if(str == "void") {
            return BasicType::VOID;
        } else if(str == "int") {
            return BasicType::INT;
        } else {
            return BasicType::CHAR;
        }
    }
    
    NonFuncType::NonFuncType(const BasicType& basic_type, int pointer_levels)
        : basic_type(basic_type), pointer_levels(pointer_levels) {

    }

    bool NonFuncType::is_func() const {
        return false;
    }

    std::string NonFuncType::to_str() const {
        std::string result = "void";
        if (basic_type == BasicType::CHAR) {
            result = "char";
        }
        else if (basic_type == BasicType::INT) {
            result = "int";
        }

        for (int i = 0; i < pointer_levels; i++) {
            result = result + "*";
        }

        // if(arg_types.size()) {
        //     result = result + "(";
        //     for(int i = 0; i < arg_types.size(); i++) {
        //         result = result + arg_types.at(i)->to_str();
        //         if(i == arg_types.size() - 1) {
        //             result = result + ")";
        //         } else {
        //             result = result + ",";
        //         }
        //     }   
        // }

        return result;
    }

    int NonFuncType::size() const {
        if(basic_type == BasicType::CHAR && pointer_levels == 0) {
            return 1;
        } else {
            return 2;
        }
    }

    std::shared_ptr<NonFuncType> NonFuncType::parse_type(const std::string& str) {
        BasicType basic_type;
        if(str[0] == 'c' && str[1] == 'h' && str[2] == 'a' && str[3] == 'r') {
            basic_type = BasicType::INT;
        } else {
            basic_type = BasicType::INT;
        }
        int pointer_levels = 0;
        for(int i = 2; i < str.size(); i++) {
            if(str[i] == '*') {
                pointer_levels++;
            };
        }
        return std::make_shared<NonFuncType>(NonFuncType(basic_type, pointer_levels));
    }
    
    FuncType::FuncType(const std::shared_ptr<NonFuncType>& return_type, const std::vector<std::shared_ptr<NonFuncType> >& arg_types)
        : return_type(return_type), arg_types(arg_types) {

    }

    bool FuncType::is_func() const {
        return true;
    }

    std::string FuncType::to_str() const {
        std::string result = return_type->to_str();
        result = result + "(";
        for (int i = 0; i < arg_types.size(); i++) {
            result = result + arg_types.at(i)->to_str();
            if (i == arg_types.size() - 1) {
                result = result + ")";
            }
            else {
                result = result + ",";
            }
        }


        return result;
    }
}

