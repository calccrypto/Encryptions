#ifndef __GOSTTESTVECTORS__
#define __GOSTTESTVECTORS__

#include "../plainkeycipher.h"

// Test vector from somewhere

const std::vector <PlainKeyCipher> GOST_TEST_VECTORS = {
    std::make_tuple ("3031323330313233", "3031323330313233303132333031323330313233303132333031323330313233", "f56b8a589f6f7417"),
};

#endif // __GOSTTESTVECTORS__
