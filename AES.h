#include <vector>

#include "error.h"
#include "cryptomath.h"
#include "SymAlg.h"

#ifndef __AES__
#define __AES__

#include "AES_Const.h"

class AES : public SymAlg{
    private:
        uint8_t b, rounds, columns;
        std::vector <std::vector <uint32_t> > keys;

        void shiftrow(std::vector <uint32_t> & data);
        void invshiftrow(std::vector <uint32_t> & data);
        uint8_t GF(uint8_t a, uint8_t b);
        void mixcolumns(std::vector <uint32_t> & data);
        void invmixcolumns(std::vector <uint32_t> & data);
        std::string OUT(std::vector <uint32_t> & data);

    public:
        AES();
        AES(std::string KEY);
        void setkey(std::string KEY);
        std::string encrypt(std::string DATA);
        std::string decrypt(std::string DATA);
        unsigned int blocksize();
};
#endif
