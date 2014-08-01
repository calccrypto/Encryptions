#ifndef __CAMELLIA__
#define __CAMELLIA__

#include <algorithm>
#include <vector>

#include "../common/cryptomath.h"
#include "../common/includes.h"
#include "../common/integer.h"
#include "SymAlg.h"

#include "Camellia_Const.h"

class Camellia : public SymAlg{
    // Camellia is a CRYPTmetric key block cipher developed jointly in 2000 by
    // world top class encryption researchers at NTT and Mitsubishi Electric
    // Corporation. See:http://info.isl.ntt.co.jp/crypt/eng/camellia/index.html

    private:
        uint16_t keysize;
        std::vector <uint64_t> keys;
        unsigned int SBOX(const uint8_t s, const uint8_t value);
        uint64_t FL(const uint64_t & FL_IN, const uint64_t & KE);
        uint64_t FLINV(const uint64_t & FLINV_IN, const uint64_t & KE);
        uint64_t F(const uint64_t & F_IN, const uint64_t & KE);
        std::string run(const std::string & data);

    public:
        Camellia();
        Camellia(const std::string & KEY);
        void setkey(const std::string & KEY);
        std::string encrypt(const std::string & DATA);
        std::string decrypt(const std::string & DATA);
        unsigned int blocksize() const;
};
#endif
