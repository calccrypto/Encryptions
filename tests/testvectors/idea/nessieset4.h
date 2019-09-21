#ifndef __IDEAnessieset4__
#define __IDEAnessieset4__

#include "../plainkeycipher.h"

// Test vectors from <https://www.cosic.esat.kuleuven.be/nessie/testvectors/bc/idea/Idea-128-64.verified.test-vectors>

const std::vector <PlainKeyCipher> IDEA_NESSIE_SET_4 = {
    std::make_tuple("0011223344556677", "000102030405060708090a0b0c0d0e0f", "f526ab9a62c0d258"),
    std::make_tuple("ea024714ad5c4d84", "2bd6459f82c5b300952c49104881ff48", "c8fb51d3516627a8"),
};

#endif // __IDEAnessieset4__
