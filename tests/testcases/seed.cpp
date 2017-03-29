#include <gtest/gtest.h>

#include "Encryptions/seed.h"

#include "testvectors/seed/seedtestvectorsset1.h"
#include "testvectors/seed/seedtestvectorsset2.h"
#include "testvectors/seed/seedtestvectorsset3.h"
#include "testvectors/seed/seedtestvectorsset4.h"

TEST(SEED, set1) {
    sym_test <SEED> (SEED_TEST_VECTORS_SET_1);
}

TEST(SEED, set2) {
    sym_test <SEED> (SEED_TEST_VECTORS_SET_2);
}

TEST(SEED, set3) {
    sym_test <SEED> (SEED_TEST_VECTORS_SET_3);
}

TEST(SEED, set4) {
    sym_test <SEED> (SEED_TEST_VECTORS_SET_4);
}

