// Output Feedback
#ifndef __OFB__
#define __OFB__

#include "../common/includes.h"
#include "../common/integer.h"
#include "SymAlg.h"

class OFB{
    private:
        SymAlg * algo;
        std::string const_IV;
        uint8_t blocksize;

    public:
        OFB(SymAlg * instance, const std::string & iv = "");
        std::string encrypt(const std::string & data);
        std::string decrypt(const std::string & data);
};
#endif
