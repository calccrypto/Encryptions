#include <gtest/gtest.h>

#include "Encryptions/GOST.h"

#include "testvectors/gost/testvectors.h"

TEST(GOST, 28147_89) {
    for(PlainKeyCipher const & pkc : GOST_TEST_VECTORS){
        std::string plain, key, cipher;
        std::tie(plain, key, cipher) = pkc;
        auto gost = GOST(unhexlify(key), DES_sbox);
        EXPECT_EQ(gost.encrypt(unhexlify(plain)), unhexlify(cipher));
        EXPECT_EQ(gost.decrypt(unhexlify(cipher)), unhexlify(plain));
    }
}
