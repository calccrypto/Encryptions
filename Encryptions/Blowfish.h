#ifndef __BLOWFISH__
#define __BLOWFISH__

#include <algorithm>

#include "../common/includes.h"
#include "SymAlg.h"

#include "Blowfish_Const.h"

class Blowfish : public SymAlg{
    private:
        bool settingkey;
        uint32_t p[18], sbox[4][512];        //Taken from a C file from the Blowfish site
        uint32_t f(const uint32_t & left);
        std::string run(const std::string & data);

    public:
        Blowfish();
        Blowfish(const std::string & KEY);
        void setkey(const std::string & KEY);
        std::string encrypt(const std::string & DATA);
        std::string decrypt(const std::string & DATA);
        unsigned int blocksize() const;
};
#endif
