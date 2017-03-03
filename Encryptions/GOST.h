/*
GOST.h

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

#ifndef __GOST__
#define __GOST__

#include "../common/cryptomath.h"
#include "../common/includes.h"
#include "SymAlg.h"

#include "GOST_Const.h"

// GOST 28147-89
class GOST : public SymAlg{
    private:
        uint8_t k[8][16];
        uint32_t X[8], N[6], C1, C2;
        uint32_t CM1(const uint32_t a, const uint32_t b);
        uint32_t CM2(const uint32_t a, const uint32_t b);
//        uint32_t CM3(const uint32_t a, const uint32_t b){return static_cast <uint32_t> (a + b);}
//        uint32_t CM4(const uint32_t a, const uint32_t b){return static_cast <uint32_t> (a + b) % mod32;}
//        uint32_t CM5(const uint32_t a, const uint32_t b){return static_cast <uint32_t> (a ^ b);}
        uint32_t sub(uint32_t in);

    public:
        GOST();
        GOST(const std::string & KEY, const uint8_t sbox[8][16]);
        void setkey(const std::string & KEY, const uint8_t sbox[8][16]);
        std::string encrypt(const std::string & DATA);
        std::string decrypt(const std::string & DATA);
        unsigned int blocksize() const;
};

#endif
