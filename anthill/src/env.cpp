#include <cstdint>
#include <string>
#include <memory>
#include <map>

#include "static_type.h"
#include "env.h"

namespace anthill {
    Env::Env(const std::shared_ptr<Env>& parent_env, const std::shared_ptr<Func>& parent_func)
        : var_types({}), var_offsets({}), parent_env(parent_env), parent_func(parent_func)  {
    }
    
    // bool Env::has(const std::string& name) {
    //     if (var_types.count(name)) {
    //         return true;
    //     }
    //     else if (parent != nullptr) {
    //         return parent->has(name);
    //     }
    //     else {
    //         // Giving a proper error with line number can be handled by the compiler code in try-catches
    //         throw std::string("cannot find variable '" + name + "'");
    //     }        
    // }

    StaticType Env::get_type(const std::string& name) {
        if (var_types.count(name)) {
            return var_types.at(name);
        }
        else if (parent_env != nullptr) {
            return parent_env->get_type(name);
        }
        else {
            // Giving a proper error with line number can be handled by the compiler code in try-catches
            throw std::string("cannot find variable '" + name + "'");
        }
    }

    int32_t Env::get_offset(const std::string& name) {
        if (var_offsets.count(name)) {
            return var_offsets.at(name);
        }
        else if (parent_env != nullptr) {
            return parent_env->get_offset(name);
        }
        else {
            // Giving a proper error with line number can be handled by the compiler code in try-catches
            throw std::string("cannot find variable '" + name + "'");
        }
    }

    // bool Env::check_type(const std::string& name, const StaticType& intended_type) {
    //     StaticType actual_type = get_type(name);
    //     return actual_type.basic_type == intended_type.basic_type && actual_type.pointer_levels == intended_type.pointer_levels;
    // }
} // namespace anthill