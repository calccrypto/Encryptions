A C++ library of encryption algorithms

Copyright (c) 2013 - 2017 Jason Lee @ calccrypto at gmail.com

Please see LICENSE file for license.

[![Build Status](https://travis-ci.org/calccrypto/Encryptions.svg?branch=master)](https://travis-ci.org/calccrypto/Encryptions)
<pre>

IMPORTANT:
    This library was not written for actual use.
    Rather, it was meant for educational purposes,
    so if you choose to use it in a real setting
    where secrecy is required, do so at your own risk.
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
    Twofish
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
        bits. If there are the wrong number of bits, the algorithm
        should crash.

        The keying algorithms will do the same, unless there are
        defined padding methods.

        blocksize() returns the blocksize in bits

        Data padding is a hopefully correct implementation of PKCS5

    Modes of Operation:
        Only the general ideas of how each Mode of Operation works is used.
        If any of the included algorithm has a specific method of running
        under a certain Mode of Operation, it was probably not programmed.

        The default Initialization Vector is just a series of 0s.

Build:
    mkdir build
    cd build
    cmake ..
    make
    (optional) make test
    (optional) make install

Usage:
    'instance' is an instance of an algorithm
    'key' is a string that is one key long for any algorithm
    'plaintext' is a one block long string of non encrypted data
    'ciphertext' is a one block long string of encrypted data

    To run the algorithms separately (run on only 1 block), simply use '.encrypt(data)'
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
            delete(instance)
</pre>
