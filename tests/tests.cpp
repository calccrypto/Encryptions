/*
A few Known Answer Tests for the Symmetric Algorithms
*/

#include <chrono>
#include <iostream>

#include "../Encryptions.h"

// check if a symmetric algorithm outputs expected values
// plaintext, key, and ciphertext should be in hex
template <typename Alg> bool validate_symalg(const std::string & plaintext, const std::string & key, const std::string & ciphertext, std::ostream & stream = null_out, const std::string & name = "", const unsigned int & linew = 40){
    Alg alg(unhexlify(key));
    bool correct = (alg.encrypt(unhexlify(plaintext)) == unhexlify(ciphertext));
    stream << pad(name + " Encrypt:", linew, ' ') << (correct?"Passed":"Failed") << std::endl;
    correct &= (alg.decrypt(unhexlify(ciphertext)) == unhexlify(plaintext));
    stream << pad(name + " Decrypt:", linew, ' ') << (correct?"Passed":"Failed") << std::endl;
    return correct;
}

bool validate_all_symalg(std::ostream & stream = null_out, const bool do_1000000_check = false, const unsigned int & linew = 40){
    // Known Answer Test (KAT) to check if all the algorihtms are correct
    bool all_correct = true, correct;

    // AES 128, 192, 256
    // http://csrc.nist.gov/publications/fips/fips197/fips-197.pdf
    all_correct &= validate_symalg <AES>   ("00112233445566778899aabbccddeeff",
                                            "000102030405060708090a0b0c0d0e0f",
                                            "69c4e0d86a7b0430d8cdb78070b4c55a",
                                            stream, "AES 128 Bit Key", linew);

    all_correct &= validate_symalg <AES>   ("00112233445566778899aabbccddeeff",
                                            "000102030405060708090a0b0c0d0e0f1011121314151617",
                                            "dda97ca4864cdfe06eaf70a0ec0d7191",
                                            stream, "AES 192 Bit Key", linew);

    all_correct &= validate_symalg <AES>   ("00112233445566778899aabbccddeeff",
                                            "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f",
                                            "8ea2b7ca516745bfeafc49904b496089",
                                            stream, "AES 256 Bit Key", linew);


    // Blowfish
    // http://www.schneier.com/code/vectors.txt
    all_correct &= validate_symalg <Blowfish>  ("480D39006EE762F2",
                                                "025816164629B007",
                                                "7555AE39F59B87BD",
                                                stream, "Blowfish Test 1", linew);

    all_correct &= validate_symalg <Blowfish>  ("437540C8698F3CFA",
                                                "49793EBC79B3258F",
                                                "53C55F9CB49FC019",
                                                stream, "Blowfish Test 2", linew);


    // Camellia
    // RFC3713
    // 128-bit key
    all_correct &= validate_symalg <Camellia>  ("0123456789abcdeffedcba9876543210",
                                                "0123456789abcdeffedcba9876543210",
                                                "67673138549669730857065648eabe43",
                                                stream, "Camellia 128 Bit Key", linew);
    // 192-bit key
    all_correct &= validate_symalg <Camellia>  ("0123456789abcdeffedcba9876543210",
                                                "0123456789abcdeffedcba98765432100011223344556677",
                                                "b4993401b3e996f84ee5cee7d79b09b9",
                                                stream, "Camellia 192 Bit Key", linew);
    //256-bitkey
    all_correct &= validate_symalg <Camellia>  ("0123456789abcdeffedcba9876543210",
                                                "0123456789abcdeffedcba987654321000112233445566778899aabbccddeeff",
                                                "9acc237dff16d76c20ef7c919e3a7509",
                                                stream, "Camellia 256 Bit Key", linew);


    // CAST-128;
    // RFC2144;
    // 40-bit
    all_correct &= validate_symalg <CAST128>  ("0123456789ABCDEF",
                                                "0123456712",
                                                "7AC816D16E9B302E",
                                                stream, "CAST-128 40 Bit Key", linew);
    // 80-bit
    all_correct &= validate_symalg <CAST128>  ("0123456789ABCDEF",
                                                "01234567123456782345",
                                                "EB6A711A2C02271B",
                                                stream, "CAST-128 80 Bit Key", linew);
    // 128-bit
    all_correct &= validate_symalg <CAST128>  ("0123456789ABCDEF",
                                               "0123456712345678234567893456789A",
                                               "238B4FE5847E44B2",
                                               stream, "CAST-128 128 Bit Key", linew);

    // Full Maintenance Test
    if (do_1000000_check){
        std::string a = unhexlify("0123456712345678234567893456789A");
        std::string b = unhexlify("0123456712345678234567893456789A");
        for(uint32_t x = 0; x < 1000000; x++){;
            a = CAST128(b).encrypt(a.substr(0,8)) + a.substr(8,8);
            a = a.substr(0,8) + CAST128(b).encrypt(a.substr(8,8));
            b = CAST128(a).encrypt(b.substr(0,8)) + b.substr(8,8);
            b = b.substr(0,8) + CAST128(a).encrypt(b.substr(8,8));
        };
        correct = ((a == unhexlify("EEA9D0A249FD3BA6B3436FB89D6DCA92")) && (b == unhexlify("B2C95EB00C31AD7180AC05B8E83D696E")));
        stream << "CAST-128 Full Maintenance Test: \t" << (correct?"Passed":"Failed") << std::endl;
        all_correct &= correct;
    }


    // CAST-256;
    // RFC2612;
    // 128 bit
    all_correct &= validate_symalg <CAST256>  ("00000000000000000000000000000000",
                                               "2342bb9efa38542c0af75647f29f615d",
                                               "c842a08972b43d20836c91d1b7530f6b",
                                               stream, "CAST-256 128 Bit Key", linew);
    // 192 bit
    all_correct &= validate_symalg <CAST256>  ("00000000000000000000000000000000",
                                               "2342bb9efa38542cbed0ac83940ac298bac77a7717942863",
                                               "1b386c0210dcadcbdd0e41aa08a7a7e8",
                                               stream, "CAST-256 192 Bit Key", linew);
    // 256 bit
    all_correct &= validate_symalg <CAST256>  ("00000000000000000000000000000000",
                                               "2342bb9efa38542cbed0ac83940ac2988d7c47ce264908461cc1b5137ae6b604",
                                               "4f6a2038286897b9c9870136553317fa",
                                               stream, "CAST-256 256 Bit Key", linew);


    // DES
    // http://orlingrabbe.com/des.htm
    all_correct &= validate_symalg <DES>  ("0123456789ABCDEF",
                                           "133457799BBCDFF1",
                                           "85E813540F0AB405",
                                           stream, "DES Test 1", linew);

    all_correct &= validate_symalg <DES>  ("8787878787878787",
                                           "0E329232EA6D0D73",
                                           "0000000000000000",
                                           stream, "DES Test 2", linew);


    // saferk64 28147-89
    // http://dl.packetstormsecurity.net/crypt/LIBS/saferk64/gutmann
    GOST gost(unhexlify("3031323330313233303132333031323330313233303132333031323330313233"), DES_sbox);
    correct = (gost.encrypt(unhexlify("3031323330313233")) == unhexlify("f56b8a589f6f7417"));
    stream << pad("gost Test 1 Encrypt:", linew, ' ') << (correct?"Passed":"Failed") << std::endl;
    correct = (gost.decrypt(unhexlify("f56b8a589f6f7417")) == unhexlify("3031323330313233"));
    stream << pad("gost Test 1 Decrypt:", linew, ' ') << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;



    // IDEA
    // http://www.unsw.adfa.edu.au/~lpb/src/IDEAcalc/index.html
    all_correct &= validate_symalg <IDEA> ("05320a6414c819fa",
                                           "006400c8012c019001f4025802bc0320",
                                           "65be87e7a2538aed",
                                           stream, "IDEA Test 1", linew);

    // http://www.informationsuebertragung.ch/indexAlgorithmen.html
    all_correct &= validate_symalg <IDEA> ("0000000100020003",
                                           "00010002000300040005000600070008",
                                           "11fbed2b01986de5",
                                           stream, "IDEA Test 2", linew);


    // MISTY1
    // RFC 2994
    all_correct &= validate_symalg <MISTY1> ("0123456789abcdef",
                                             "00112233445566778899aabbccddeeff",
                                             "8b1da5f56ab3d07c",
                                             stream, "MISTY1 Test 1", linew);

    all_correct &= validate_symalg <MISTY1> ("fedcba9876543210",
                                             "00112233445566778899aabbccddeeff",
                                             "04b68240b13be95d",
                                             stream, "MISTY1 Test 2", linew);


    // RC4;
    // http://groups.google.com/group/sci.crypt/msg/10a300c9d21afca0
    all_correct &= validate_symalg <RC4> ("0123456789abcdef",
                                          "0123456789abcdef",
                                          "75b7878099e0c596",
                                          stream, "RC4 Test 1", linew);

    all_correct &= validate_symalg <RC4> ("0000000000000000",
                                          "0123456789abcdef",
                                          "7494c2e7104b0879",
                                          stream, "RC4 Test 2", linew);

    all_correct &= validate_symalg <RC4> ("0000000000000000",
                                          "0000000000000000",
                                          "de188941a3375d3a",
                                          stream, "RC4 Test 3", linew);

    all_correct &= validate_symalg <RC4> ("00000000000000000000",
                                          "ef012345",
                                          "d6a141a7ec3c38dfbd61",
                                          stream, "RC4 Test 4", linew);


    // RC5;
    // From the paper;
    all_correct &= validate_symalg <RC5> ("0000000000000000",
                                          "00000000000000000000000000000000",
                                          "eedba5216d8f4b15",
                                          stream, "RC5 Test 1", linew);

    all_correct &= validate_symalg <RC5> ("eedba5216d8f4b15",
                                          "915f4619be41b2516355a50110a9ce91",
                                          "ac13c0f752892b5b",
                                          stream, "RC5 Test 2", linew);

    all_correct &= validate_symalg <RC5> ("ac13c0f752892b5b",
                                          "783348e75aeb0f2fd7b169bb8dc16787",
                                          "b7b3422f92fc6903",
                                          stream, "RC5 Test 3", linew);

    all_correct &= validate_symalg <RC5> ("b7b3422f92fc6903",
                                          "dc49db1375a5584f6485b413b5f12baf",
                                          "b278c165cc97d184",
                                          stream, "RC5 Test 4", linew);

    all_correct &= validate_symalg <RC5> ("b278c165cc97d184",
                                          "5269f149d41ba0152497574d7f153125",
                                          "15e444eb249831da",
                                          stream, "RC5 Test 4", linew);


    // RC6
    // From the paper
    all_correct &= validate_symalg <RC6> ("00000000000000000000000000000000",
                                          "00000000000000000000000000000000",
                                          "8fc3a53656b1f778c129df4e9848a41e",
                                          stream, "RC6 Test 1", linew);

    all_correct &= validate_symalg <RC6> ("02132435465768798a9bacbdcedfe0f1",
                                          "0123456789abcdef0112233445566778",
                                          "524e192f4715c6231f51f6367ea43f18",
                                          stream, "RC6 Test 2", linew);

    all_correct &= validate_symalg <RC6> ("00000000000000000000000000000000",
                                          "000000000000000000000000000000000000000000000000",
                                          "6cd61bcb190b30384e8a3f168690ae82",
                                          stream, "RC6 Test 3", linew);

    all_correct &= validate_symalg <RC6> ("02132435465768798a9bacbdcedfe0f1",
                                          "0123456789abcdef0112233445566778899aabbccddeeff0",
                                          "688329d019e505041e52e92af95291d4",
                                          stream, "RC6 Test 4", linew);

    all_correct &= validate_symalg <RC6> ("00000000000000000000000000000000",
                                          "0000000000000000000000000000000000000000000000000000000000000000",
                                          "8f5fbd0510d15fa893fa3fda6e857ec2",
                                          stream, "RC6 Test 5", linew);

    all_correct &= validate_symalg <RC6> ("02132435465768798a9bacbdcedfe0f1",
                                          "0123456789abcdef0112233445566778899aabbccddeeff01032547698badcfe",
                                          "c8241816f0d7e48920ad16a1674e5d48",
                                          stream, "RC6 Test 6", linew);


    // SAFER K-64
    // From the paper
    SAFERK64 saferk64(unhexlify("0807060504030201"), 6);
    correct = (saferk64.encrypt(unhexlify("0102030405060708")) == unhexlify("c8f29cdd87783ed9"));
    stream << pad("SAFER K-64 6 Rounds Test 1 Encrypt:", linew, ' ') << (correct?"Passed":"Failed") << std::endl;
    correct = (saferk64.decrypt(unhexlify("c8f29cdd87783ed9")) == unhexlify("0102030405060708"));
    stream << pad("SAFER K-64 6 Rounds Test 1 Decrypt:", linew, ' ') << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;

    saferk64 = SAFERK64(unhexlify("0000000000000000"), 6);
    correct = (saferk64.encrypt(unhexlify("0102030405060708")) == unhexlify("7d28038633b92eb4"));
    stream << pad("SAFER K-64 6 Rounds Test 2 Encrypt:", linew, ' ') << (correct?"Passed":"Failed") << std::endl;
    correct = (saferk64.decrypt(unhexlify("7d28038633b92eb4")) == unhexlify("0102030405060708"));
    stream << pad("SAFER K-64 6 Rounds Test 2 Decrypt:", linew, ' ') << (correct?"Passed":"Failed") << std::endl;
    all_correct &= correct;


    // SEED;
    // From somewhere
    all_correct &= validate_symalg <SEED> ("000102030405060708090A0B0C0D0E0F",
                                           "00000000000000000000000000000000",
                                           "5EBAC6E0054E166819AFF1CC6D346CDB",
                                           stream, "SEED Test 1", linew);

    all_correct &= validate_symalg <SEED> ("00000000000000000000000000000000",
                                           "000102030405060708090A0B0C0D0E0F",
                                           "C11F22F20140505084483597E4370F43",
                                           stream, "SEED Test 2", linew);

    all_correct &= validate_symalg <SEED> ("B41E6BE2EBA84A148E2EED84593C5EC7",
                                           "28DBC3BC49FFD87DCFA509B11D422BE7",
                                           "9B9B7BFCD1813CB95D0B3618F40F5122",
                                           stream, "SEED Test 3", linew);


    // Skipjack;
    // http://jya.com/Skipjack-spec.htmIII.;
    all_correct &= validate_symalg <Skipjack> ("33221100ddccbbaa",
                                               "00998877665544332211",
                                               "2587cae27a12d300",
                                               stream, "Skipjack Test 1", linew);


    // TEA
    // http://edipermadi.files.wordpress.com/2009/01\the_implementation_of_tiny_encryption_algorithm_on_pic18f4550.pdf
    all_correct &= validate_symalg <TEA> ("0123456789abcdef",
                                          "00112233445566778899aabbccddeeff",
                                          "126c6b92c0653a3e",
                                          stream, "TEA Test 1", linew);


    // Twofish
    // https://github.com/calccrypto/OpenPGP/blob/master/tests/testcases/test_twofish_ecb.cpp
    // -> https://www.schneier.com/code/twofish-kat.zip
    all_correct &= validate_symalg <Twofish> ("00000000000000000000000000000000",
                                              "00000000000000000000000000000000",
                                              "9F589F5CF6122C32B6BFEC2F2AE8C35A",
                                              stream, "Twofish 128", linew);

    all_correct &= validate_symalg <Twofish> ("00000000000000000000000000000000",
                                              "0123456789ABCDEFFEDCBA98765432100011223344556677",
                                              "CFD1D2E5A9BE9CDF501F13B892BD2248",
                                              stream, "Twofish 192", linew);

    all_correct &= validate_symalg <Twofish> ("00000000000000000000000000000000",
                                              "0123456789ABCDEFFEDCBA987654321000112233445566778899AABBCCDDEEFF",
                                              "37527BE0052334B89F0CFCCAE87CFA20",
                                              stream, "Twofish 256", linew);


    // XTEA
    // http://www.3amsystems.com/monetics/vectors.htm
    all_correct &= validate_symalg <XTEA> ("4142434445464748",
                                           "000102030405060708090a0b0c0d0e0f",
                                           "497df3d072612cb5",
                                           stream, "XTEA Test 1", linew);

    return all_correct;
}

