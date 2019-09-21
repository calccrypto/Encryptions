#include <gtest/gtest.h>

#include "Encryptions/RC5.h"

#include "testvectors/rc/rc5paper.h"
#include "testvectors/rc/rc5nessieset1.h"
#include "testvectors/rc/rc5nessieset2.h"
#include "testvectors/rc/rc5nessieset3.h"
#include "testvectors/rc/rc5nessieset4.h"

TEST(RC5, paper) {
    sym_test <RC5> (RC5_PAPER);
}

TEST(RC5, set1) {
    sym_test <RC5> (RC5_NESSIE_SET_1);
}

TEST(RC5, set2) {
    sym_test <RC5> (RC5_NESSIE_SET_2);
}

TEST(RC5, set3) {
    sym_test <RC5> (RC5_NESSIE_SET_3);
}

TEST(RC5, set4) {
    sym_test <RC5> (RC5_NESSIE_SET_4);
}

