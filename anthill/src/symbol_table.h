#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <string>
#include <memory>
#include <map>

#include "token.h"
#include "type.h"

namespace anthill {
    class SymbolTable {
    public:
        std::shared_ptr<SymbolTable> parent;
        std::map<std::string, Type> record;
        SymbolTable(const std::shared_ptr<SymbolTable>& parent);
        bool has(const std::string& name);
        Type get(const std::string& name);
        void def(const std::string& name, const Type& type);
        void set(const std::string& name, const Type& type);
    };
}

#endif