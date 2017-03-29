#include <gtest/gtest.h>

#include "Encryptions/XTEA.h"

#include "testvectors/xtea/xteatestvectors.h"

TEST(XTEA, test) {
    sym_test <XTEA> (XTEA_TEST_VECTORS);
}
