#include <gtest/gtest.h>

#include "Encryptions/IDEA.h"

#include "testvectors/idea/ideatestvectorsset1.h"
#include "testvectors/idea/ideatestvectorsset2.h"
#include "testvectors/idea/ideatestvectorsset3.h"
#include "testvectors/idea/ideatestvectorsset4.h"
#include "testvectors/idea/ideatestvectorsset5.h"
#include "testvectors/idea/ideatestvectorsset6.h"
#include "testvectors/idea/ideatestvectorsset7.h"
#include "testvectors/idea/ideatestvectorsset8.h"

TEST(IDEA, set1) {
    sym_test <IDEA> (IDEA_TEST_VECTORS_SET_1);
}

TEST(IDEA, set2) {
    sym_test <IDEA> (IDEA_TEST_VECTORS_SET_2);
}

TEST(IDEA, set3) {
    sym_test <IDEA> (IDEA_TEST_VECTORS_SET_3);
}

TEST(IDEA, set4) {
    sym_test <IDEA> (IDEA_TEST_VECTORS_SET_4);
}

TEST(IDEA, set5) {
    sym_test <IDEA> (IDEA_TEST_VECTORS_SET_5);
}

TEST(IDEA, set6) {
    sym_test <IDEA> (IDEA_TEST_VECTORS_SET_6);
}

TEST(IDEA, set7) {
    sym_test <IDEA> (IDEA_TEST_VECTORS_SET_7);
}

TEST(IDEA, set8) {
    sym_test <IDEA> (IDEA_TEST_VECTORS_SET_8);
}
