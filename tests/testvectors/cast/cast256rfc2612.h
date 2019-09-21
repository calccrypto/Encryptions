#ifndef __CAST256TESTVECTORS__
#define __CAST256TESTVECTORS__

#include "../plainkeycipher.h"

// Test vector from <https://tools.ietf.org/html/rfc2612#appendix-A>

static const std::vector <PlainKeyCipher> CAST256_RFC2612 = {
    std::make_tuple("00000000000000000000000000000000", "2342bb9efa38542c0af75647f29f615d",                                 "c842a08972b43d20836c91d1b7530f6b"),
    std::make_tuple("00000000000000000000000000000000", "2342bb9efa38542cbed0ac83940ac298bac77a7717942863",                 "1b386c0210dcadcbdd0e41aa08a7a7e8"),
    std::make_tuple("00000000000000000000000000000000", "2342bb9efa38542cbed0ac83940ac2988d7c47ce264908461cc1b5137ae6b604", "4f6a2038286897b9c9870136553317fa"),
};

#endif // __CAST256TESTVECTORS__
