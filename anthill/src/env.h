#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <cinttypes>
#include <string>
#include <memory>
#include <map>
#include "static_type.h"

namespace anthill {
    class Env {
    public:
        std::map<std::string, StaticType> types{};
        std::map<std::string, int32_t> addrs{};
        std::shared_ptr<Env> parent;
        Env();
        Env(const std::map<std::string, StaticType>& types, const  std::map<std::string, int32_t>& addrs, const std::shared_ptr<Env>& parent = nullptr);
        bool has(const std::string& name);
        StaticType get_type(const std::string& name);
        int32_t get_addr(const std::string& name);
        bool check_type(const std::string& name, const StaticType& intended_type);
    };
} // namespace anthill

#endif // ENV_H