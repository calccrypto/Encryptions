#ifndef ENCRYPTIONS_H
#define ENCRYPTIONS_H

#include <chrono>

// common includes
#include "../common/includes.h"
#include "../common/cryptomath.h"
#include "SymAlg.h"

// Algorithms
#include "AES.h"
#include "Blowfish.h"
#include "Camellia.h"
#include "CAST128.h"
#include "CAST256.h"
#include "DES.h"
#include "DESX.h"
#include "GOST.h"
#include "IDEA.h"
#include "MISTY1.h"
#include "RC2.h"
#include "RC4.h"
#include "RC5.h"
#include "RC6.h"
#include "SAFERK64.h"
#include "SEED.h"
#include "Skipjack.h"
#include "TDES.h"
#include "TEA.h"
#include "Twofish.h"
#include "XTEA.h"

// Modes of Operation
#include "ECB.h"
#include "CBC.h"
#include "CFB.h"
#include "CTR.h"
#include "OFB.h"
#include "PCPB.h"

// Check if all symmetric algorithms pass some Known Value Tests
bool validate_symalg(std::ostream & stream = null_out, const bool do_1000000_check = false);

// Do a simple benchmark of a symmetric algorithm
template <class algorithm> double benchmark(const uint64_t & bytes = 1024){
    std::string key(32, 0xff);
    algorithm current(key);
    uint8_t blocksize = current.blocksize() >> 3;
    std::string data(blocksize, 0);
    uint64_t loops = bytes / blocksize;
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    for(uint64_t x = 0; x < loops; x++){
        current.encrypt(data);
    }
    return std::chrono::duration_cast<std::chrono::duration<double> >(std::chrono::high_resolution_clock::now() - start).count();
}
// Benchmark all symmetric algorithms
std::vector <std::string> test_all(const uint64_t & bytes = 1024);
#endif