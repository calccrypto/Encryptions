/*
CAST128.h

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

#ifndef __CAST128__
#define __CAST128__

#include "../common/cryptomath.h"
#include "../common/includes.h"
#include "SymAlg.h"

#include "CAST_Const.h"
#include "CAST128_Const.h"

class CAST128 : public SymAlg{
    private:
        uint8_t rounds, kr[16];
        uint32_t km[16];
        uint32_t F(const uint8_t & round, const uint32_t & D, const uint32_t & Kmi, const uint8_t & Kri);
        std::string run(const std::string & data, const uint8_t start, const uint8_t stop, const uint8_t step);

    public:
        CAST128();
        CAST128(const std::string & KEY);
        void setkey(std::string KEY);
        std::string encrypt(const std::string & DATA);
        std::string decrypt(const std::string & DATA);
        unsigned int blocksize() const;
};

#endif
