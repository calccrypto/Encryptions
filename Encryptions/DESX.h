#ifndef __DESX__
#define __DESX__

#include "../common/includes.h"
#include "SymAlg.h"

#include "DES.h"

class DESX : public SymAlg{
    private:
        DES des;
        std::string K1, K2;
        
    public:
        DESX();

        DESX(const std::string & KEY, const std::string & KEY1, const std::string & KEY2);
        std::string encrypt(const std::string & DATA);
        std::string decrypt(const std::string & DATA);
        unsigned int blocksize() const;
};
#endif
