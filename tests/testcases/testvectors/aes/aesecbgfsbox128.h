#ifndef _GFSBOX128__
#define _GFSBOX128__

#include "../plainkeycipher.h"

// Test vectors from <http://csrc.nist.gov/groups/STM/cavp/documents/aes/KAT_AES.zip>

const std::vector <PlainKeyCipher> AES128_GFSBOX = {
    std::make_tuple("f34481ec3cc627bacd5dc3fb08f273e6", "00000000000000000000000000000000", "0336763e966d92595a567cc9ce537f5e"), 
    std::make_tuple("9798c4640bad75c7c3227db910174e72", "00000000000000000000000000000000", "a9a1631bf4996954ebc093957b234589"), 
    std::make_tuple("96ab5c2ff612d9dfaae8c31f30c42168", "00000000000000000000000000000000", "ff4f8391a6a40ca5b25d23bedd44a597"), 
    std::make_tuple("6a118a874519e64e9963798a503f1d35", "00000000000000000000000000000000", "dc43be40be0e53712f7e2bf5ca707209"), 
    std::make_tuple("cb9fceec81286ca3e989bd979b0cb284", "00000000000000000000000000000000", "92beedab1895a94faa69b632e5cc47ce"), 
    std::make_tuple("b26aeb1874e47ca8358ff22378f09144", "00000000000000000000000000000000", "459264f4798f6a78bacb89c15ed3d601"), 
    std::make_tuple("58c8e00b2631686d54eab84b91f0aca1", "00000000000000000000000000000000", "08a4e2efec8a8e3312ca7460b9040bbf"), 
};

#endif // _GFSBOX128__
