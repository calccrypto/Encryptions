#include <gtest/gtest.h>

#include "Encryptions/CAST256.h"

#include "testvectors/cast/cast256testvectors.h"

TEST(CAST256, rfc) {
    sym_test <CAST256> (CAST256_TEST_VECTORS);
}
