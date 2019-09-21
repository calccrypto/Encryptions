#ifndef __SAFERK64PAPER__
#define __SAFERK64PAPER__

#include "../plainkeycipher.h"

// Test vector from <https://pdfs.semanticscholar.org/5996/c04302db4a965ee6860169c6956081c998ce.pdf>

static const std::vector <PlainKeyCipher> SAFERK64_PAPER = {
    std::make_tuple("0102030405060708", "0000000000000000", "7d28038633b92eb4"),
    std::make_tuple("0000000000000000", "0102030405060708", "5ab27f7214a33ae1"),
    std::make_tuple("0102030405060708", "0807060504030201", "c8f29cdd87783ed9"),
    std::make_tuple("0000000000000000", "0000000000000000", "032808c90ee7ab7f"),
};

#endif // __SAFERK64PAPER__
