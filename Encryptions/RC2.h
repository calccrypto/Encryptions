#include <vector>

#include "../common/cryptomath.h"
#include "../common/includes.h"
#include "SymAlg.h"

#ifndef __RC2__
#define __RC2__

#include "RC2_Const.h"

class RC2 : public SymAlg{
    private:
        uint16_t K[64], R[4];
        uint32_t T1;
        void mix(const uint8_t j, const uint8_t i, const uint8_t s);
        void mash(const uint8_t i);
        void r_mix(const uint8_t j, const uint8_t i, const uint8_t s);
        void r_mash(const uint8_t i);

    public:
        RC2();
        RC2(const std::string & KEY, const uint32_t & t1 = 64);
        void setkey(const std::string & KEY, const uint32_t & t1 = 64);
        std::string encrypt(const std::string & DATA);
        std::string decrypt(const std::string & DATA);
        unsigned int blocksize();
};
#endif
