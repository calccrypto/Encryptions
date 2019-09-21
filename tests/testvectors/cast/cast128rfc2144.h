#ifndef __CAST128TESTVECTORS__
#define __CAST128TESTVECTORS__

#include "../plainkeycipher.h"

// Test vector from <http://tools.ietf.org/html/rfc2144#appendix-B>

static const std::vector <PlainKeyCipher> CAST128_RFC2144 = {
    std::make_tuple("0123456789abcdef", "0123456712",                       "7ac816d16e9b302e"),
    std::make_tuple("0123456789abcdef", "01234567123456782345",             "eb6a711a2c02271b"),
    std::make_tuple("0123456789abcdef", "0123456712345678234567893456789a", "238B4fe5847e44b2"),
};

#endif // __CAST128TESTVECTORS__
