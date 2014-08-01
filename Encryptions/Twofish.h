#ifndef __TWOFISH__
#define __TWOFISH__

#include <vector>

#include "../common/includes.h"
#include "SymAlg.h"

#include "Twofish_Const.h"

class Twofish : public SymAlg{
    private:
        std::vector<uint32_t> l_key;
        std::vector<std::vector<uint32_t>> mk_tab;

        uint32_t h_fun(uint32_t x, const std::vector<uint32_t> & key);
        std::string run(const std::string & data, bool enc);

    public:
        Twofish();
        Twofish(const std::string & KEY);
        void setkey(const std::string & KEY);
        std::string encrypt(const std::string & DATA);
        std::string decrypt(const std::string & DATA);
        unsigned int blocksize() const;
};

#endif
