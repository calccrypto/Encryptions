#include "error.h"
#include "SymAlg.h"

#ifndef __SKIPJACK__
#define __SKIPJACK__

#include "Skipjack_Const.h"

class Skipjack : public SymAlg{
    private:
        std::string key;
        uint16_t G_e(uint16_t quarter, uint32_t fourkeys);
        void A(uint16_t & w1, uint16_t & w2, uint16_t & w3, uint16_t & w4, uint16_t i);
        void B(uint16_t & w1, uint16_t & w2, uint16_t & w3, uint16_t & w4, uint16_t i);
        uint16_t G_d(uint16_t quarter, uint32_t fourkeys);
        void invA(uint16_t & w1, uint16_t & w2, uint16_t & w3, uint16_t & w4, uint16_t i);
        void invB(uint16_t & w1, uint16_t & w2, uint16_t & w3, uint16_t & w4, uint16_t i);

    public:
        Skipjack();
        Skipjack(std::string KEY);
        void setkey(std::string KEY);
        std::string encrypt(std::string DATA);
        std::string decrypt(std::string DATA);
        unsigned int blocksize();
};
#endif
