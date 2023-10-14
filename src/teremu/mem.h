#ifndef MEM_H
#define MEM_H

#include <vector>

#include "../core/tryte.h"
#include "../core/word.h"

namespace termite {
    class Mem {
    protected:
        std::vector<Tryte> data;
    public:
        static constexpr int MAX_MEM = 43046721;
        Mem();
        void initialize();
        Tryte get_tryte(const Word& addr) const;
        void set_tryte(const Word& addr, const Tryte& tryte);
        Word get_word(const Word& addr) const;
        void set_word(const Word& addr, const Word& word);
        void load_bct_file(const std::string& filename);
    };
} // namespace termite

#endif
