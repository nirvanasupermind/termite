#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <cinttypes>
#include <string>
#include <memory>
#include <map>
#include "static_type.h"
#include "function.h"

namespace anthill {
    class Env {
    public:
        std::map<std::string, StaticType> types{};
        std::map<std::string, int32_t> offsets{};
        std::shared_ptr<Env> parent;
        std::shared_ptr<Function> func;
        Env();
        bool has(const std::string& name);
        StaticType get_type(const std::string& name);
        int32_t get_offset(const std::string& name);
        bool check_type(const std::string& name, const StaticType& intended_type);
    };
} // namespace anthill

#endif // ENV_H