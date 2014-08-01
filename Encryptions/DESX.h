#ifndef __DESX__
#define __DESX__

#include "SymAlg.h"

#include "DES.h"

class DESX : public SymAlg{
    private:
        DES des;

    public:
        DESX();

        DESX(const std::string & KEY, const std::string & KEY2);
        std::string encrypt(const std::string & data, const std::string & KEY3);
        std::string decrypt(const std::string & data, const std::string & KEY3);
        unsigned int blocksize() const;
};
#endif
