#include "./TEA.h"

TEA::TEA(){
    keyset = false;
}

TEA::TEA(const std::string & KEY, const uint32_t & ROUNDS, const uint32_t & DELTA, const uint32_t & TOTAL){
    keyset = false;
    setkey(KEY, ROUNDS, DELTA, TOTAL);
}

void TEA::setkey(const std::string & KEY, const uint32_t & ROUNDS, const uint32_t & DELTA, const uint32_t & TOTAL){
    if (keyset){
        std::cerr << "Error: Key has already been set." << std::endl;
        throw 1;
    }

    if (KEY.size() != 16){
        std::cerr << "Error: Key must be 128 bits in length." << std::endl;
        throw 1;
    }

    delta = DELTA;
    total = TOTAL;
    cycles = ROUNDS >> 1;
    for(uint8_t x = 0; x < 4; x++){
        key[x] = (uint32_t) toint(KEY.substr(x << 2, 4), 256);
    }
    keyset = true;
}

std::string TEA::encrypt(const std::string & DATA){
    if (!keyset){
        std::cerr << "Error: Key has not been set." << std::endl;
        throw 1;
    }

    if (DATA.size() != 8){
        std::cerr << "Error: Data must be 64 bits in length." << std::endl;
        throw 1;
    }

    uint32_t data[2] = {(uint32_t) toint(DATA.substr(0, 4), 256), (uint32_t) toint(DATA.substr(4, 4), 256)};
    total = 0;
    for(uint8_t i = 0; i < cycles; i++){
        total += delta;
        data[0] += ((data[1] << 4) + key[0]) ^ (data[1] + total) ^ ((data[1] >> 5) + key[1]);
        data[1] += ((data[0] << 4) + key[2]) ^ (data[0] + total) ^ ((data[0] >> 5) + key[3]);
    }
    return unhexlify(makehex(data[0], 8) + makehex(data[1], 8));
}

std::string TEA::decrypt(const std::string & DATA){
    if (!keyset){
        std::cerr << "Error: Key has not been set." << std::endl;
        throw 1;
    }

    if (DATA.size() != 8){
        std::cerr << "Error: Data must be 64 bits in length." << std::endl;
        throw 1;
    }

    uint32_t data[2] = {(uint32_t) toint(DATA.substr(0, 4), 256), (uint32_t) toint(DATA.substr(4, 4), 256)};
    for(uint8_t i = 0; i < cycles; i++){
        data[1] -= ((data[0] << 4) + key[2]) ^ (data[0] + total) ^ ((data[0] >> 5) + key[3]);
        data[0] -= ((data[1] << 4) + key[0]) ^ (data[1] + total) ^ ((data[1] >> 5) + key[1]);
        total -= delta;
    }
    return unhexlify(makehex(data[0], 8) + makehex(data[1], 8));
}

unsigned int TEA::blocksize(){
    return 64;
}
