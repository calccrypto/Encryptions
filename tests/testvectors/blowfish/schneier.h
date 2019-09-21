#ifndef __BLOWFISHTESTVECTORS__
#define __BLOWFISHTESTVECTORS__

#include "../plainkeycipher.h"

// Test vectors from <https://www.schneier.com/code/vectors.txt>

const std::vector <PlainKeyCipher> BLOWFISH_SCHNEIER = {
    std::make_tuple("0000000000000000", "0000000000000000", "4ef997456198dd78"), 
    std::make_tuple("ffffffffffffffff", "ffffffffffffffff", "51866fd5b85ecb8a"), 
    std::make_tuple("1000000000000001", "3000000000000000", "7d856f9a613063f2"), 
    std::make_tuple("1111111111111111", "1111111111111111", "2466dd878b963c9d"), 
    std::make_tuple("1111111111111111", "0123456789abcdef", "61f9c3802281b096"), 
    std::make_tuple("0123456789abcdef", "1111111111111111", "7d0cc630afda1ec7"), 
    std::make_tuple("0000000000000000", "0000000000000000", "4ef997456198dd78"), 
    std::make_tuple("0123456789abcdef", "fedcba9876543210", "0aceab0fc6a0a28d"), 
    std::make_tuple("01a1d6d039776742", "7ca110454a1a6e57", "59c68245eb05282b"), 
    std::make_tuple("5cd54ca83def57da", "0131d9619dc1376e", "b1b8cc0b250f09a0"), 
    std::make_tuple("0248d43806f67172", "07a1133e4a0b2686", "1730e5778bea1da4"), 
    std::make_tuple("51454b582ddf440a", "3849674c2602319e", "a25e7856cf2651eb"), 
    std::make_tuple("42fd443059577fa2", "04b915ba43feb5b6", "353882b109ce8f1a"), 
    std::make_tuple("059b5e0851cf143a", "0113b970fd34f2ce", "48f4d0884c379918"), 
    std::make_tuple("0756d8e0774761d2", "0170f175468fb5e6", "432193b78951fc98"), 
    std::make_tuple("762514b829bf486a", "43297fad38e373fe", "13f04154d69d1ae5"), 
    std::make_tuple("3bdd119049372802", "07a7137045da2a16", "2eedda93ffd39c79"), 
    std::make_tuple("26955f6835af609a", "04689104c2fd3b2f", "d887e0393c2da6e3"), 
    std::make_tuple("164d5e404f275232", "37d06bb516cb7546", "5f99d04f5b163969"), 
    std::make_tuple("6b056e18759f5cca", "1f08260d1ac2465e", "4a057a3b24d3977b"), 
    std::make_tuple("004bd6ef09176062", "584023641aba6176", "452031c1e4fada8e"), 
    std::make_tuple("480d39006ee762f2", "025816164629b007", "7555ae39f59b87bd"), 
    std::make_tuple("437540c8698f3cfa", "49793ebc79b3258f", "53c55f9cb49fc019"), 
    std::make_tuple("072d43a077075292", "4fb05e1515ab73a7", "7a8e7bfa937e89a3"), 
    std::make_tuple("02fe55778117f12a", "49e95d6d4ca229bf", "cf9c5d7a4986adb5"), 
    std::make_tuple("1d9d5c5018f728c2", "018310dc409b26d6", "d1abb290658bc778"), 
    std::make_tuple("305532286d6f295a", "1c587f1c13924fef", "55cb3774d13ef201"), 
    std::make_tuple("0123456789abcdef", "0101010101010101", "fa34ec4847b268b2"), 
    std::make_tuple("0123456789abcdef", "1f1f1f1f0e0e0e0e", "a790795108ea3cae"), 
    std::make_tuple("0123456789abcdef", "e0fee0fef1fef1fe", "c39e072d9fac631d"), 
    std::make_tuple("ffffffffffffffff", "0000000000000000", "014933e0cdaff6e4"), 
    std::make_tuple("0000000000000000", "ffffffffffffffff", "f21e9a77b71c49bc"), 
    std::make_tuple("0000000000000000", "0123456789abcdef", "245946885754369a"), 
    std::make_tuple("ffffffffffffffff", "fedcba9876543210", "6b5c5a9c5d9e0a5a"), 
};

#endif // __BLOWFISHTESTVECTORS__
