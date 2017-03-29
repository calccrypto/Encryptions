#include <gtest/gtest.h>

#include "Encryptions/skipjack.h"

#include "testvectors/skipjack/skipjacktestvectorsnist.h"
#include "testvectors/skipjack/skipjacktestvectorsset1.h"
#include "testvectors/skipjack/skipjacktestvectorsset2.h"
#include "testvectors/skipjack/skipjacktestvectorsset3.h"
#include "testvectors/skipjack/skipjacktestvectorsset4.h"

TEST(Skipjack, NIST) {
    sym_test <Skipjack> (SKIPJACK_TEST_VECTORS_NIST);
}

TEST(Skipjack, set1) {
    sym_test <Skipjack> (SKIPJACK_TEST_VECTORS_SET_1);
}

TEST(Skipjack, set2) {
    sym_test <Skipjack> (SKIPJACK_TEST_VECTORS_SET_2);
}

TEST(Skipjack, set3) {
    sym_test <Skipjack> (SKIPJACK_TEST_VECTORS_SET_3);
}

TEST(Skipjack, set4) {
    sym_test <Skipjack> (SKIPJACK_TEST_VECTORS_SET_4);
}

