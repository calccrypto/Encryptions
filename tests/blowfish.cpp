#include <gtest/gtest.h>

#include "Encryptions/Blowfish.h"

#include "testvectors/blowfish/schneier.h"

TEST(Blowfish, 64) {
    sym_test <Blowfish> (BLOWFISH_SCHNEIER);
}


