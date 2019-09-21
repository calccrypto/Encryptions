#ifndef __XTEATESTVECTORS__
#define __XTEATESTVECTORS__

#include "../plainkeycipher.h"

// Test vector from <http://www.tayloredge.com/reference/Mathematics/XTEA.pdf>

static const std::vector <PlainKeyCipher> XTEA_TAYLOR_EDGE = {
    std::make_tuple("AF20A390547571AA", "27f917b1c1da899360e2acaaa6eb923d", "D26428AF0A202283"),
    std::make_tuple("0288419716939937", "31415926535897932384626433832795", "46e2007d58bbc2ea"),
    std::make_tuple("abc1234abc1234ab", "1234abc1234abc1234abc1234abc1234", "5c0754c1f6f0bd9b"),
    std::make_tuple("234abc1234abc123", "abc1234abc1234abc1234abc1234abc1", "cdfcc72c24bc116b"),
    std::make_tuple("deadbeefdeadbeef", "deadbeefdeadbeefdeadbeefdeadbeef", "faf28cb50940c0e0"),
    std::make_tuple("9647a9189ec565d5", "deadbeefdeadbeefdeadbeefdeadbeef", "deadbeefdeadbeef"),
    std::make_tuple("499602d2499602d2", "499602d2499602d2499602d2499602d2", "69cc2fbbe234a670"),
    std::make_tuple("74c4424ca09494e2", "499602d2499602d2499602d2499602d2", "499602d2499602d2"),
};

#endif // __XTEATESTVECTORS__
