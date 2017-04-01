#ifndef __TEST_IDEAnessieset8__
#define __TEST_IDEAnessieset8__

#include "../plainkeycipher.h"

// Test vectors from <https://www.cosic.esat.kuleuven.be/nessie/testvectors/bc/idea/Idea-128-64.verified.test-vectors>

const std::vector <PlainKeyCipher> IDEA_NESSIE_SET_8 = {
    std::make_tuple("db2d4a92aa68273f", "000102030405060708090a0b0c0d0e0f", "0011223344556677"),
    std::make_tuple("f129a6601ef62a47", "2bd6459f82c5b300952c49104881ff48", "ea024714ad5c4d84"),
};

#endif // __TEST_IDEAnessieset8__
