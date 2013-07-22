#include "error.h"
#include "SymAlg.h"

#ifndef __DES__
#define __DES__

#include "DES_Const.h"

class DES : public SymAlg{
    private:
        uint64_t keys[16];
        std::string run(std::string & data);

    public:
        DES();
        DES(std::string KEY);
        void setkey(std::string KEY);
        std::string encrypt(std::string DATA);
        std::string decrypt(std::string DATA);
        unsigned int blocksize();
};
#endif
