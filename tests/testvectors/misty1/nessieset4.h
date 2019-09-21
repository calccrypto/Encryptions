#ifndef __MISTY1NESSIESET4__
#define __MISTY1NESSIESET4__

#include "../plainkeycipher.h"

// Test vector from <https://www.cosic.esat.kuleuven.be/nessie/testvectors/bc/misty1/Misty1-128-64.verified.test-vectors>

const std::vector <PlainKeyCipher> MISTY1_NESSIE_SET_4 = {
    std::make_tuple("0011223344556677", "000102030405060708090A0B0C0D0E0F", "3A3D8F2F2CDB11A7"),
    std::make_tuple("EA024714AD5C4D84", "2BD6459F82C5B300952C49104881FF48", "5901047178CCA69C"),
};

#endif // __MISTY1NESSIESET4__
