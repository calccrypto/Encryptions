#include <vector>

#include "error.h"
#include "integer.h"
#include "cryptomath.h"
#include "SymAlg.h"

#ifndef __CAMELLIA__
#define __CAMELLIA__

#include "Camellia_Const.h"

class Camellia : public SymAlg{
    // Camellia is a CRYPTmetric key block cipher developed jointly in 2000 by
    // world top class encryption researchers at NTT and Mitsubishi Electric
    // Corporation. See:http://info.isl.ntt.co.jp/crypt/eng/camellia/index.html

    private:
        uint16_t size;
        std::vector <uint64_t> keys;
        unsigned int SBOX(uint8_t s, uint8_t value);
        uint64_t FL(uint64_t & FL_IN, uint64_t & KE);
        uint64_t FLINV(uint64_t & FLINV_IN, uint64_t & KE);
        uint64_t F(uint64_t & F_IN, const uint64_t & KE);
        std::string run(std::string & data);

    public:
        Camellia();
        Camellia(std::string KEY);
        void setkey(std::string KEY);
        std::string encrypt(std::string DATA);
        std::string decrypt(std::string DATA);
        unsigned int blocksize();
};
#endif
