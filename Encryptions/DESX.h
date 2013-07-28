#include "error.h"
#include "SymAlg.h"

#ifndef __DESX__
#define __DESX__

#include "DES.h"

class DESX : public SymAlg{
    private:
        DES des;

    public:
        DESX();

        DESX(std::string & KEY, std::string & KEY2);
        std::string encrypt(std::string & data, std::string & KEY3);
        std::string decrypt(std::string & data, std::string & KEY3);
        unsigned int blocksize();
};
#endif
