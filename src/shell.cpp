#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <utility>

#include "shell.h"
#include "tryte.h"
#include "word.h"
#include "cpu.h"
#include "filesystem.h"
#include "util.h"

namespace termite
{
    Shell::Shell()
        : rootDir(std::shared_ptr<Directory>(new Directory(""))), currentDir(rootDir)
    {
        rootDir->addToPool();
    }

    void Shell::executeCommand(const std::vector<std::string> &command)
    {
        std::string tag = command.at(0);


        if(tag == "exit")
        {
            std::exit(0);
            return;
        }

        if(tag == "cd")
        {
            std::string relativePath = command.at(1);

            std::string path = absolutePath(relativePath);

            currentDir = getDir(path);
            return;
        }
        
        if(tag == "pwd")
        {
            std::cout << currentDir->path() << '\n';

            return;
        }

        if(tag == "mkdir")
        {
            std::string relativePath = command.at(1);

            std::string path = absolutePath(relativePath);
        
            if (checkDiskable(path))
            {
                throw std::string("file exists: " + relativePath);
            }

            std::vector<std::string> splitPath = splitString(path, '/');
            
            std::vector<std::string> splitParentPath(splitPath.begin(), splitPath.end() - 1);
            std::string parentPath = joinVec(splitParentPath, '/');

            std::string dirName = splitPath.back();

            std::shared_ptr<Directory> dir(new Directory(dirName, getDir(parentPath)));

            dir->addToPool();

            return;
        }

        if(tag == "ls")
        {
            for(const auto pair : Diskable::pool)
            {   
                std::shared_ptr<Diskable> diskable = pair.second;

                if(diskable->parent == currentDir)
                {
                    std::string diskableName = splitString(diskable->path(), '/').back();
                    std::cout << diskableName << '\t';
                }                
            }

            std::cout << '\n';

            return;
        }

        throw std::string("command not found: " + tag);
        return;
    }

    std::shared_ptr<Directory> Shell::getDir(const std::string &path) const
    {
        try
        {
            std::shared_ptr<Diskable> diskable = Diskable::pool.at(path);

            std::shared_ptr<Directory> dir = std::static_pointer_cast<Directory>(diskable);
            
            if(!dir)
            {
                throw std::string("not a directory: " +path);
                return std::shared_ptr<Directory>();     
            }

            return dir;
        } 
        catch(const std::exception &e)
        {
            throw std::string("no such file or directory: " +path);
            return std::shared_ptr<Directory>();
        }
    }


    bool Shell::checkDiskable(const std::string &path) const
    {
        try
        {
            std::shared_ptr<Diskable> diskable = Diskable::pool.at(path);

            std::shared_ptr<Directory> dir = std::static_pointer_cast<Directory>(diskable);
            
            return true;
        } 
        catch(const std::exception &e)
        {
            return false;
        }
    }

    bool Shell::checkDir(const std::string &path) const
    {
        try
        {
            std::shared_ptr<Diskable> diskable = Diskable::pool.at(path);

            std::shared_ptr<Directory> dir = std::static_pointer_cast<Directory>(diskable);
            
            if(!dir)
            {
                return false;
            }

            return true;
        } 
        catch(const std::exception &e)
        {
            return false;
        }
    }

    bool Shell::checkFile(const std::string &path) const
    {
        try
        {
            std::shared_ptr<Diskable> diskable = Diskable::pool.at(path);

            std::shared_ptr<File> file = std::static_pointer_cast<File>(diskable);
            
            if(!file)
            {
                return false;
            }

            return true;
        } 
        catch(const std::exception &e)
        {
            return false;
        }
    }

    std::string Shell::absolutePath(const std::string &path) const
    {
        if(path.at(0) == '/')
        {
            return path;
        }

        if(currentDir->path() == "/")
        {
            return "/" + path;
        }

        return currentDir->path() + "/" + path;
    }
}