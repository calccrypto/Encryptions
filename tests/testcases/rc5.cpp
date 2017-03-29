#include <gtest/gtest.h>

#include "Encryptions/RC5.h"

#include "testvectors/rc/rc5testvectorspaper.h"
#include "testvectors/rc/rc5testvectorsset1.h"
#include "testvectors/rc/rc5testvectorsset2.h"
#include "testvectors/rc/rc5testvectorsset3.h"
#include "testvectors/rc/rc5testvectorsset4.h"

TEST(RC5, paper) {
    sym_test <RC5> (RC5_TEST_VECTORS_PAPER);
}

TEST(RC5, set1) {
    sym_test <RC5> (RC5_TEST_VECTORS_SET_1);
}

TEST(RC5, set2) {
    sym_test <RC5> (RC5_TEST_VECTORS_SET_2);
}

TEST(RC5, set3) {
    sym_test <RC5> (RC5_TEST_VECTORS_SET_3);
}

TEST(RC5, set4) {
    sym_test <RC5> (RC5_TEST_VECTORS_SET_4);
}

