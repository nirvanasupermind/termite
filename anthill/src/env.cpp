#include <cinttypes>
#include <string>
#include <memory>
#include <map>

#include "static_type.h"
#include "env.h"

namespace anthill {
    Env::Env()
        : types({}), offsets({}), parent(std::shared_ptr<Env>()), func(std::shared_ptr<Function>())  {
    }
    
    bool Env::has(const std::string& name) {
        if (types.count(name)) {
            return true;
        }
        else if (parent != nullptr) {
            return parent->has(name);
        }
        else {
            // Giving a proper error with line number can be handled by the compiler code in try-catches
            throw std::string("cannot find variable '" + name + "'");
        }        
    }

    StaticType Env::get_type(const std::string& name) {
        if (types.count(name)) {
            return types.at(name);
        }
        else if (parent != nullptr) {
            return parent->get_type(name);
        }
        else {
            // Giving a proper error with line number can be handled by the compiler code in try-catches
            throw std::string("cannot find variable '" + name + "'");
        }
    }

    int32_t Env::get_offset(const std::string& name) {
        if (offsets.count(name)) {
            return offsets.at(name);
        }
        else if (parent != nullptr) {
            return parent->get_offset(name);
        }
        else {
            // Giving a proper error with line number can be handled by the compiler code in try-catches
            throw std::string("cannot find variable '" + name + "'");
        }
    }

    bool Env::check_type(const std::string& name, const StaticType& intended_type) {
        StaticType actual_type = get_type(name);
        return actual_type.basic_type == intended_type.basic_type && actual_type.pointer_levels == intended_type.pointer_levels;
    }
} // namespace anthill