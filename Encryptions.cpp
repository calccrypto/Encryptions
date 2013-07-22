#include "Encryptions.h"

bool validate_symalg(std::ostream & stream, bool do_1000000_check){
    // Known Answer Test (KAT) to check if all the algorihtms are correct
    std::string data, key, ciphertext, e = "e", d = "d";
    bool all_correct = true, correct;

    // AES 128, 192, 256
    // http://csrc.nist.gov/publications/fips/fips197/fips-197.pdf
    data = "00112233445566778899aabbccddeeff";
    key = "000102030405060708090a0b0c0d0e0f";
    ciphertext = "69c4e0d86a7b0430d8cdb78070b4c55a";
    AES aes(unhexlify(key));
    correct = (aes.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "AES 128 Encrypt: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (aes.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "AES 128 Decrypt: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    data = "00112233445566778899aabbccddeeff";
    key = "000102030405060708090a0b0c0d0e0f1011121314151617";
    ciphertext = "dda97ca4864cdfe06eaf70a0ec0d7191";
    aes = AES(unhexlify(key));
    correct = (aes.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "AES 192 Encrypt: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (aes.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "AES 192 Decrypt: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    data = "00112233445566778899aabbccddeeff";
    key = "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f";
    ciphertext = "8ea2b7ca516745bfeafc49904b496089";
    aes = AES(unhexlify(key));
    correct = (aes.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "AES 256 Encrypt: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (aes.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "AES 256 Decrypt: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;


    // Blowfish
    // http://www.schneier.com/code/vectors.txt
    data = "480D39006EE762F2";
    key = "025816164629B007";
    ciphertext = "7555AE39F59B87BD";
    Blowfish blowfish(unhexlify(key));
    correct = (blowfish.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "Blowfish Encrypt 1: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (blowfish.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "Blowfish Decrypt 1: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    data = "437540C8698F3CFA";
    key = "49793EBC79B3258F";
    ciphertext = "53C55F9CB49FC019";
    blowfish = Blowfish(unhexlify(key));
    correct = (blowfish.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "Blowfish Encrypt 2: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (blowfish.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "Blowfish Decrypt 2: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;


    // Camellia;
    // RFC3713:;
    // 128-bit key;
    data = "0123456789abcdeffedcba9876543210";
    key = "0123456789abcdeffedcba9876543210";
    ciphertext = "67673138549669730857065648eabe43";
    Camellia camellia(unhexlify(key));
    correct = (camellia.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "Camellia 128-bit Key Encrypt: \t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (camellia.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "Camellia 128-bit Key Decrypt: \t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    // 192-bit key;
    data = "0123456789abcdeffedcba9876543210";
    key = "0123456789abcdeffedcba98765432100011223344556677";
    ciphertext = "b4993401b3e996f84ee5cee7d79b09b9";
    camellia = Camellia(unhexlify(key));
    correct = (camellia.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "Camellia 192-bit Key Encrypt: \t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (camellia.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "Camellia 192-bit Key Decrypt: \t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    //256-bitkey;
    data = "0123456789abcdeffedcba9876543210";
    key = "0123456789abcdeffedcba987654321000112233445566778899aabbccddeeff";
    ciphertext = "9acc237dff16d76c20ef7c919e3a7509";
    camellia = Camellia(unhexlify(key));
    correct = (camellia.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "Camellia 256-bit Key Encrypt: \t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (camellia.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "Camellia 256-bit Key Decrypt: \t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;


    // CAST-128;
    // RFC2144;
    // 40-bit;
    data = "0123456789ABCDEF";
    key = "0123456712";
    ciphertext = "7AC816D16E9B302E";
    CAST128 cast128(unhexlify(key));
    correct = (cast128.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "CAST-128 40-bit Key Encrypt: \t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (cast128.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "CAST-128 40-bit Key Decrypt: \t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    // 80-bit;
    data = "0123456789ABCDEF";
    key = "01234567123456782345";
    ciphertext = "EB6A711A2C02271B";
    cast128 = CAST128(unhexlify(key));
    correct = (cast128.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "CAST-128 80-bit Key Encrypt: \t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (cast128.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "CAST-128 80-bit Key Decrypt: \t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    // 128-bit;
    data = "0123456789ABCDEF";
    key = "0123456712345678234567893456789A";
    ciphertext = "238B4FE5847E44B2";
    cast128 = CAST128(unhexlify(key));
    correct = (cast128.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "CAST-128 128-bit Key Encrypt: \t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (cast128.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "CAST-128 128-bit Key Decrypt: \t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    // Full Maintanence Test
    if (do_1000000_check){
        std::string a = unhexlify("0123456712345678234567893456789A");
        std::string b = unhexlify("0123456712345678234567893456789A");
        for(uint32_t x = 0; x < 1000000; x++){;
            a = CAST128(b).encrypt(a.substr(0,8)) + a.substr(8,8);;
            a = a.substr(0,8) + CAST128(b).encrypt(a.substr(8,8));;
            b = CAST128(a).encrypt(b.substr(0,8)) + b.substr(8,8);;
            b = b.substr(0,8) + CAST128(a).encrypt(b.substr(8,8));;
        };
        correct = ((a == unhexlify("EEA9D0A249FD3BA6B3436FB89D6DCA92")) && (b == unhexlify("B2C95EB00C31AD7180AC05B8E83D696E")));
        stream << "CAST-128 Full Maintenence Test: \t" << (correct?"Passed":"Failed") << std::endl;
        all_correct &= correct;
    }


    // CAST-256;
    // RFC2612;
    // 128 bits;
    data = "00000000000000000000000000000000";
    key = "2342bb9efa38542c0af75647f29f615d";
    ciphertext = "c842a08972b43d20836c91d1b7530f6b";
    CAST256 cast256(unhexlify(key));
    correct = (cast256.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "CAST-256 128-bit Key Encrypt: \t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (cast256.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "CAST-256 128-bit Key Decrypt: \t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    // 192 bits;
    data = "00000000000000000000000000000000";
    key = "2342bb9efa38542cbed0ac83940ac298bac77a7717942863";
    ciphertext = "1b386c0210dcadcbdd0e41aa08a7a7e8";
    cast256 = CAST256(unhexlify(key));
    correct = (cast256.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "CAST-256 192-bit Key Encrypt: \t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (cast256.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "CAST-256 192-bit Key Decrypt: \t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    // 256 bits;
    data = "00000000000000000000000000000000";
    key = "2342bb9efa38542cbed0ac83940ac2988d7c47ce264908461cc1b5137ae6b604";
    ciphertext = "4f6a2038286897b9c9870136553317fa";
    cast256 = CAST256(unhexlify(key));
    correct = (cast256.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "CAST-256 256-bit Key Encrypt: \t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (cast256.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "CAST-256 256-bit Key Decrypt: \t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;


    // DES;
    // http://orlingrabbe.com/des.htm;
    data = "0123456789ABCDEF";
    key = "133457799BBCDFF1";
    ciphertext = "85E813540F0AB405";
    DES des(unhexlify(key));
    correct = (des.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "DES Encrypt Test 1: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (des.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "DES Decrypt Test 1: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    data = "8787878787878787";
    key = "0E329232EA6D0D73";
    ciphertext = "0000000000000000";
    des = DES(unhexlify(key));
    correct = (des.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "DES Encrypt Test 2: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (des.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "DES Decrypt Test 2: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;


    // GOST 28147-89
    // http://dl.packetstormsecurity.net/crypt/LIBS/gost/gutmann
    data = "3031323330313233";
    key = "3031323330313233303132333031323330313233303132333031323330313233";
    ciphertext = "f56b8a589f6f7417";
    GOST gost(unhexlify(key), DES_sbox);
    correct = (gost.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "GOST Encrypt Test 1: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (gost.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "GOST Decrypt Test 1: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;


    // IDEA;
    // http://www.unsw.adfa.edu.au/~lpb/src/IDEAcalc/index.html;
    data = "05320a6414c819fa";
    key = "006400c8012c019001f4025802bc0320";
    ciphertext = "65be87e7a2538aed";
    IDEA idea(unhexlify(key));
    correct = (idea.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "IDEA Encrypt Test 1: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (idea.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "IDEA Decrypt Test 1: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    // http://www.informationsuebertragung.ch/indexAlgorithmen.html;
    data = "0000000100020003";
    key = "00010002000300040005000600070008";
    ciphertext = "11fbed2b01986de5";
    idea = IDEA(unhexlify(key));
    correct = (idea.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "IDEA Encrypt Test 2: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (idea.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "IDEA Decrypt Test 2: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;


    // MISTY1
    // RFC 2994
    data = "0123456789abcdef";
    key = "00112233445566778899aabbccddeeff";
    ciphertext = "8b1da5f56ab3d07c";
    MISTY1 misty1(unhexlify(key));
    correct = (misty1.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "MISTY1 Encrypt Test 1: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (misty1.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "MISTY1 Decrypt Test 1: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    data = "fedcba9876543210";
    key = "00112233445566778899aabbccddeeff";
    ciphertext = "04b68240b13be95d";
    misty1 = MISTY1(unhexlify(key));
    correct = (misty1.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "MISTY1 Encrypt Test 2: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (misty1.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "MISTY1 Decrypt Test 2: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;


    // RC4;
    // http://groups.google.com/group/sci.crypt/msg/10a300c9d21afca0;
    data = "0123456789abcdef";
    key = "0123456789abcdef";
    ciphertext = "75b7878099e0c596";
    RC4 rc4(unhexlify(key));
    correct = (rc4.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "RC4 Encrypt Test 1: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (rc4.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "RC4 Decrypt Test 1: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    data = "0000000000000000";
    key = "0123456789abcdef";
    ciphertext = "7494c2e7104b0879";
    rc4 = RC4(unhexlify(key));
    correct = (rc4.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "RC4 Encrypt Test 2: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (rc4.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "RC4 Decrypt Test 2: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    data = "0000000000000000";
    key = "0000000000000000";
    ciphertext = "de188941a3375d3a";
    rc4 = RC4(unhexlify(key));
    correct = (rc4.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "RC4 Encrypt Test 3: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (rc4.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "RC4 Decrypt Test 3: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    data = "00000000000000000000";
    key = "ef012345";
    ciphertext = "d6a141a7ec3c38dfbd61";
    rc4 = RC4(unhexlify(key));
    correct = (rc4.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "RC4 Encrypt Test 4: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (rc4.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "RC4 Decrypt Test 4: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;


    // RC5;
    // From the paper;
    data = "0000000000000000";
    key = "00000000000000000000000000000000";
    ciphertext = "eedba5216d8f4b15";
    RC5 rc5(unhexlify(key));
    correct = (rc5.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "RC5 Encrypt Test 1: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (rc5.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "RC5 Decrypt Test 1: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    data = "eedba5216d8f4b15";
    key = "915f4619be41b2516355a50110a9ce91";
    ciphertext = "ac13c0f752892b5b";
    rc5 = RC5(unhexlify(key));
    correct = (rc5.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "RC5 Encrypt Test 2: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (rc5.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "RC5 Decrypt Test 2: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    data = "ac13c0f752892b5b";
    key = "783348e75aeb0f2fd7b169bb8dc16787";
    ciphertext = "b7b3422f92fc6903";
    rc5 = RC5(unhexlify(key));
    correct = (rc5.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "RC5 Encrypt Test 3: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (rc5.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "RC5 Decrypt Test 3: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    data = "b7b3422f92fc6903";
    key = "dc49db1375a5584f6485b413b5f12baf";
    ciphertext = "b278c165cc97d184";
    rc5 = RC5(unhexlify(key));
    correct = (rc5.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "RC5 Encrypt Test 4: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (rc5.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "RC5 Decrypt Test 4: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    data = "b278c165cc97d184";
    key = "5269f149d41ba0152497574d7f153125";
    ciphertext = "15e444eb249831da";
    rc5 = RC5(unhexlify(key));
    correct = (rc5.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "RC5 Encrypt Test 5: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (rc5.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "RC5 Decrypt Test 5: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;


    // RC6
    // From the paper
    data = "00000000000000000000000000000000";
    key = "00000000000000000000000000000000";
    ciphertext = "8fc3a53656b1f778c129df4e9848a41e";
    RC6 rc6(unhexlify(key));
    correct = (rc6.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "RC6 Encrypt Test 1: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (rc6.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "RC6 Decrypt Test 1: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    data = "02132435465768798a9bacbdcedfe0f1";
    key = "0123456789abcdef0112233445566778";
    ciphertext = "524e192f4715c6231f51f6367ea43f18";
    rc6 = RC6(unhexlify(key));
    correct = (rc6.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "RC6 Encrypt Test 2: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (rc6.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "RC6 Decrypt Test 2: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    data = "00000000000000000000000000000000";
    key = "000000000000000000000000000000000000000000000000";
    ciphertext = "6cd61bcb190b30384e8a3f168690ae82";
    rc6 = RC6(unhexlify(key));
    correct = (rc6.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "RC6 Encrypt Test 3: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (rc6.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "RC6 Decrypt Test 3: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    data = "02132435465768798a9bacbdcedfe0f1";
    key = "0123456789abcdef0112233445566778899aabbccddeeff0";
    ciphertext = "688329d019e505041e52e92af95291d4";
    rc6 = RC6(unhexlify(key));
    correct = (rc6.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "RC6 Encrypt Test 4: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (rc6.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "RC6 Decrypt Test 4: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    data = "00000000000000000000000000000000";
    key = "0000000000000000000000000000000000000000000000000000000000000000";
    ciphertext = "8f5fbd0510d15fa893fa3fda6e857ec2";
    rc6 = RC6(unhexlify(key));
    correct = (rc6.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "RC6 Encrypt Test 5: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (rc6.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "RC6 Decrypt Test 5: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    data = "02132435465768798a9bacbdcedfe0f1";
    key = "0123456789abcdef0112233445566778899aabbccddeeff01032547698badcfe";
    ciphertext = "c8241816f0d7e48920ad16a1674e5d48";
    rc6 = RC6(unhexlify(key));
    correct = (rc6.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "RC6 Encrypt Test 6: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (rc6.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "RC6 Decrypt Test 6: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;


    // SAFER K-64
    // From the paper
    data = "0102030405060708";
    key = "0807060504030201";
    ciphertext = "c8f29cdd87783ed9";
    SAFERK64 saferk64(unhexlify(key), 6);
    correct = (saferk64.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "SAFER K-64 6 Rounds Encrypt Test 1: \t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (saferk64.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "SAFER K-64 6 Rounds Decrypt Test 1: \t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    data = "0102030405060708";
    key = "0000000000000000";
    ciphertext = "7d28038633b92eb4";
    saferk64 = SAFERK64(unhexlify(key), 6);
    correct = (saferk64.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "SAFER K-64 6 Rounds Encrypt Test 2: \t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (saferk64.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "SAFER K-64 6 Rounds Decrypt Test 2: \t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;


    // SEED;
    // From somewhere
    data = "000102030405060708090A0B0C0D0E0F";
    key = "00000000000000000000000000000000";
    ciphertext = "5EBAC6E0054E166819AFF1CC6D346CDB";
    SEED seed(unhexlify(key));
    correct = (seed.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "SEED Encrypt Test 1: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (seed.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "SEED Decrypt Test 1: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    data = "00000000000000000000000000000000";
    key = "000102030405060708090A0B0C0D0E0F";
    ciphertext = "C11F22F20140505084483597E4370F43";
    seed = SEED(unhexlify(key));
    correct = (seed.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "SEED Encrypt Test 2: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (seed.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "SEED Decrypt Test 2: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    data = "00000000000000000000000000000000";
    key = "000102030405060708090A0B0C0D0E0F";
    ciphertext = "C11F22F20140505084483597E4370F43";
    seed = SEED(unhexlify(key));
    correct = (seed.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    all_correct &= correct;
    correct = (seed.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    all_correct &= correct;

    data = "B41E6BE2EBA84A148E2EED84593C5EC7";
    key = "28DBC3BC49FFD87DCFA509B11D422BE7";
    ciphertext = "9B9B7BFCD1813CB95D0B3618F40F5122";
    seed = SEED(unhexlify(key));
    correct = (seed.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "SEED Encrypt Test 3: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (seed.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "SEED Decrypt Test 3: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;


    // Skipjack;
    // http://jya.com/Skipjack-spec.htmIII.;
    data = "33221100ddccbbaa";
    key = "00998877665544332211";
    ciphertext = "2587cae27a12d300";
    Skipjack Skipjack(unhexlify(key));
    correct = (Skipjack.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "Skipjack Encrypt Test 1: \t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (Skipjack.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "Skipjack Decrypt Test 1: \t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;


    // TEA
    // http://edipermadi.files.wordpress.com/2009/01/the_implementation_of_tiny_encryption_algorithm_on_pic18f4550.pdf
    data = "0123456789abcdef";
    key = "00112233445566778899aabbccddeeff";
    ciphertext = "126c6b92c0653a3e";
    TEA tea(unhexlify(key));
    correct = (tea.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "TEA Encrypt Test 1: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (tea.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "TEA Decrypt Test 1: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;


    // XTEA
    // http://www.3amsystems.com/monetics/vectors.htm
    data = "4142434445464748";
    key = "000102030405060708090a0b0c0d0e0f";
    ciphertext = "497df3d072612cb5";
    XTEA xtea(unhexlify(key));
    correct = (xtea.encrypt(unhexlify(data)) == unhexlify(ciphertext));
    stream << "XTEA Encrypt Test 1: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;
    correct = (xtea.decrypt(unhexlify(ciphertext)) == unhexlify(data));
    stream << "XTEA Decrypt Test 1: \t\t\t" << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    return all_correct;
}

std::vector <std::string> test_all(uint64_t bytes){
    // Results are in MB/s
    std::vector <std::string> out;
    std::stringstream stream;
    stream << "Benchmarking with " << bytes << " of data";
    out.push_back(stream.str()); stream.str("");
    stream << "Results are in MB/s";
    out.push_back(stream.str()); stream.str("");
    stream << "AES...................." << benchmark<AES>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << "Blowfish..............." << benchmark<Blowfish>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << "Camellia..............." << benchmark<Camellia>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << "CAST128................" << benchmark<CAST128>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << "CAST256................" << benchmark<CAST256>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << "DES...................." << benchmark<DES>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << "IDEA..................." << benchmark<IDEA>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << "RC2...................." << benchmark<RC2>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << "RC4...................." << benchmark<RC4>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << "RC5...................." << benchmark<RC5>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << "RC6...................." << benchmark<RC6>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << "SAFERK64..............." << benchmark<SAFERK64>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << "SEED..................." << benchmark<SEED>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << "Skipjack..............." << benchmark<Skipjack>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << "TEA...................." << benchmark<TEA>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << "XTEA..................." << benchmark<XTEA>(bytes);
    out.push_back(stream.str());
    return out;
}
