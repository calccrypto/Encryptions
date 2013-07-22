#include <vector>

#include "error.h"
#include "cryptomath.h"
#include "SymAlg.h"

#ifndef __SAFERK64__
#define __SAFERK64__

#include "SAFERK64_Const.h"

class SAFERK64 : public SymAlg{
    private:
        uint8_t r;          // 6 <= r <= 10
        std::vector <std::vector <uint8_t> > keys;
        void add_bias(std::vector <uint8_t> & key_i, uint8_t b[8]);
        std::vector <uint8_t> byte_rotate_3(std::vector <uint8_t> & key_i);
        void xor_add(std::vector <uint8_t> & data, std::vector <uint8_t> & key);
        void add_xor(std::vector <uint8_t> & data, std::vector <uint8_t> & key);
        void xor_sub(std::vector <uint8_t> & data, std::vector <uint8_t> & key);
        void sub_xor(std::vector <uint8_t> & data, std::vector <uint8_t> & key);
        void nonlinear_lajer(std::vector <uint8_t> & data);
        void inv_nonlinear_lajer(std::vector <uint8_t> & data);
        void pht(uint8_t & a1, uint8_t & a2);
        void inv_pht(uint8_t & b1, uint8_t & b2);
        void pht_layer(std::vector <uint8_t> & data);
        void inv_pht_layer(std::vector <uint8_t> & data);

    public:
        SAFERK64();
        SAFERK64(std::string KEY, const uint8_t & rounds = 10);
        void setkey(std::string KEY, const uint8_t & rounds = 10);
        std::string encrypt(std::string DATA);
        std::string decrypt(std::string DATA);
        unsigned int blocksize();
};
#endif