// Do a simple benchmark of a symmetric algorithm
template <class Alg> double benchmark(const uint64_t & bytes = 1024){
    std::string key(32, 0xff);
    Alg current(key);
    uint8_t blocksize = current.blocksize() >> 3;
    std::string data(blocksize, 0);
    uint64_t loops = bytes / blocksize;
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(uint64_t x = 0; x < loops; x++){
        current.encrypt(data);
    }
    return std::chrono::duration_cast<std::chrono::duration<double> >(std::chrono::high_resolution_clock::now() - start).count();
}

std::vector <std::string> test_all(const uint64_t & bytes = 1024){
    // Results are in MB/s
    std::vector <std::string> out;
    std::stringstream stream;
    stream << "Benchmarking with " << bytes << " of data";
    out.push_back(stream.str()); stream.str("");
    stream << "Results are in MB/s";
    out.push_back(stream.str()); stream.str("");
    stream << zfill("AES", 20, '.') << benchmark<AES>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << zfill("Blowfish", 20, '.') << benchmark<Blowfish>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << zfill("Camellia", 20, '.') << benchmark<Camellia>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << zfill("CAST128", 20, '.') << benchmark<CAST128>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << zfill("CAST256", 20, '.') << benchmark<CAST256>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << zfill("DES", 20, '.') << benchmark<DES>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << zfill("IDEA", 20, '.') << benchmark<IDEA>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << zfill("RC2", 20, '.') << benchmark<RC2>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << zfill("RC4", 20, '.') << benchmark<RC4>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << zfill("RC5", 20, '.') << benchmark<RC5>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << zfill("RC6", 20, '.') << benchmark<RC6>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << zfill("SAFERK64", 20, '.') << benchmark<SAFERK64>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << zfill("SEED", 20, '.') << benchmark<SEED>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << zfill("Skipjack", 20, '.') << benchmark<Skipjack>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << zfill("TEA", 20, '.') << benchmark<TEA>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << zfill("Twofish", 20, '.') << benchmark<Twofish>(bytes);
    out.push_back(stream.str()); stream.str("");
    stream << zfill("XTEA", 20, '.') << benchmark<XTEA>(bytes);
    out.push_back(stream.str());
    return out;
}

int main(){
    std::cout << "\n\n"
              << (validate_all_symalg(std::cout)?std::string("Passed"):std::string("Failed"))
              << std::endl;
    return 0;
}