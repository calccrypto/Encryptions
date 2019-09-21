#ifndef __SEEDNESSIESET4__
#define __SEEDNESSIESET4__

#include "../plainkeycipher.h"

// Test vectors from <https://www.cosic.esat.kuleuven.be/nessie/testvectors/bc/seed/Seed-128-128.unverified.test-vectors>

static const std::vector <PlainKeyCipher> SEED_NESSIE_SET_4 = {
    std::make_tuple("00112233445566778899AABBCCDDEEFF", "000102030405060708090A0B0C0D0E0F", "AF527210EB79C7A023ABF348E70C9045"),
    std::make_tuple("EA024714AD5C4D84EA024714AD5C4D84", "2BD6459F82C5B300952C49104881FF48", "14AE1E10DDB7764BD7D6CD66717CAF76"),
};

#endif // __SEEDNESSIESET4__