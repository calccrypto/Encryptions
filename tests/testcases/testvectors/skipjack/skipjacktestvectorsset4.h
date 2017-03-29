#ifndef __SKIPJACKTESTVECTORSSET4__
#define __SKIPJACKTESTVECTORSSET4__

#include "../plainkeycipher.h"

// Test vector from <https://www.cosic.esat.kuleuven.be/nessie/testvectors/bc/skipjack/Skipjack-80-64.unverified.test-vectors>

static const std::vector <PlainKeyCipher> SKIPJACK_TEST_VECTORS_SET_4 = {
    std::make_tuple("0011223344556677", "00010203040506070809", "756BC483AD0733E1"),
    std::make_tuple("EA024714AD5C4D84", "2BD6459F82C5B300952C", "98B020AFF67D19FC"),
};

#endif // __SKIPJACKTESTVECTORSSET4__
