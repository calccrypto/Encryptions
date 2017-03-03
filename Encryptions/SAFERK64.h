/*
SAFERK64.h

Copyright (c) 2013 - 2017 Jason Lee @ calccrypto at gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef __SAFERK64__
#define __SAFERK64__

#include <vector>

#include "../common/cryptomath.h"
#include "SymAlg.h"

#include "SAFERK64_Const.h"

class SAFERK64 : public SymAlg{
    private:
        uint8_t r;          // 6 <= r <= 10
        std::vector <std::vector <uint8_t> > keys;
        void add_bias(std::vector <uint8_t> & key_i, const uint8_t b[8]);
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
        SAFERK64(const std::string & KEY, const uint8_t & rounds = 10);
        void setkey(const std::string & KEY, const uint8_t & rounds = 10);
        std::string encrypt(const std::string & DATA);
        std::string decrypt(const std::string & DATA);
        unsigned int blocksize() const;
};

#endif
