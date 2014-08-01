#include "DES.h"
#include "SymAlg.h"

#ifndef __TDES__
#define __TDES__
class TDES : public SymAlg{
    private:
        std::string k1, k2, k3;
        bool m1, m2, m3;
        std::string run(const std::string & data, const std::string & key, const bool & mode);

    public:
        TDES();
        TDES(const std::string & key1, const std::string & mode1, const std::string & key2, const std::string & mode2, const std::string & key3, const std::string & mode3);
        void setkey(const std::string & key1, const std::string & mode1, const std::string & key2, const std::string & mode2, const std::string & key3, const std::string & mode3);
        std::string encrypt(const std::string & DATA);
        std::string decrypt(const std::string & DATA);
        unsigned int blocksize() const;
};
#endif
