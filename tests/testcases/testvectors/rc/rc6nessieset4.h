#ifndef __RC6nessieset4__
#define __RC6nessieset4__

#include "../plainkeycipher.h"

// Test vector from <https://www.cosic.esat.kuleuven.be/nessie/testvectors/bc/rc6/Rc6-192-128.verified.test-vectors>

static const std::vector <PlainKeyCipher> RC6_NESSIE_SET_4 = {
    std::make_tuple("00112233445566778899AABBCCDDEEFF", "000102030405060708090A0B0C0D0E0F1011121314151617", "37E13FB5351BD78D3E7912FDC5F80FCD"),
    std::make_tuple("EA024714AD5C4D84EA024714AD5C4D84", "2BD6459F82C5B300952C49104881FF482BD6459F82C5B300", "50D29745329694B65D6F54EE65455180"),
};

#endif // __RC6nessieset4__
