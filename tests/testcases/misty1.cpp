#include <gtest/gtest.h>

#include "Encryptions/MISTY1.h"

#include "testvectors/misty1/misty1testvectorsset1.h"
#include "testvectors/misty1/misty1testvectorsset2.h"
#include "testvectors/misty1/misty1testvectorsset3.h"
#include "testvectors/misty1/misty1testvectorsset4.h"

TEST(MISTY1, set1) {
    sym_test <MISTY1> (MISTY1_TEST_VECTORS_SET_1);
}

TEST(MISTY1, set2) {
    sym_test <MISTY1> (MISTY1_TEST_VECTORS_SET_2);
}

TEST(MISTY1, set3) {
    sym_test <MISTY1> (MISTY1_TEST_VECTORS_SET_3);
}

TEST(MISTY1, set4) {
    sym_test <MISTY1> (MISTY1_TEST_VECTORS_SET_4);
}

