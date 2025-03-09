#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <memory>
#include <map>

#include "token.h"
#include "static_type.h"

namespace anthill {
    class SymbolTable {
    public:
        std::shared_ptr<SymbolTable> parent;
        std::map<std::string, StaticType> variables;
        std::map<std::string, std::vector<StaticType> > func_signatures;
        SymbolTable();
        SymbolTable(const std::shared_ptr<SymbolTable>& parent);
        bool has(const std::string& name);
        StaticType get(const std::string& name);
        void def(const std::string& name, const StaticType& type);
        void set(const std::string& name, const StaticType& type);
        bool has_func_signature(const std::string& name);
        std::vector<StaticType> get_func_signature(const std::string& name);
        void def_func_signature(const std::string& name, const std::vector<StaticType>& func_signature);

    };

}

#endif