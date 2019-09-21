#ifndef __RC2RFC2268__
#define __RC2RFC2268__

#include "../plainkeycipher.h"

// Test vectors from <https://tools.ietf.org/html/rfc2268>

static const std::vector <PlainKeyCipher> RC2_RFC2268 = {
    // std::make_tuple("0000000000000000", "0000000000000000",                                                     "ebb773f993278eff"),
    // std::make_tuple("ffffffffffffffff", "ffffffffffffffff",                                                     "278b27e42e2f0d49"),
    // std::make_tuple("1000000000000001", "3000000000000000",                                                     "30649edf9be7d2c2"),
    // std::make_tuple("0000000000000000", "88",                                                                   "61a8a244adacccf0"),
    // std::make_tuple("0000000000000000", "88bca90e90875a",                                                       "6ccf4308974c267f"),
    // std::make_tuple("0000000000000000", "88bca90e90875a7f0f79c384627bafb2",                                     "1a807d272bbe5db1"),
    // std::make_tuple("0000000000000000", "88bca90e90875a7f0f79c384627bafb2",                                     "2269552ab0f85ca6"),
    // std::make_tuple("0000000000000000", "88bca90e90875a7f0f79c384627bafb216f80a6f85920584c42fceb0be255daf1e",   "5b78d3a43dfff1f1"),
};

#endif // __RC2RFC2268__