#include <gtest/gtest.h>

#include "Encryptions/Camellia.h"

#include "testvectors/camellia/ntt.h"

// don't use sym_test; too much swapping

TEST(Camellia, 128) {
    ASSERT_EQ(CAMELLIA128_KEY.size(), CAMELLIA128_CIPHER.size());

    for ( unsigned int i = 0; i < CAMELLIA128_KEY.size(); ++i ) {
        ASSERT_EQ(CAMELLIA_PLAIN.size(), CAMELLIA128_CIPHER[i].size());

        auto camellia128 = Camellia(unhexlify(CAMELLIA128_KEY[i]));
        for ( unsigned int x = 0; x < CAMELLIA_PLAIN.size(); ++x ) {
            EXPECT_EQ(hexlify(camellia128.encrypt(unhexlify(CAMELLIA_PLAIN[x]))), CAMELLIA128_CIPHER[i][x]);
            EXPECT_EQ(hexlify(camellia128.decrypt(unhexlify(CAMELLIA128_CIPHER[i][x]))), CAMELLIA_PLAIN[x]);
        }
    }
}

TEST(Camellia, 192) {
    ASSERT_EQ(CAMELLIA192_KEY.size(), CAMELLIA192_CIPHER.size());

    for ( unsigned int i = 0; i < CAMELLIA192_KEY.size(); ++i ) {

        ASSERT_EQ(CAMELLIA_PLAIN.size(), CAMELLIA192_CIPHER[i].size());

        auto camellia192 = Camellia(unhexlify(CAMELLIA192_KEY[i]));
        for ( unsigned int x = 0; x < CAMELLIA_PLAIN.size(); ++x ) {
            EXPECT_EQ(hexlify(camellia192.encrypt(unhexlify(CAMELLIA_PLAIN[x]))), CAMELLIA192_CIPHER[i][x]);
            EXPECT_EQ(hexlify(camellia192.decrypt(unhexlify(CAMELLIA192_CIPHER[i][x]))), CAMELLIA_PLAIN[x]);
        }
    }
}

TEST(Camellia, 256) {
    ASSERT_EQ(CAMELLIA256_KEY.size(), CAMELLIA256_CIPHER.size());

    for ( unsigned int i = 0; i < CAMELLIA256_KEY.size(); ++i ) {

        ASSERT_EQ(CAMELLIA_PLAIN.size(), CAMELLIA256_CIPHER[i].size());

        auto camellia256 = Camellia(unhexlify(CAMELLIA256_KEY[i]));
        for ( unsigned int x = 0; x < CAMELLIA_PLAIN.size(); ++x ) {
            EXPECT_EQ(hexlify(camellia256.encrypt(unhexlify(CAMELLIA_PLAIN[x]))), CAMELLIA256_CIPHER[i][x]);
            EXPECT_EQ(hexlify(camellia256.decrypt(unhexlify(CAMELLIA256_CIPHER[i][x]))), CAMELLIA_PLAIN[x]);
        }
    }
}
