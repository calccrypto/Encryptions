#include <gtest/gtest.h>

#include "Encryptions/MISTY1.h"

#include "testvectors/misty1/nessieset1.h"
#include "testvectors/misty1/nessieset2.h"
#include "testvectors/misty1/nessieset3.h"
#include "testvectors/misty1/nessieset4.h"

TEST(MISTY1, set1) {
    sym_test <MISTY1> (MISTY1_NESSIE_SET_1);
}

TEST(MISTY1, set2) {
    sym_test <MISTY1> (MISTY1_NESSIE_SET_2);
}

TEST(MISTY1, set3) {
    sym_test <MISTY1> (MISTY1_NESSIE_SET_3);
}

TEST(MISTY1, set4) {
    sym_test <MISTY1> (MISTY1_NESSIE_SET_4);
}

