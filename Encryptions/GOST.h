#ifndef __GOST__
#define __GOST__

#include "../common/cryptomath.h"
#include "../common/includes.h"
#include "SymAlg.h"

#include "GOST_Const.h"

// GOST 28147-89
class GOST : public SymAlg{
    private:
        uint8_t k[8][16];
        uint32_t X[8], N[6], C1, C2;
        uint32_t CM1(const uint32_t a, const uint32_t b);
        uint32_t CM2(const uint32_t a, const uint32_t b);
//        uint32_t CM3(const uint32_t a, const uint32_t b){return static_cast <uint32_t> (a + b);}
//        uint32_t CM4(const uint32_t a, const uint32_t b){return static_cast <uint32_t> (a + b) % mod32;}
//        uint32_t CM5(const uint32_t a, const uint32_t b){return static_cast <uint32_t> (a ^ b);}
        uint32_t sub(uint32_t in);

    public:
        GOST();
        GOST(const std::string & KEY, const uint8_t sbox[8][16]);
        void setkey(const std::string & KEY, const uint8_t sbox[8][16]);
        std::string encrypt(const std::string & DATA);
        std::string decrypt(const std::string & DATA);
        unsigned int blocksize() const;
};
#endif
