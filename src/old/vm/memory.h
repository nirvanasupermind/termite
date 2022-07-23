#ifndef MEMORY_H
#define MEMORY_H
#include <string>
#include <array>

#include "../core/tryte.h"

namespace termite
{
    const int mem_size = 729;

    // Represents the random-access memory of the virtual machine, 
    // implemented as a thin wrapper around an STL array.
    // The memory contains 3^6 = 729 trytes of data, each uniquely addressed by a tryte.

    class Memory 
    {
    protected:
        std::array<Tryte, mem_size> data;
    public:
        Memory() = default;

        Tryte load(const Tryte &addr) const;

        void store(const Tryte &addr, const Tryte &val);
    };
} // namespace termite

#endif