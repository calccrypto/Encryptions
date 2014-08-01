#ifndef __IDEA__
#define __IDEA__

#include <vector>

#include "../common/cryptomath.h"
#include "../common/includes.h"
#include "SymAlg.h"

class IDEA : public SymAlg{
    private:
        std::vector <std::vector <uint16_t> > keys;
        std::vector <uint16_t> k;
        uint16_t mult(uint32_t value1, uint32_t value2);
        std::string run(const std::string & data);

    public:
        IDEA();
        IDEA(const std::string & KEY);
        void setkey(const std::string & KEY);
        std::string encrypt(const std::string & DATA);
        std::string decrypt(const std::string & DATA);
        unsigned int blocksize() const;
};
#endif
