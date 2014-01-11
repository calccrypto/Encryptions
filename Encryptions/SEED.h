#ifndef __SEED__
#define __SEED__

#include <algorithm>

#include "../common/cryptomath.h"
#include "../common/includes.h"
#include "../common/integer.h"
#include "SymAlg.h"

#include "SEED_Const.h"

class SEED : public SymAlg{
    private:
        std::string mode;
        std::pair <uint32_t, uint32_t> k[16];
        uint32_t G(uint32_t X);
        uint64_t F(const uint64_t & right, const std::pair <uint32_t, uint32_t> & K);
        std::string run(const std::string & data);

    public:
        SEED();
        SEED(const std::string & KEY);
        void setkey(const std::string & KEY);
        std::string encrypt(const std::string & DATA);
        std::string decrypt(const std::string & DATA);
        unsigned int blocksize();
};
#endif
