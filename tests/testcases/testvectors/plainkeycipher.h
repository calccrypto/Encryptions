/*
plainkeycipher.h

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


#ifndef __PLAINKEYCIPHER__
#define __PLAINKEYCIPHER__

#include <string>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

#include "common/includes.h"

// hold matching plaintext/key/ciphertext tuples
typedef std::tuple <std::string, std::string, std::string> PlainKeyCipher;

// generic function to test symmetric key algorithms
template <typename Alg>
void sym_test(const std::vector <PlainKeyCipher> & test_vectors){
    static_assert(std::is_base_of <SymAlg, Alg>::value, "Error: Algorithm type should be a symmetric key algorithm.");

    for(PlainKeyCipher const & pkc : test_vectors){
        std::string plain, key, cipher;
        std::tie(plain, key, cipher) = pkc;
        auto alg = Alg(unhexlify(key));
        EXPECT_EQ(alg.encrypt(unhexlify(plain)), unhexlify(cipher));
        EXPECT_EQ(alg.decrypt(unhexlify(cipher)), unhexlify(plain));
    }
}

#endif