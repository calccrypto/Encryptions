#include <gtest/gtest.h>

#include "common/includes.h"
#include "Encryptions/RC4.h"

#include "testvectors/rc/rc4testvectorsscicrypt.h"

TEST(RC4, sci_crypt) {
    sym_test <RC4> (RC4_TEST_VECTORS_SCI_CRYPT);
}
