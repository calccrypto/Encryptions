#include <gtest/gtest.h>

#include "Encryptions/AES.h"

#include "testvectors/aes/aesecbgfsbox128.h"
#include "testvectors/aes/aesecbsbox128.h"
#include "testvectors/aes/aesecbvarkey128.h"
#include "testvectors/aes/aesecbvartxt128.h"

TEST(AES, 128_gfsbox) {
    sym_test <AES> (AES128_GFSBOX);
}

TEST(AES, 128_sbox) {
    sym_test <AES> (AES128_SBOX);
}

TEST(AES, 128_varkey) {
    sym_test <AES> (AES128_VARKEY);
}

TEST(AES, 128_vartxt) {
    sym_test <AES> (AES128_VARTXT);
}

#include "testvectors/aes/aesecbgfsbox192.h"
#include "testvectors/aes/aesecbsbox192.h"
#include "testvectors/aes/aesecbvarkey192.h"
#include "testvectors/aes/aesecbvartxt192.h"

TEST(AES, 192_gfsbox) {
    sym_test <AES> (AES192_GFSBOX);
}

TEST(AES, 192_sbox) {
    sym_test <AES> (AES192_SBOX);
}

TEST(AES, 192_varkey) {
    sym_test <AES> (AES192_VARKEY);
}

TEST(AES, 192_vartxt) {
    sym_test <AES> (AES192_VARTXT);
}


#include "testvectors/aes/aesecbgfsbox256.h"
#include "testvectors/aes/aesecbsbox256.h"
#include "testvectors/aes/aesecbvarkey256.h"
#include "testvectors/aes/aesecbvartxt256.h"

TEST(AES, 256_gfsbox) {
    sym_test <AES> (AES256_GFSBOX);
}

TEST(AES, 256_sbox) {
    sym_test <AES> (AES256_SBOX);
}

TEST(AES, 256_varkey) {
    sym_test <AES> (AES256_VARKEY);
}

TEST(AES, 256_vartxt) {
    sym_test <AES> (AES256_VARTXT);
}
