#include <gtest/gtest.h>

#include "Encryptions/Blowfish.h"

#include "testvectors/blowfish/blowfishtestvectors.h"

TEST(Blowfish, 64) {
    sym_test <Blowfish> (BLOWFISH_TEST_VECTORS);
}


