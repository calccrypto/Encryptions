#include <gtest/gtest.h>

#include "Encryptions/RC6.h"

#include "testvectors/rc/rc6nessieset1.h"
#include "testvectors/rc/rc6nessieset2.h"
#include "testvectors/rc/rc6nessieset3.h"
#include "testvectors/rc/rc6nessieset4.h"

TEST(RC6, set1) {
    sym_test <RC6> (RC6_NESSIE_SET_1);
}

TEST(RC6, set2) {
    sym_test <RC6> (RC6_NESSIE_SET_2);
}

TEST(RC6, set3) {
    sym_test <RC6> (RC6_NESSIE_SET_3);
}

TEST(RC6, set4) {
    sym_test <RC6> (RC6_NESSIE_SET_4);
}
