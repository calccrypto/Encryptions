#include <gtest/gtest.h>

#include "Encryptions/SEED.h"

#include "testvectors/seed/nessieset1.h"
#include "testvectors/seed/nessieset2.h"
#include "testvectors/seed/nessieset3.h"
#include "testvectors/seed/nessieset4.h"

TEST(SEED, set1) {
    sym_test <SEED> (SEED_NESSIE_SET_1);
}

TEST(SEED, set2) {
    sym_test <SEED> (SEED_NESSIE_SET_2);
}

TEST(SEED, set3) {
    sym_test <SEED> (SEED_NESSIE_SET_3);
}

TEST(SEED, set4) {
    sym_test <SEED> (SEED_NESSIE_SET_4);
}

