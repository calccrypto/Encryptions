#ifndef __CAST128__
#define __CAST128__

#include "../common/cryptomath.h"
#include "../common/includes.h"
#include "SymAlg.h"

#include "CAST_Const.h"
#include "CAST128_Const.h"

class CAST128 : public SymAlg{
    private:
        uint8_t rounds, kr[16];
        uint32_t km[16];
        uint32_t F(const uint8_t & round, const uint32_t & D, const uint32_t & Kmi, const uint8_t & Kri);
        std::string run(const std::string & data, const uint8_t start, const uint8_t stop, const uint8_t step);

    public:
        CAST128();
        CAST128(const std::string & KEY);
        void setkey(std::string KEY);
        std::string encrypt(const std::string & DATA);
        std::string decrypt(const std::string & DATA);
        unsigned int blocksize() const;
};
#endif
