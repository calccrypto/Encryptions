#include <gtest/gtest.h>

#include "common/includes.h"
#include "Encryptions/RC4.h"

#include "testvectors/rc/rc4scicrypt.h"

TEST(RC4, sci_crypt) {
    sym_test <RC4> (RC4_SCI_CRYPT);
}
