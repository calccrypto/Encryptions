#include <gtest/gtest.h>

#include "Encryptions/XTEA.h"

#include "testvectors/xtea/tayloredge.h"

TEST(XTEA, Taylor_Edge) {
    sym_test <XTEA> (XTEA_TAYLOR_EDGE);
}
