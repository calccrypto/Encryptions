#ifndef __SKIPJACKTESTVECTORSNIST__
#define __SKIPJACKTESTVECTORSNIST__

#include "../plainkeycipher.h"

// Test vector from <http://csrc.nist.gov/groups/STM/cavp/documents/skipjack/skipjack.pdf>

static const std::vector <PlainKeyCipher> SKIPJACK_TEST_VECTORS_NIST = {
    std::make_tuple("33221100ddccbbaa", "00998877665544332211", "2587cae27a12d300"),
};

#endif // __SKIPJACKTESTVECTORSNIST__
