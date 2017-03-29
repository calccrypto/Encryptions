#include <gtest/gtest.h>

#include "Encryptions/DES.h"

#include "testvectors/des/destestvectorsset1.h"
#include "testvectors/des/destestvectorsset2.h"
#include "testvectors/des/destestvectorsset3.h"
#include "testvectors/des/destestvectorsset4.h"


TEST(DES, set1) {
    sym_test <DES> (DES_TEST_VECTORS_SET_1);
}

TEST(DES, set2) {
    sym_test <DES> (DES_TEST_VECTORS_SET_2);
}

TEST(DES, set3) {
    sym_test <DES> (DES_TEST_VECTORS_SET_3);
}

TEST(DES, set4) {
    sym_test <DES> (DES_TEST_VECTORS_SET_4);
}
