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
        std::map<std::string, std::shared_ptr<StaticType> > variables;
        SymbolTable();
        SymbolTable(const std::shared_ptr<SymbolTable>& parent);
        bool has(const std::string& name);
        std::shared_ptr<StaticType> get(const std::string& name);
        void def(const std::string& name, const std::shared_ptr<StaticType>& type);
        void set(const std::string& name, const std::shared_ptr<StaticType>& type);
    };

}

#endif