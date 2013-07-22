#include <vector>

#include "error.h"
#include "integer.h"
#include "cryptomath.h"
#include "SymAlg.h"

#ifndef __RC6__
#define __RC6__

#include "RC_PQ.h"

class RC6 : public SymAlg{
    private:
        unsigned int w, r, b, lgw;
        std::vector <uint32_t> S;
        integer mod;

    public:
        RC6();
        RC6(std::string KEY, const unsigned int & W = 32, const unsigned int & R = 20);
        void setkey(std::string KEY, const unsigned int & W = 32, const unsigned int & R = 20);
        std::string encrypt(std::string DATA);
        std::string decrypt(std::string DATA);
        unsigned int blocksize();
};
#endif
