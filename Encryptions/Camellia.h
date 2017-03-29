/*
Camellia.h

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

#ifndef __CAMELLIA__
#define __CAMELLIA__

#include <algorithm>
#include <vector>

#include "../common/cryptomath.h"
#include "../common/includes.h"
#include "SymAlg.h"

#include "Camellia_Const.h"

class Camellia : public SymAlg{
    // Camellia is a CRYPTmetric key block cipher developed jointly in 2000 by
    // world top class encryption researchers at NTT and Mitsubishi Electric
    // Corporation. See:http://info.isl.ntt.co.jp/crypt/eng/camellia/index.html

    private:
        uint16_t keysize;
        std::vector <std::string> keys;
        uint8_t  SBOX(const uint8_t s, const uint8_t value);
        std::string FL(const std::string & FL_IN, const std::string & KE);
        std::string FLINV(const std::string & FLINV_IN, const std::string & KE);
        std::string F(const std::string & F_IN, const std::string & KE);
        std::string run(const std::string & data);

    public:
        Camellia();
        Camellia(const std::string & KEY);
        void setkey(const std::string & KEY);
        std::string encrypt(const std::string & DATA);
        std::string decrypt(const std::string & DATA);
        unsigned int blocksize() const;
};

#endif
