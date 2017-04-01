#include <gtest/gtest.h>

#include "Encryptions/Skipjack.h"

#include "testvectors/skipjack/nist.h"
#include "testvectors/skipjack/scicrypt.h"

TEST(Skipjack, NIST) {
    sym_test <Skipjack> (SKIPJACK_NIST);
}

TEST(Skipjack, sci_crypt) {
    sym_test <Skipjack> (SKIPJACK_SCI_CRYPT);
}
