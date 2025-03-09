#include <string>
#include <memory>
#include <map>

#include "token.h"
#include "static_type.h"
#include "symbol_table.h"


namespace anthill {
    SymbolTable::SymbolTable()
        : parent(std::shared_ptr<SymbolTable>()), variables({}) {

    }

    SymbolTable::SymbolTable(const std::shared_ptr<SymbolTable>& parent)
        : parent(parent), variables({}) {

    }

    bool SymbolTable::has(const std::string& name) {
        if (variables.count(name)) {
            return true;
        }
        else if (parent) {
            return parent->has(name);
        }
        else {
            return false;
        }
    }

    std::shared_ptr<StaticType> SymbolTable::get(const std::string& name) {
        if (variables.count(name)) {
            return variables.at(name);
        }
        else if (parent) {
            return parent->get(name);
        }
        else {
            throw std::string("cannot find variable '" + name + "'");
        }
    }

    void SymbolTable::def(const std::string& name, const std::shared_ptr<StaticType>& type) {
        if (parent->has(name)) {
            throw std::string("variable '" + name + "' already exists");
        }
        variables[name] = type;
    }

    void SymbolTable::set(const std::string& name, const std::shared_ptr<StaticType>& type) {
        if (parent->has(name)) {
            parent->set(name, type);
        }
        else {
            variables[name] = type;
        }
    }
}