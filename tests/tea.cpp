#include <gtest/gtest.h>

#include "Encryptions/TEA.h"

#include "testvectors/tea/edipermadi.h"

TEST(TEA, edipermadi) {
    sym_test <TEA> (TEA_EDIPERMADI);
}
