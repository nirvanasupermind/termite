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

    StaticType SymbolTable::get(const std::string& name) {
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

    void SymbolTable::def(const std::string& name, const StaticType& type) {
        if (parent->has(name)) {
            throw std::string("variable '" + name + "' already exists");
        }
        variables[name] = type;
    }

    void SymbolTable::set(const std::string& name, const StaticType& type) {
        if (parent->has(name)) {
            parent->set(name, type);
        }
        else {
            variables[name] = type;
        }
    }

    bool SymbolTable::has_func_signature(const std::string& name) {
        if (func_signatures.count(name)) {
            return true;
        }
        else if (parent) {
            return parent->has_func_signature(name);
        }
        else {
            return false;
        }
    }

    std::vector<StaticType> SymbolTable::get_func_signature(const std::string& name) {
        if (func_signatures.count(name)) {
            return func_signatures.at(name);
        }
        else if (parent) {
            return parent->get_func_signature(name);
        }
        else {
            throw std::string("cannot find function '" + name + "'");
        }
    }

    void SymbolTable::def_func_signature(const std::string& name, const std::vector<StaticType>& func_signature) {
        if (parent->has(name)) {
            throw std::string("variable '" + name + "' already exists");
        }

        func_signatures[name] = func_signature;

    }
}