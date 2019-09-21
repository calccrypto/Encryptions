#ifndef __RC5PAPER__
#define __RC5PAPER__

#include "../plainkeycipher.h"

// Test vectors from <https://people.csail.mit.edu/rivest/Rivest-rc5rev.pdf>

static const std::vector <PlainKeyCipher> RC5_PAPER = {
    std::make_tuple("0000000000000000", "00000000000000000000000000000000", "21a5dbee154b8f6d"),
    std::make_tuple("21a5dbee154b8f6d", "915f4619be41b2516355a50110a9ce91", "f7c013ac5b2b8952"),
    std::make_tuple("f7c013ac5b2b8952", "783348e75aeb0f2fd7b169bb8dc16787", "2f42b3b70369fc92"),
    std::make_tuple("2f42b3b70369fc92", "dc49db1375a5584f6485b413b5f12baf", "65c178b284d197cc"),
    std::make_tuple("65c178b284d197cc", "5269f149d41ba0152497574d7f153125", "eb44e415da319824"),
};

#endif // __RC5TESTVECTORSPAPER__