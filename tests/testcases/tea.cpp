#include <gtest/gtest.h>

#include "Encryptions/TEA.h"

#include "testvectors/tea/teatestvectors.h"

TEST(TEA, test) {
    sym_test <TEA> (TEA_TEST_VECTORS);
}
