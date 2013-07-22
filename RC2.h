#include "error.h"
#include "cryptomath.h"
#include "SymAlg.h"

#ifndef __RC2__
#define __RC2__

#include "RC2_Const.h"

class RC2 : public SymAlg{
    private:
        uint16_t K[64], R[4];
        uint32_t T1;
        void mix(uint8_t j, uint8_t i, uint8_t s);
        void mash(uint8_t i);
        void r_mix(uint8_t j, uint8_t i, uint8_t s);
        void r_mash(uint8_t i);

    public:
        RC2();
        RC2(std::string & KEY, uint32_t t1 = 64);
        void setkey(std::string KEY);
        std::string encrypt(std::string DATA);
        std::string decrypt(std::string DATA);
        unsigned int blocksize();
};
#endif
