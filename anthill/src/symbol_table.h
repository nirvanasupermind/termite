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
        std::map<std::string, std::shared_ptr<StaticType> > types;
        std::map<std::string, std::string> addrs;
        SymbolTable();
        SymbolTable(const std::shared_ptr<SymbolTable>& parent);
        bool has(const std::string& name);
        std::shared_ptr<StaticType> get_type(const std::string& name);
        void def_type(const std::string& name, const std::shared_ptr<StaticType>& type);
        std::string get_addr(const std::string& name);
        void def_addr(const std::string& name, const std::string& addr);
    };

}

#endif