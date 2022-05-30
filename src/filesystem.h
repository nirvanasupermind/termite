#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include <string>
#include <vector>
#include <map>
#include <memory>

#include "tryte.h"

namespace termite
{
    class Directory;

    class Diskable: public std::enable_shared_from_this<Diskable>
    {
    public:
        std::string name;
        std::shared_ptr<Directory> parent;

        Diskable() = default;
        Diskable(const std::string &name);
        Diskable(const std::string &name, std::shared_ptr<Directory> parent);

        void addToPool();
        
        std::string path() const;

        static std::map<std::string, std::shared_ptr<Diskable> > pool;
    };

    class Directory: public Diskable
    {
    public:
        using Diskable::Diskable;
    };

    class File: public Diskable
    {
    public:
        using Diskable::Diskable;

        std::vector<Tryte> data;

        File(const std::string &name, std::vector<Tryte> data);
        File(const std::string &name, std::vector<Tryte> data, std::shared_ptr<Directory> parent);
    };
}

#endif