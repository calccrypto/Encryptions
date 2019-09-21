#include <gtest/gtest.h>

#include "Encryptions/IDEA.h"

#include "testvectors/idea/nessieset1.h"
#include "testvectors/idea/nessieset2.h"
#include "testvectors/idea/nessieset3.h"
#include "testvectors/idea/nessieset4.h"
#include "testvectors/idea/nessieset5.h"
#include "testvectors/idea/nessieset6.h"
#include "testvectors/idea/nessieset7.h"
#include "testvectors/idea/nessieset8.h"

TEST(IDEA, set1) {
    sym_test <IDEA> (IDEA_NESSIE_SET_1);
}

TEST(IDEA, set2) {
    sym_test <IDEA> (IDEA_NESSIE_SET_2);
}

TEST(IDEA, set3) {
    sym_test <IDEA> (IDEA_NESSIE_SET_3);
}

TEST(IDEA, set4) {
    sym_test <IDEA> (IDEA_NESSIE_SET_4);
}

TEST(IDEA, set5) {
    sym_test <IDEA> (IDEA_NESSIE_SET_5);
}

TEST(IDEA, set6) {
    sym_test <IDEA> (IDEA_NESSIE_SET_6);
}

TEST(IDEA, set7) {
    sym_test <IDEA> (IDEA_NESSIE_SET_7);
}

TEST(IDEA, set8) {
    sym_test <IDEA> (IDEA_NESSIE_SET_8);
}
