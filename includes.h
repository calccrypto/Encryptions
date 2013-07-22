/*
A bunch of useful constants and functions.
Some functions were heavily influenced by python 2.7.2
*/
#include <algorithm>
#include <iostream>
#include <sstream>

#ifndef __INCLUDES__
#define __INCLUDES__

// Some useful constants
const std::string zero("\x00", 1);
const std::string b = "01";
const std::string d = b + "23456789";
const std::string h = d + "abcdef";
const uint8_t mod8 = 0xffU;
const uint16_t mod16 = 0xffffU;
const uint32_t mod32 = 0xffffffffUL;
const uint64_t mod64 = 0xffffffffffffffffULL;

uint64_t toint(const std::string & s, const int & base = 10);
std::string little_end(const std::string & str, const unsigned int & base = 16);
template <typename T> std::string makebin(T value, unsigned int size = 8 * sizeof(T)){
    // Changes a value into its binary string
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
template <typename T> std::string makehex(T value, unsigned int size = 2 * sizeof(T)){
    // Changes a value to its hexadecimal string
    if (!size){
        std::stringstream out;
        out << std::hex << value;
        return out.str();
    }
    std::string out(size, '0');
    while (value && size){
        out[--size] = h[value & 15];
        value >>= 4;
    }
    return out;
}

std::string bintohex(const std::string & in);
std::string hexlify(const std::string & in);
std::string hexlify(const char in);
std::string unhexlify(const std::string & in);
std::string pkcs5(const std::string & data, const unsigned int & blocksize);
std::string remove_padding(std::string data);
std::string zfill(std::string str, const unsigned int & n, const std::string & fill = "0");

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
