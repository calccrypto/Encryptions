#ifndef __CAST256__
#define __CAST256__

#include <algorithm>
#include <vector>

#include "../common/cryptomath.h"
#include "../common/includes.h"
#include "SymAlg.h"

#include "CAST_Const.h"

class CAST256 : public SymAlg{
    private:
        uint32_t A, B, C, D, a, b, c, d, e, f, g, h;
        std::vector <std::vector <uint8_t> > Kr, Tr;
        std::vector <std::vector <uint32_t> > Km, Tm;
        uint32_t F1(const uint32_t Data, const uint32_t Kmi, const uint8_t Kri);
        uint32_t F2(const uint32_t Data, const uint32_t Kmi, const uint8_t Kri);
        uint32_t F3(const uint32_t Data, const uint32_t Kmi, const uint8_t Kri);
        void W(const uint8_t i);
        std::vector <uint8_t> kr();
        std::vector <uint32_t> km();
        void Q(const uint8_t & i);
        void QBAR(const uint8_t & i);
        std::string run(const std::string & data);

    public:
        CAST256();
        CAST256(const std::string & KEY);
        void setkey(std::string KEY);
        std::string encrypt(const std::string & DATA);
        std::string decrypt(const std::string & DATA);
        unsigned int blocksize() const;
};
#endif
