// Output Feedback

#include "includes.h"
#include "integer.h"
#include "SymAlg.h"

#ifndef __OFB__
#define __OFB__
class OFB{
    private:
        SymAlg * algo;
        std::string const_IV;
        uint8_t blocksize;

    public:
        OFB(SymAlg * instance, std::string iv = "");
        std::string encrypt(std::string data);
        std::string decrypt(std::string data);
};
#endif
