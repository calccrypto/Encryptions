#ifndef __RC4__
#define __RC4__

#include <vector>

#include "SymAlg.h"

class RC4 : public SymAlg{
    private:
        uint8_t s_e[256], i_e, j_e,         // encryption SBox and "pointers"
                s_d[256], i_d, j_d;         // decryption SBox and "pointers"

        void ksa(const std::string & k);    // key scheduling algorithm
        int prga(const char mode);          // pseudo random generation algorithm

    public:
        RC4();
        RC4(const std::string & KEY);
        void setkey(const std::string & KEY);
        std::string encrypt(const std::string & DATA);
        std::string decrypt(const std::string & DATA);
        unsigned int blocksize() const;
};
#endif
