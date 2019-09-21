#ifndef __RC5nessieset4__
#define __RC5nessieset4__

#include "../plainkeycipher.h"

// Test vectors from <https://www.cosic.esat.kuleuven.be/nessie/testvectors/bc/rc5/Rc5-128-64.verified.test-vectors>

static const std::vector <PlainKeyCipher> RC5_NESSIE_SET_4 = {
    std::make_tuple("0011223344556677", "000102030405060708090A0B0C0D0E0F", "2DDC149BCF088B9E"),
    std::make_tuple("EA024714AD5C4D84", "2BD6459F82C5B300952C49104881FF48", "11E43B86D231EA64"),
};

#endif // __RC5nessieset4__