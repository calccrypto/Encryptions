#include "error.h"
#include "SymAlg.h"

#ifndef __MISTY1__
#define __MISTY1__

#include "MISTY1_Const.h"

class MISTY1 : public SymAlg{
    private:
        uint16_t EK[32];
        uint16_t FI(uint16_t FI_IN, uint16_t FI_KEY);
        uint32_t FO(uint32_t FO_IN, uint16_t k);
        uint32_t FL(uint32_t FL_IN, uint32_t k);
        uint32_t FLINV(uint32_t FL_IN, uint32_t k);

    public:
        MISTY1();
        MISTY1(std::string KEY);
        void setkey(std::string KEY);
        std::string encrypt(std::string DATA);
        std::string decrypt(std::string DATA);
        unsigned int blocksize();
};
#endif
