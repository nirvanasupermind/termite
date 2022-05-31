#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <utility>

#include "os.h"
#include "tryte.h"
#include "word.h"
#include "cpu.h"
#include "filesystem.h"
#include "util.h"
#include "text.h"
#include "decoder.h"

namespace termite
{
    OS::OS()
        : rootDir(std::shared_ptr<Directory>(new Directory(""))), currentDir(rootDir)
    {
        rootDir->addToPool();
    }

    void OS::addSystemFiles()
    {
        executeCommand({"mkdir", "/ter"});
        executeCommand({"touch", "/ter/test_file"});
        
        std::shared_ptr<File> testFile = getFile("/ter/test_file");
        testFile->data.push_back(termite::Tryte("000001"));
        testFile->data.push_back(termite::Tryte("000010"));
        testFile->data.push_back(termite::Tryte("000011"));
        testFile->data.push_back(termite::Tryte("000001"));
    }

    void OS::executeCommand(const std::vector<std::string> &command)
    {
        std::string tag = command.at(0);

        if(tag == "clear")
        {
            #ifdef _WIN32
                std::system("cls");
            #else
                std::system("clear");
            #endif

            return;        
        }

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



        if(tag == "touch")
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

            std::shared_ptr<File> file(new File(dirName, getDir(parentPath)));

            file->addToPool();

            return;
        }

        std::shared_ptr<File> exe = getFile("/ter/" + tag);

        runExecutable(exe->data);

        return;
    }

    void OS::runExecutable(const std::vector<Tryte> &exe) 
    {
        for(int i = 0; i < exe.size(); i += 2)
        {
            Word word(exe.at(i), exe.at(i + 1));

            Instr instr = decodeInstr(word);

            switch(instr.op)
            {
                case InstrOp::NOP:
                    // Do nothing
                    break;
                case InstrOp::PUSH:
                    cpu.push(instr.val);
                    break;
                case InstrOp::POP:
                    cpu.pop();
                    break;
                case InstrOp::SWAP:
                    cpu.swap();
                    break;
                case InstrOp::SYSCALL:
                    cpu.syscall(instr.val);
                    break;
                case InstrOp::ADD:
                    cpu.add();
                    break;
                case InstrOp::SUB:
                    cpu.sub();
                    break;
                case InstrOp::MUL:
                    cpu.mul();  
                    break;
                case InstrOp::NEG:
                    cpu.neg(); 
                    break; 
                case InstrOp::AND:
                    cpu.and_();  
                    break;
                case InstrOp::OR:
                    cpu.or_();
                    break;
                case InstrOp::XOR:
                    cpu.xor_();
                    break;
                case InstrOp::NOT:
                    cpu.not_();   
                    break;           
                default:
                    break;       
            } 
        }
    }
    std::shared_ptr<Directory> OS::getDir(const std::string &path) const
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

    std::shared_ptr<File> OS::getFile(const std::string &path) const
    {
        try
        {
            std::shared_ptr<Diskable> diskable = Diskable::pool.at(path);

            std::shared_ptr<File> file = std::static_pointer_cast<File>(diskable);
            
            if(!file)
            {
                throw std::string("not a file: " +path);
                return std::shared_ptr<File>();     
            }

            return file;
        } 
        catch(const std::exception &e)
        {
            throw std::string("no such file or directory: " +path);
            return std::shared_ptr<File>();
        }
    }


    bool OS::checkDiskable(const std::string &path) const
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

    bool OS::checkDir(const std::string &path) const
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

    bool OS::checkFile(const std::string &path) const
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

    std::string OS::absolutePath(const std::string &path) const
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