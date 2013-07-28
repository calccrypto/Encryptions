#include "../common/cryptomath.h"
#include "../common/integer.h"
#include "error.h"
#include "SymAlg.h"

#ifndef __SEED__
#define __SEED__

#include "SEED_Const.h"

class SEED : public SymAlg{
    private:
        std::string mode;
        std::pair <uint32_t, uint32_t> k[16];
        uint32_t G(uint32_t X);
        uint64_t F(uint64_t & right, std::pair <uint32_t, uint32_t> & K);
        std::string run(std::string & data);

    public:
        SEED();
        SEED(std::string KEY);
        void setkey(std::string KEY);
        std::string encrypt(std::string DATA);
        std::string decrypt(std::string DATA);
        unsigned int blocksize();
};
#endif
