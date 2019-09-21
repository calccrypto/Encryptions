#include <gtest/gtest.h>

#include "Encryptions/DES.h"

#include "testvectors/des/nessieset1.h"
#include "testvectors/des/nessieset2.h"
#include "testvectors/des/nessieset3.h"
#include "testvectors/des/nessieset4.h"

TEST(DES, set1) {
    sym_test <DES> (DES_NESSIE_SET_1);
}

TEST(DES, set2) {
    sym_test <DES> (DES_NESSIE_SET_2);
}

TEST(DES, set3) {
    sym_test <DES> (DES_NESSIE_SET_3);
}

TEST(DES, set4) {
    sym_test <DES> (DES_NESSIE_SET_4);
}
