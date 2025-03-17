#include <string>
#include <memory>
#include <map>

#include "token.h"
#include "static_type.h"
#include "symbol_table.h"


namespace anthill {
    SymbolTable::SymbolTable()
        : parent(std::shared_ptr<SymbolTable>()), types({}), addrs({}) {

    }

    SymbolTable::SymbolTable(const std::shared_ptr<SymbolTable>& parent)
        : parent(parent), types({}), addrs({}) {

    }

    bool SymbolTable::has(const std::string& name) {
        if (types.count(name)) {
            return true;
        }
        else if (parent) {
            return parent->has(name);
        }
        else {
            return false;
        }
    }

    std::shared_ptr<StaticType> SymbolTable::get_type(const std::string& name) {
        if (types.count(name)) {
            return types[name];
        }
        else if (parent) {
            return parent->get_type(name);
        }
        else {
            throw std::string("cannot find variable '" + name + "'");
        }
    }

    void SymbolTable::def_type(const std::string& name, const std::shared_ptr<StaticType>& type) {
        if (has(name)) {
            throw std::string("variable '" + name + "' already exists");
        } else {
            types[name] = type;
        }
    }


    int32_t SymbolTable::get_addr(const std::string& name) {
        if (addrs.count(name)) {
            return addrs[name];
        }
        else if (parent) {
            return parent->get_addr(name);
        }
        else {
            throw std::string("cannot find variable '" + name + "'");
        }
    }

    void SymbolTable::def_addr(const std::string& name, int32_t addr) {
        if (has(name)) {
            throw std::string("variable '" + name + "' already exists");
        } else {
            addrs[name] = addr;
        }
    }
}