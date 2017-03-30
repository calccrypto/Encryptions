#include <gtest/gtest.h>

#include "Encryptions/Skipjack.h"

#include "testvectors/skipjack/skipjacktestvectorsnist.h"
#include "testvectors/skipjack/skipjacktestvectorsscicrypt.h"

TEST(Skipjack, NIST) {
    sym_test <Skipjack> (SKIPJACK_TEST_VECTORS_NIST);
}

TEST(Skipjack, sci_crypt) {
    sym_test <Skipjack> (SKIPJACK_TEST_VECTORS_SCI_CRYPT);
}
