/*
A bunch of useful constants and functions.
Some functions were heavily influenced by python 2.7.2
*/

#ifndef __INCLUDES__
#define __INCLUDES__

#include <cstdint>
#include <iostream>
#include <sstream>
#include <stdexcept>

// Some useful constants
static const std::string zero(1, 0);
static const uint8_t  mod8  = 0xffU;
static const uint16_t mod16 = 0xffffU;
static const uint32_t mod32 = 0xffffffffUL;
static const uint64_t mod64 = 0xffffffffffffffffULL;

// string to integer
uint64_t toint(const std::string & s, const int & base = 10);

// flip the order of the octets
// base = 2 for binary source
//        16 for hex source
//        256 for ASCII source
std::string little_end(const std::string & str, const unsigned int & base = 16);

// Changes a numeric value into its binary string
template <typename T> std::string makebin(T value, unsigned int size = 8 * sizeof(T)){
    std::string out(size, '0');
    if (!size){
        out = "";
        while (value){
            out = "01"[value & 1] + out;
            value >>= 1;
        }
        return out;
    }
    while (value && size){
        out[--size] = "01"[value & 1];
        value >>= 1;
    }
    return out;
}

// Thanks to Ben Voigt @ stackoverflow for the makehex function
// which I then adapted to makebin
// Changes a  numeric value to its hexadecimal string
template <typename T> std::string makehex(T value, unsigned int size = 2 * sizeof(T), bool caps = false){
    if (!size){
        std::stringstream out;
        out << std::hex << value;
        return out.str();
    }

    std::string out(size, '0');
    while (value && size){
        if (caps){
            out[--size] = "0123456789ABCDEF"[value & 15];
        }
        else{
            out[--size] = "0123456789abcdef"[value & 15];
        }
        value >>= 4;
    }
    return out;
}

// extract 8 bits from a numeric value
template <typename T> uint8_t byte(const T & value, const uint16_t & n){
    return (value >> (n << 3)) & 0xff;
}

// direct binary to hex string
std::string bintohex(const std::string & in, bool caps = false);

// convert an ASCII string into a string of 0s and 1s
std::string binify(const std::string & in, unsigned int size = 0);

// character to string of 0s and 1s
std::string binify(unsigned char c);

// string of 0s and 1s to ASCII
std::string unbinify(const std::string & in);

// ASCII string to hex string
std::string hexlify(const std::string & in, bool caps = false);

// character to hex string
std::string hexlify(const char in, bool caps = false);

// hex string to ASCII string
std::string unhexlify(const std::string & in);

std::string pkcs5(const std::string & data, const unsigned int & blocksize);

std::string remove_pkcs5(std::string data);

// adds characters to the front of the string
std::string zfill(const std::string & str, const unsigned int & n, const char fill);

// Left rotate a string
std::string ROL(const std::string & str, const std::size_t bits);

// and two strings, up to the last character of the shorter string
std::string and_strings(const std::string & str1, const std::string & str2);

// or two strings, up to the last character of the shorter string
std::string or_strings(const std::string & str1, const std::string & str2);

// xor the contents of 2 strings, up to the last character of the shorter string
std::string xor_strings(const std::string & str1, const std::string & str2);

#endif
