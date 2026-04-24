#include <string>
#include <memory>
#include <map>
#include <iostream>
#include "token.h"
#include "static_type.h"
#include "symbol_table.h"

namespace anthill {
    SymbolTable::SymbolTable()
        : parent(std::shared_ptr<SymbolTable>()), types(std::map<std::string, std::shared_ptr<StaticType> >({})), addrs(std::map<std::string, std::string>({})), is_func(false) {
std::isalpha(3);

    }

    SymbolTable::SymbolTable(const std::shared_ptr<SymbolTable>& parent)
        : parent(parent), types(std::map<std::string, std::shared_ptr<StaticType> >({})), addrs(std::map<std::string, std::string>({})), is_func(parent->is_func) {

    }

    bool SymbolTable::has(const std::string& name) {
        if (types.count(name)) {
            std::cout << "dbg24" << '\n';
            return true;
        }
        else if (parent) {
            std::cout << "dbg27" << '\n';
            return parent->has(name);
        }
        else {
            std::cout << "dbg32" << '\n';
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
        if (types.count(name)) {
            throw std::string("variable '" + name + "' already exists");
        } else {
            types[name] = type;
        }
    }

    std::string SymbolTable::get_addr(const std::string& name) {
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

    void SymbolTable::def_addr(const std::string& name, const std::string& addr) {
        std::cout << "dbg66" << '\n';
        // if (has(name)) {
        //     throw std::string("variable '" + name + "' already exists");
        // } else {
            addrs[name] = addr;
        // }
    }
}