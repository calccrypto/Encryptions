#include <gtest/gtest.h>

#include "Encryptions/TDES.h"

#include "testvectors/tdes/tripledesecbinvperm.h"
#include "testvectors/tdes/tripledesecbpermop.h"
#include "testvectors/tdes/tripledesecbsubtab.h"
#include "testvectors/tdes/tripledesecbvarkey.h"
#include "testvectors/tdes/tripledesecbvartxt.h"

TEST(TripleDES, invperm) {
    for(PlainKeyCipher const & pkc : TDES_INVPERM){
        std::string plain, key, cipher;
        std::tie(plain, key, cipher) = pkc;
        key = unhexlify(key);
        auto tdes = TDES(key, "e", key, "d", key, "e");  //!< DES(key) == TDES(key, key, key)
        EXPECT_EQ(tdes.encrypt(unhexlify(plain)), unhexlify(cipher));
        EXPECT_EQ(tdes.decrypt(unhexlify(cipher)), unhexlify(plain));
    }
}

TEST(TripleDES, permop) {
    for(PlainKeyCipher const & pkc : TDES_PERMOP){
        std::string plain, key, cipher;
        std::tie(plain, key, cipher) = pkc;
        key = unhexlify(key);
        auto tdes = TDES(key, "e", key, "d", key, "e");  //!< DES(key) == TDES(key, key, key)
        EXPECT_EQ(tdes.encrypt(unhexlify(plain)), unhexlify(cipher));
        EXPECT_EQ(tdes.decrypt(unhexlify(cipher)), unhexlify(plain));
    }
}

TEST(TripleDES, subtab) {
    for(PlainKeyCipher const & pkc : TDES_SUBTAB){
        std::string plain, key, cipher;
        std::tie(plain, key, cipher) = pkc;
        key = unhexlify(key);
        auto tdes = TDES(key, "e", key, "d", key, "e");  //!< DES(key) == TDES(key, key, key)
        EXPECT_EQ(tdes.encrypt(unhexlify(plain)), unhexlify(cipher));
        EXPECT_EQ(tdes.decrypt(unhexlify(cipher)), unhexlify(plain));
    }
}

TEST(TripleDES, varkey) {
    for(PlainKeyCipher const & pkc : TDES_VARKEY){
        std::string plain, key, cipher;
        std::tie(plain, key, cipher) = pkc;
        key = unhexlify(key);
        auto tdes = TDES(key, "e", key, "d", key, "e");  //!< DES(key) == TDES(key, key, key)
        EXPECT_EQ(tdes.encrypt(unhexlify(plain)), unhexlify(cipher));
        EXPECT_EQ(tdes.decrypt(unhexlify(cipher)), unhexlify(plain));
    }
}

TEST(TripleDES, vartext) {
    for(PlainKeyCipher const & pkc : TDES_VARTXT){
        std::string plain, key, cipher;
        std::tie(plain, key, cipher) = pkc;
        key = unhexlify(key);
        auto tdes = TDES(key, "e", key, "d", key, "e");  //!< DES(key) == TDES(key, key, key)
        EXPECT_EQ(tdes.encrypt(unhexlify(plain)), unhexlify(cipher));
        EXPECT_EQ(tdes.decrypt(unhexlify(cipher)), unhexlify(plain));
    }
}
