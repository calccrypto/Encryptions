#include <gtest/gtest.h>

#include "Encryptions/RC6.h"

#include "testvectors/rc/rc6testvectorsset1.h"
#include "testvectors/rc/rc6testvectorsset2.h"
#include "testvectors/rc/rc6testvectorsset3.h"
#include "testvectors/rc/rc6testvectorsset4.h"

TEST(RC6, set1) {
    sym_test <RC6> (RC6_TEST_VECTORS_SET_1);
}

TEST(RC6, set2) {
    sym_test <RC6> (RC6_TEST_VECTORS_SET_2);
}

TEST(RC6, set3) {
    sym_test <RC6> (RC6_TEST_VECTORS_SET_3);
}

TEST(RC6, set4) {
    sym_test <RC6> (RC6_TEST_VECTORS_SET_4);
}
