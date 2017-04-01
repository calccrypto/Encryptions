#ifndef __DESnessieset4__
#define __DESnessieset4__

#include "../plainkeycipher.h"

// Test vectors from <https://www.cosic.esat.kuleuven.be/nessie/testvectors/bc/des/Des-64-64.test-vectors>

static const std::vector <PlainKeyCipher> DES_NESSIE_SET_4 = {
    std::make_tuple("0011223344556677", "0001020304050607", "3EF0A891CF8ED990"),
    std::make_tuple("EA024714AD5C4D84", "2BD6459F82C5B300", "126EFE8ED312190A"),
};

#endif // __DESnessieset4__