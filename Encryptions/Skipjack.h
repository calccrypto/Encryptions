/*
Skipjack.h

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

#ifndef __SKIPJACK__
#define __SKIPJACK__

#include "../common/includes.h"
#include "SymAlg.h"

#include "Skipjack_Const.h"

class Skipjack : public SymAlg{
    private:
        std::string key;
        uint16_t G_e(const uint16_t quarter, const uint32_t fourkeys);
        void A(uint16_t & w1, uint16_t & w2, uint16_t & w3, uint16_t & w4, const uint16_t i);
        void B(uint16_t & w1, uint16_t & w2, uint16_t & w3, uint16_t & w4, const uint16_t i);
        uint16_t G_d(const uint16_t quarter, const uint32_t fourkeys);
        void invA(uint16_t & w1, uint16_t & w2, uint16_t & w3, uint16_t & w4, const uint16_t i);
        void invB(uint16_t & w1, uint16_t & w2, uint16_t & w3, uint16_t & w4, const uint16_t i);

    public:
        Skipjack();
        Skipjack(const std::string & KEY);
        void setkey(const std::string & KEY);
        std::string encrypt(const std::string & DATA);
        std::string decrypt(const std::string & DATA);
        unsigned int blocksize() const;
};

#endif
