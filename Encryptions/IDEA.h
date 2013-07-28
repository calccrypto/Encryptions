#include <vector>

#include "../common/cryptomath.h"
#include "error.h"
#include "SymAlg.h"

#ifndef __IDEA__
#define __IDEA__
class IDEA : public SymAlg{
    private:
        std::string mode;
        std::vector <std::vector <uint16_t> > keys;
        std::vector <uint16_t> k;
        uint16_t mult(uint32_t value1, uint32_t value2);
        int invmod(uint32_t b);
        std::string run(std::string & data);

    public:
        IDEA();
        IDEA(std::string KEY);
        void setkey(std::string KEY);
        std::string encrypt(std::string DATA);
        std::string decrypt(std::string DATA);
        unsigned int blocksize();
};
#endif
