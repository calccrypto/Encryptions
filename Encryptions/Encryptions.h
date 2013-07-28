/*
A C++ library of encryption alogorithms
by Jason Lee @ calccrypto at gmail.com

IMPORTANT:
    This library was not written for actual use.
    Rather, it was meant for educational purposes,
    so if you choose to use it in a real setting
    where secrecy is requied, do so at your own risk.
    People who use this library to learn about the
    algorithms can easily add a few std::couts to
    see the internal data.

Algorithms:
    AES 128/192/256
    Blowfish
    Camellia 128/192/256
    CAST-128 aka CAST5
    CAST-256 aka CAST6
    DES
    DES-X
    GOST 28147-89
    IDEA
    MISTY1
    RC2
    RC4 (Allegedly)
    RC5-32/12/16 (can be changed)
    RC6-32/20 (can be changed)
    SAFER K-64
    SEED
    Skipjack
    Triple DES
    TEA
    XTEA

Modes of Operation (mod_op):
    Electronic Codebook (ECB)
    Cipher - Block Chaining (CBC)
    Cipher Feedback (CFB)
    Counter (CTR)
    Output Feedback (OFB)
    Propagating Cipher - Block Chaining (PCBC)

Notes:
    Algorithms:
        All above algorithms are derived from the "SymAlg" class,
        which is used in the Mode of Operations template.

        Algorithms will expect eactly 1 block or b bits of data in
        8 bit ASCII, where b is the block size of the algorithm in
        bits. If there are less than b bits, the algorithm might
        crash If there are more, only the first b bits will be
        operated on.

        The keying algorithms will do the same, unless there are
        defined padding methods.

        blocksize() returns the blocksize in bits

        Data padding is a hopefully correct implementation of PKCS5

    Modes of Operation:
        Only the general ideas of how each Mode of Operation works is used.
        If any of the included algorithm has a specific method of runing
        under a certain Mode of Operaion, it was probably not programmed.

        The default Initialization Vector is just a series of 0s.

Build:
	make (creates the object files only)

	or

	g++ -std=c++11 main.cpp common/*.cpp Encryptions/*.cpp

	or some equivalent

	You have to provide the main function/file since this is a library,
	not a fully functioning program.

Usage:
    'instance' is an instance of an algorithm
    'key' is a string that is one key long for any algorithm
    'plaintext' is a one block long string of non encrypted data
    'ciphertext' is a one block long string of encrypted data

    To run the algorithms seperately (run on only 1 block), simply use '.encrypt(data)'
    to encrypt or '.decrypt(data)' to decrypt, since the key has already been expanded.

    Ex:
        AES instance(key)
        ciphertext = instance.encrypt(plaintext)

    To encrypt or decrypt data using a Mode of Operation function, Simply create an instance of the mod_op.
    The input is the entire data in one string.
        Notes:
            * ECB mode does not require an IV.
            * Modes CFB, CTR, and OFB are always in encrypt mode (already programmed in)
            * The other modes can use encrypt or decrypt instances of the algorithms
            * IV are hex strings of any length, preferably one block long
            * Any input with default value NULL can have any input. It does not matter
    Ex:
        Encrypting using CBC mode on AES:
            SymAlg * instance = new AES(key)
            data = CBC(instance, IV).encrypt(plaintext1 + plaintext2 + ... + plaintextN)
            free(instance)
*/

#ifndef ENCRYPTIONS_H
#define ENCRYPTIONS_H

#include <ctime>

// common includes
#include "../common/includes.h"
#include "../common/cryptomath.h"
#include "error.h"
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
#include "XTEA.h"

// Modes of Operation
#include "ECB.h"
#include "CBC.h"
#include "CFB.h"
#include "CTR.h"
#include "OFB.h"
#include "PCPB.h"

// Check if all symmetric algorithms pass some Known Value Tests
bool validate_symalg(std::ostream & stream = null_out, bool do_1000000_check = false);

// Do a simple benchmark of a symmetric algorithm
template <class algorithm> double benchmark(uint64_t bytes = 1024){
    std::string key(32, '\xff');
    algorithm current(key);
    uint8_t blocksize = current.blocksize() >> 3;
    std::string data(blocksize, '\x00');
    uint64_t loops = bytes / blocksize;
    time_t start = clock();
    for(uint64_t x = 0; x < loops; x++){
        current.encrypt(data);
    }
    time_t end = clock();
    return (double) bytes * CLOCKS_PER_SEC / (float(end - start) * 1048576);
}
// Benchmark all symmetric algorithms
std::vector <std::string> test_all(uint64_t bytes = 1024);

#endif
