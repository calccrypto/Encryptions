#include "error.h"
#include "cryptomath.h"
#include "SymAlg.h"

#ifndef __GOST__
#define __GOST__

#include "GOST_Const.h"

// GOST 28147-89
class GOST : public SymAlg{
    private:
        uint8_t k[8][16];
        uint32_t X[8], N[6], C1, C2;
        uint32_t CM1(uint32_t a, uint32_t b);
        uint32_t CM2(uint32_t a, uint32_t b);
//        uint32_t CM3(uint32_t a, uint32_t b){return (uint32_t) (a + b);}
//        uint32_t CM4(uint32_t a, uint32_t b){return (uint32_t) (a + b) % mod32;}
//        uint32_t CM5(uint32_t a, uint32_t b){return (uint32_t) (a ^ b);}
        std::string reverse(std::string & in);
        uint32_t sub(uint32_t in);

    public:
        GOST();
        GOST(std::string KEY, const uint8_t sbox[8][16]);
        void setkey(std::string KEY, const uint8_t sbox[8][16]);
        std::string encrypt(std::string DATA);
        std::string decrypt(std::string DATA);
        unsigned int blocksize();
};
#endif
