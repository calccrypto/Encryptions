#ifndef __RC4__
#define __RC4__

#include <vector>

#include "SymAlg.h"

class RC4 : public SymAlg{
    private:
        std::vector <uint8_t> key;
        uint8_t s[256], i_e, j_e, i_d, j_d;
        void ksa(std::vector <uint8_t> & key);
        int prga(uint8_t & i, uint8_t & j);

    public:
        RC4();
        RC4(const std::string & KEY);
        void setkey(const std::string & KEY);
        std::string encrypt(const std::string & DATA);
        std::string decrypt(const std::string & DATA);
        unsigned int blocksize() const;
};
#endif
