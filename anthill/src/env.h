#ifndef ENV_H
#define ENV_H

#include <string>
#include <vector>
#include <memory>
#include <cstdint>
#include <map>
#include "static_type.h"
#include "func.h"

namespace anthill {
   class Env {
   public:
        std::map<std::string, StaticType> var_types;
        std::map<std::string, int32_t> var_offsets;
        std::map<std::string, Func> funcs;
        std::shared_ptr<Env> parent_env;
        std::shared_ptr<Func> parent_func;
        Env(const std::shared_ptr<Env>& parent_env, const std::shared_ptr<Func>& parent_func);
        StaticType get_type(const std::string& name);
        int32_t get_offset(const std::string& name);
   };

} // namespace anthill

#endif