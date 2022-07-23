#include <string>
#include <array>


#include "../core/tryte.h"
#include "./word.h"
#include "./memory.h"

namespace termite
{
    Tryte Memory::load(const Tryte &addr) const 
    {
        return data.at(addr.to_int());
    }

    void Memory::store(const Tryte &addr, const Tryte &val)
    {
        data[addr.to_int()] = val;
    }
} // namespace termite