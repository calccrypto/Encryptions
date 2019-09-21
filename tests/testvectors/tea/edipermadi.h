#ifndef __TEATESTVECTORS__
#define __TEATESTVECTORS__

#include "../plainkeycipher.h"

// Test vector from <https://edipermadi.files.wordpress.com/2009/01/the_implementation_of_tiny_encryption_algorithm_on_pic18f4550.pdf>

static const std::vector <PlainKeyCipher> TEA_EDIPERMADI = {
    std::make_tuple("0123456789abcdef", "00112233445566778899aabbccddeeff", "126c6b92c0653a3e"),
};

#endif // __TEATESTVECTORS__
