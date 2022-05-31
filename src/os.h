#ifndef SHELL_H
#define SHELL_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "tryte.h"
#include "word.h"
#include "cpu.h"
#include "filesystem.h"

namespace termite
{
    class OS
    {
    public:
        CPU cpu;

        std::shared_ptr<Directory> rootDir;

        std::shared_ptr<Directory> currentDir;

        OS();

        void addSystemFiles();

        void executeCommand(const std::vector<std::string> &command);

        void runExecutable(const std::vector<Tryte> &exe);

        std::shared_ptr<Directory> getDir(const std::string &path) const;

        std::shared_ptr<File> getFile(const std::string &path) const;

        bool checkDiskable(const std::string &path) const;

        bool checkDir(const std::string &path) const;

        bool checkFile(const std::string &path) const;

        std::string absolutePath(const std::string &path) const;

    };
}

#endif