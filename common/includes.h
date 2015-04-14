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
const std::string zero("\x00", 1);
const std::string b = "01";
const std::string d = b + "23456789";
const std::string h_lower = d + "abcdef";
const std::string h_upper = d + "ABCDEF";
const uint8_t mod8 = 0xffU;
const uint16_t mod16 = 0xffffU;
const uint32_t mod32 = 0xffffffffUL;
const uint64_t mod64 = 0xffffffffffffffffULL;

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
            out = b[value & 1] + out;
            value >>= 1;
        }
        return out;
    }
    while (value && size){
        out[--size] = b[value & 1];
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
        if (!caps){
            out[--size] = h_lower[value & 15];
        }
        else{
            out[--size] = h_upper[value & 15];
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

std::string remove_padding(std::string data);

// add to front of string
std::string zfill(const std::string & str, const unsigned int & n, const char fill = 0); 

// adds to back of string
std::string pad(const std::string & str, const unsigned int & n, const char fill = 0); 

// xor the contents of 2 strings, up to the last character of the shorter string
std::string xor_strings(const std::string & str1, const std::string & str2); 

// ////////////////////////////////////////////////////////////////////////////////
// Thanks to Xeo @ stackoverflow
// http://stackoverflow.com/questions/6240950/platform-independent-dev-null-in-c
template<typename Ch, typename Traits = std::char_traits<Ch> >
struct basic_nullbuf : std::basic_streambuf<Ch, Traits> {
	typedef std::basic_streambuf<Ch, Traits> base_type;
	typedef typename base_type::int_type int_type;
	typedef typename base_type::traits_type traits_type;

	virtual int_type overflow(int_type c) {
		return traits_type::not_eof(c);
	}
};

// convenient typedefs
typedef basic_nullbuf<char> nullbuf;
typedef basic_nullbuf<wchar_t> wnullbuf;

// buffers and streams
// in some .h
extern std::ostream null_out;
extern std::wostream wnull_out;

//// in a concrete .cpp
//nullbuf null_obj;
//wnullbuf wnull_obj;
//std::ostream null_out(&null_obj);
//std::wostream wnull_out(&wnull_obj);
//// ////////////////////////////////////////////////////////////////////////////////
#endif
