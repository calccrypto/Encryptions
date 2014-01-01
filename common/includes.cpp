#include "includes.h"

uint64_t toint(const std::string & s, const int & base){
    // Changees strings to uint64_t
    uint64_t value = 0;
    switch (base){
        case 2:
            for(const unsigned char & c : s){
                value = (value << 1) + ((uint8_t) c - '\x30');
            }
            break;
        case 8:
            std::stringstream(s) >> std::oct >> value;
            break;
        case 10:
            std::stringstream(s) >> std::dec >> value;
            break;
        case 16:
            std::stringstream(s) >> std::hex >> value;    // Thanks to Oli Charlesworth @ stackoverflow
            break;
        case 256:
            for(const unsigned char & c : s){
                value = (value << 8) + (uint8_t) c;
            }
            break;
        default:
            std::cerr << "InputError: toint() undefined for base: " << std::dec << base << std::endl;
            throw 1;
            break;
    };
    return value;
}

std::string little_end(const std::string & str, const unsigned int & base){
    // Changes a string to its little endian form
	int s = 8 * (base == 2) + 2 * (base == 16) + (base == 256);
	std::string t = "";
	for (uint32_t x = 0; x < str.size() / s; x++){
		t = str.substr(s * x, s)+ t;
    }
	return t;
}

std::string bintohex(const std::string & in, bool caps){
    // Changes a binary string to its hexadecimal equivalent
    if (in.size() % 4){
        std::cerr << "Error: input string length not a multiple of 4." << std::endl;
        throw 1;
    }
    std::string out = "";
    for(unsigned int x = 0; x < (in.size() >> 2); x++){
        out += makehex(toint(in.substr(x << 2, 4), 2), 1, caps);
    }
    return out;
}

std::string hexlify(const std::string & in, bool caps){
    // Changes an ASCII string to an ASCII string containing the
    // hexadecimal representation of the orignal chars
    std::string out = "";
    for(unsigned int x = 0; x < in.size(); x++){
        out += makehex((unsigned char) in[x], 2, caps);
    }
    return out;
}

std::string hexlify(const char in, bool caps){
    return makehex((uint8_t) in, 2, caps);
}

std::string unhexlify(const std::string & in){
	// Reverse hexlify
	if (in.size() & 1){
		std::cerr << "Error: input string of odd length." << std::endl;
        throw 1;
    }
    std::string out(in.size() >> 1, 0);
	for(unsigned int x = 0; x < in.size(); x += 2){
        if (('0' <= in[x]) && (in[x] <= '9')){
            out[x >> 1] = (uint8_t) ((in[x] - '0') << 4);
        }
        else if(('a' <= in[x]) && (in[x] <= 'f')){
            out[x >> 1] = (uint8_t) ((in[x] - 'a' + 10) << 4);
        }
        else if(('A' <= in[x]) && (in[x] <= 'F')){
            out[x >> 1] = (uint8_t) ((in[x] - 'A' + 10) << 4);
        }
        else{
            std::cerr << "Error: Invalid character found: " << (char) in[x] << std::endl;
            throw 1;
        }
        if (('0' <= in[x + 1]) && (in[x + 1] <= '9')){
            out[x >> 1] |= (uint8_t) (in[x + 1] - '0');
        }
        else if(('a' <= in[x + 1]) && (in[x + 1] <= 'f')){
            out[x >> 1] |= (uint8_t) (in[x + 1] - 'a' + 10);
        }
        else if(('A' <= in[x + 1]) && (in[x + 1] <= 'F')){
            out[x >> 1] |= (uint8_t) (in[x + 1] - 'A' + 10);
        }
        else{
            std::cerr << "Error: Invalid character found: " << (char) in[x + 1] << std::endl;
            throw 1;
        }
    }
	return out;
}

std::string pkcs5(const std::string & data, const unsigned int & blocksize){
    // Adds PKCS5 Padding
	int pad = ((blocksize - data.size()) % blocksize) % blocksize;
	std::string padding(pad, (char) pad);
	return data + padding;
}

std::string remove_padding(std::string data){
	// Removes PKCS Padding
	uint8_t pad = (uint8_t) data[data.size() - 1];
	std::string padding(pad, (char) pad);
	if ((pad < data.size()) && (padding == data.substr(data.size() - pad, pad)))
		data = data.substr(0, data.size() - pad);
	return data;
}

std::string zfill(std::string str, const unsigned int & n, const std::string & fill){
    // adds (default "0") octets to the front of the string so it doesnt change the value if the string is meant to be changed to an int
	while (str.size() < n){
		str = fill + str;
    }
	return str;
}

nullbuf null_obj;
wnullbuf wnull_obj;
std::ostream null_out(&null_obj);
std::wostream wnull_out(&wnull_obj);
