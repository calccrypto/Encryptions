#include <algorithm>
#include <vector>

#ifndef __AES__
#define __AES__

#include "../common/cryptomath.h"
#include "../common/includes.h"
#include "SymAlg.h"

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
        AES(const std::string & KEY);
        void setkey(const std::string & KEY);
        std::string encrypt(const std::string & DATA);
        std::string decrypt(const std::string & DATA);
        unsigned int blocksize() const;
};
#endif
