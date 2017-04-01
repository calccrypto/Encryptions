#include <gtest/gtest.h>

#include "common/includes.h"
#include "Encryptions/SAFERK64.h"

#include "testvectors/safer/saferk64paper.h"

TEST(SAFERK64, 6_rounds) {
    for(PlainKeyCipher const & pkc : SAFERK64_PAPER){
        std::string plain, key, cipher;
        std::tie(plain, key, cipher) = pkc;
        auto saferk64 = SAFERK64(unhexlify(key), 6);
        EXPECT_EQ(saferk64.encrypt(unhexlify(plain)), unhexlify(cipher));
        EXPECT_EQ(saferk64.decrypt(unhexlify(cipher)), unhexlify(plain));
    }
}
