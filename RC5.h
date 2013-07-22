#include <vector>

#include "error.h"
#include "cryptomath.h"
#include "SymAlg.h"

#ifndef __RC5__
#define __RC5__

#include "RC_PQ.h"

class RC5 : public SymAlg{
    private:
        uint64_t w, r, b;
        uint64_t mod;
        std::vector <uint64_t> S;

    public:
        RC5();
        RC5(std::string KEY, const uint64_t & W = 32, const uint64_t & R = 12, const uint64_t & B = 16);
        void setkey(std::string KEY, const uint64_t & W = 32, const uint64_t & R = 12, const uint64_t & B = 16);
        std::string encrypt(std::string DATA);
        std::string decrypt(std::string DATA);
        unsigned int blocksize();
};
#endif
