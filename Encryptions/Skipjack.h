#include "../common/includes.h"
#include "SymAlg.h"

#ifndef __SKIPJACK__
#define __SKIPJACK__

#include "Skipjack_Const.h"

class Skipjack : public SymAlg{
    private:
        std::string key;
        uint16_t G_e(const uint16_t quarter, const uint32_t fourkeys);
        void A(uint16_t & w1, uint16_t & w2, uint16_t & w3, uint16_t & w4, const uint16_t i);
        void B(uint16_t & w1, uint16_t & w2, uint16_t & w3, uint16_t & w4, const uint16_t i);
        uint16_t G_d(const uint16_t quarter, const uint32_t fourkeys);
        void invA(uint16_t & w1, uint16_t & w2, uint16_t & w3, uint16_t & w4, const uint16_t i);
        void invB(uint16_t & w1, uint16_t & w2, uint16_t & w3, uint16_t & w4, const uint16_t i);

    public:
        Skipjack();
        Skipjack(const std::string & KEY);
        void setkey(const std::string & KEY);
        std::string encrypt(const std::string & DATA);
        std::string decrypt(const std::string & DATA);
        unsigned int blocksize();
};
#endif
