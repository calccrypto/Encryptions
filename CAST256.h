#include <vector>

#include "error.h"
#include "cryptomath.h"
#include "SymAlg.h"

#ifndef __CAST256__
#define __CAST256__

#include "CAST_Const.h"

class CAST256 : public SymAlg{
    private:
        uint32_t A, B, C, D, a, b, c, d, e, f, g, h;
        std::vector <std::vector <uint8_t> > Kr, Tr;
        std::vector <std::vector <uint32_t> > Km, Tm;
        uint32_t F1(uint32_t Data, uint32_t Kmi, uint8_t Kri);
        uint32_t F2(uint32_t Data, uint32_t Kmi, uint8_t Kri);
        uint32_t F3(uint32_t Data, uint32_t Kmi, uint8_t Kri);
        void W(uint8_t i);
        std::vector <uint8_t> kr();
        std::vector <uint32_t> km();
        void Q(uint8_t & i);
        void QBAR(uint8_t & i);
        std::string run(std::string & data);

    public:
        CAST256();
        CAST256(std::string KEY);
        void setkey(std::string KEY);
        std::string encrypt(std::string DATA);
        std::string decrypt(std::string DATA);
        unsigned int blocksize();
};
#endif
