#include "error.h"
#include "cryptomath.h"
#include "SymAlg.h"

#ifndef __CAST128__
#define __CAST128__

#include "CAST_Const.h"
#include "CAST128_Const.h"

class CAST128 : public SymAlg{
    private:
        uint8_t rounds, kr[16];
        uint32_t km[16];
        uint32_t F(uint8_t & round, uint32_t & D, uint32_t & Kmi, uint8_t & Kri);
        std::string run(std::string & data, uint8_t start, uint8_t stop, uint8_t step);

    public:
        CAST128();
        CAST128(std::string KEY);
        void setkey(std::string KEY);
        std::string encrypt(std::string DATA);
        std::string decrypt(std::string DATA);
        unsigned int blocksize();
};
#endif
