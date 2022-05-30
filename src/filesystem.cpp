#include <string>
#include <vector>
#include <map>
#include <memory>

#include "tryte.h"
#include "filesystem.h"

namespace termite
{
    Diskable::Diskable(const std::string &name)
        : name(name), parent(std::shared_ptr<Directory>())
    {
    }
        
    Diskable::Diskable(const std::string &name, std::shared_ptr<Directory> parent)
        : name(name), parent(parent)
    {
    }

    void Diskable::addToPool()
    {
        Diskable::pool[path()] = shared_from_this();
    }

    std::string Diskable::path() const
    {
        if(!parent) 
        {
            return "/" + name;
        }

        std::string parentPath = parent->path();

        if(parentPath == "/")
        {
            return parentPath + name;
        }
    
        return parent->path() + "/" + name;
    }
        
    std::map<std::string, std::shared_ptr<Diskable> > Diskable::pool {};

    File::File(const std::string &name, std::vector<Tryte> data)
        : data(data)
    {
        this->name = name;
        this->parent = std::shared_ptr<Directory>();
        Diskable::pool[path()] = shared_from_this();
    }

    File::File(const std::string &name, std::vector<Tryte> data, std::shared_ptr<Directory> parent)
        : data(data)
    {
        this->name = name;
        this->parent = parent;
        Diskable::pool[path()] = shared_from_this();
    }

}