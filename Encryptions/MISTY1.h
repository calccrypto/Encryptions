#ifndef __MISTY1__
#define __MISTY1__

#include "../common/includes.h"
#include "SymAlg.h"

#include "MISTY1_Const.h"

class MISTY1 : public SymAlg{
    private:
        uint16_t EK[32];
        uint16_t FI(const uint16_t FI_IN, const uint16_t FI_KEY);
        uint32_t FO(const uint32_t FO_IN, const uint16_t k);
        uint32_t FL(const uint32_t FL_IN, const uint32_t k);
        uint32_t FLINV(const uint32_t FL_IN, const uint32_t k);

    public:
        MISTY1();
        MISTY1(const std::string & KEY);
        void setkey(const std::string & KEY);
        std::string encrypt(const std::string & DATA);
        std::string decrypt(const std::string & DATA);
        unsigned int blocksize() const;
};
#endif
