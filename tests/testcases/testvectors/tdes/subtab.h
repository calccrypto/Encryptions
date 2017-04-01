#ifndef __TRIPLEDESECBSUBTAB__
#define __TRIPLEDESECBSUBTAB__

#include "../plainkeycipher.h"

// Test vectors from <http://csrc.nist.gov/groups/STM/cavp/documents/des/KAT_TDES.zip>

static const std::vector <PlainKeyCipher> TDES_SUBTAB = {
    std::make_tuple("01a1d6d039776742", "7ca110454a1a6e57", "690f5b0d9a26939b"),
    std::make_tuple("5cd54ca83def57da", "0131d9619dc1376e", "7a389d10354bd271"),
    std::make_tuple("0248d43806f67172", "07a1133e4a0b2686", "868ebb51cab4599a"),
    std::make_tuple("51454b582ddf440a", "3849674c2602319e", "7178876e01f19b2a"),
    std::make_tuple("42fd443059577fa2", "04b915ba43feb5b6", "af37fb421f8c4095"),
    std::make_tuple("059b5e0851cf143a", "0113b970fd34f2ce", "86a560f10ec6d85b"),
    std::make_tuple("0756d8e0774761d2", "0170f175468fb5e6", "0cd3da020021dc09"),
    std::make_tuple("762514b829bf486a", "43297fad38e373fe", "ea676b2cb7db2b7a"),
    std::make_tuple("3bdd119049372802", "07a7137045da2a16", "dfd64a815caf1a0f"),
    std::make_tuple("26955f6835af609a", "04689104c2fd3b2f", "5c513c9c4886c088"),
    std::make_tuple("164d5e404f275232", "37d06bb516cb7546", "0a2aeeae3ff4ab77"),
    std::make_tuple("6b056e18759f5cca", "1f08260d1ac2465e", "ef1bf03e5dfa575a"),
    std::make_tuple("004bd6ef09176062", "584023641aba6176", "88bf0db6d70dee56"),
    std::make_tuple("480d39006ee762f2", "025816164629b007", "a1f9915541020b56"),
    std::make_tuple("437540c8698f3cfa", "49793ebc79b3258f", "6fbf1cafcffd0556"),
    std::make_tuple("072d43a077075292", "4fb05e1515ab73a7", "2f22e49bab7ca1ac"),
    std::make_tuple("02fe55778117f12a", "49e95d6d4ca229bf", "5a6b612cc26cce4a"),
    std::make_tuple("1d9d5c5018f728c2", "018310dc409b26d6", "5f4c038ed12b2e41"),
    std::make_tuple("305532286d6f295a", "1c587f1c13924fef", "63fac0d034d9f793"),
};

#endif // __TRIPLEDESECBSUBTAB__
