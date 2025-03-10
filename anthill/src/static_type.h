#ifndef STATIC_TYPE_H
#define STATIC_TYPE_H

#include <string>

namespace anthill {
    enum class BasicType {
        VOID,
        INT,
        CHAR
    };


    class StaticType {
    public:
        virtual bool is_func() const = 0;
        virtual std::string to_str() const = 0;
    };

    class NonFuncType : public StaticType {
    public:
        BasicType basic_type;
        int pointer_levels;
        NonFuncType(const BasicType& basic_type = BasicType::VOID, int pointer_levels = 0);
        bool is_func() const;
        std::string to_str() const;
    };

    class FuncType : public StaticType {
    public:
        std::shared_ptr<NonFuncType> return_type;
        std::vector<std::shared_ptr<NonFuncType> > arg_types;
        FuncType(const std::shared_ptr<NonFuncType>& return_type, const std::vector<std::shared_ptr<NonFuncType> >& arg_types);
        bool is_func() const;
        std::string to_str() const;
    };
}

#endif