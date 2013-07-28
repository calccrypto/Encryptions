#include "error.h"
#include "SymAlg.h"

#ifndef __BLOWFISH__
#define __BLOWFISH__

#include "Blowfish_Const.h"

class Blowfish : public SymAlg{
    private:
        bool settingkey;
        uint32_t p[18], sbox[4][512];        //Taken from a C file from the Blowfish site
        uint32_t f(uint32_t & left);
        std::string run(std::string & data);

    public:
        Blowfish();
        Blowfish(std::string KEY);
        void setkey(std::string KEY);
        std::string encrypt(std::string DATA);
        std::string decrypt(std::string DATA);
        unsigned int blocksize();
};
#endif
