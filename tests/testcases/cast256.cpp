#include <gtest/gtest.h>

#include "Encryptions/CAST256.h"

#include "testvectors/cast/cast256rfc2612.h"

TEST(CAST256, rfc2612) {
    sym_test <CAST256> (CAST256_RFC2612);
}
