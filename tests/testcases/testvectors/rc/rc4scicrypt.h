#ifndef __RC4SCICRYPT__
#define __RC4SCICRYPT__

#include "../plainkeycipher.h"

// Test vector from <http://groups.google.com/group/sci.crypt/msg/10a300c9d21afca0>

static const std::vector <PlainKeyCipher> RC4_SCI_CRYPT = {
    std::make_tuple("0123456789abcdef", "0123456789abcdef", "75b7878099e0c596"),
    std::make_tuple("0000000000000000", "0123456789abcdef", "7494c2e7104b0879"),
    std::make_tuple("0000000000000000", "0000000000000000", "de188941a3375d3a"),
    std::make_tuple("00000000000000000000", "ef012345", "d6a141a7ec3c38dfbd61"),
};

#endif // __RC4SCICRYPT__
