#include "error.h"
#include "SymAlg.h"

#ifndef __XTEA__
#define __XTEA__
class XTEA : public SymAlg{
    private:
        uint32_t delta, cycles, total, key[4];

    public:
        XTEA();
        XTEA(const std::string & KEY, const uint8_t & ROUNDS = 64, const uint32_t & DELTA = 0x9e3779b9);
        void setkey(const std::string & KEY, const uint8_t & ROUNDS = 64, const uint32_t & DELTA = 0x9e3779b9);
        std::string encrypt(std::string DATA);
        std::string decrypt(std::string DATA);
        unsigned int blocksize();
};
#endif
