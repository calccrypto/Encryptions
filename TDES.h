#include "error.h"
#include "SymAlg.h"
#include "DES.h"

#ifndef __TDES__
#define __TDES__
class TDES : public SymAlg{
    private:
        std::string k1, k2, k3;
        bool m1, m2, m3;
        std::string run(std::string data, std::string & key, const bool & mode);

    public:
        TDES();
        TDES(std::string & key1, const std::string & mode1, std::string & key2, const std::string & mode2, std::string & key3, const std::string & mode3);
        void setkey(std::string & key1, const std::string & mode1, std::string & key2, const std::string & mode2, std::string & key3, const std::string & mode3);
        std::string encrypt(std::string DATA);
        std::string decrypt(std::string DATA);
        unsigned int blocksize();
};
#endif
