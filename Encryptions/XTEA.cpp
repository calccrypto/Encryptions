#include "XTEA.h"

XTEA::XTEA()
    : SymAlg(),
    delta(0), cycles(0), total(0), key()
{}

XTEA::XTEA(const std::string & KEY, const uint8_t & ROUNDS, const uint32_t & DELTA) //, const uint32_t & TOTAL = 0xc6ef3720){
    : XTEA()
{
    setkey(KEY, ROUNDS, DELTA);
}

void XTEA::setkey(const std::string & KEY, const uint8_t & ROUNDS, const uint32_t & DELTA){
    if (keyset){
        throw std::runtime_error("Error: Key has already been set.");
    }

    if (KEY.size() != 16){
        throw std::runtime_error("Error: Key must be 128 bits in length.");
    }

    delta = DELTA;
    cycles = ROUNDS >> 1;
    for(uint8_t x = 0; x < 4; x++){
        key[x] = static_cast <uint32_t> (toint(KEY.substr(x << 2, 4), 256));
    }
    keyset = true;
}

std::string XTEA::encrypt(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }

    if (DATA.size() != 8){
        throw std::runtime_error("Error: Data must be 64 bits in length.");
    }

    uint32_t data[2] = {static_cast <uint32_t> (toint(DATA.substr(0, 4), 256)), static_cast <uint32_t> (toint(DATA.substr(4, 4), 256))};
    total = 0;
    for(uint8_t i = 0; i < cycles; i++){
        data[0] += (((data[1] << 4) ^ (data[1] >> 5)) + data[1]) ^ (total + key[total & 3]);
        total += delta;
        data[1] += (((data[0] << 4) ^ (data[0] >> 5)) + data[0]) ^ (total + key[(total >> 11) & 3]);
    }
    return unhexlify(makehex(data[0], 8) + makehex(data[1], 8));
}

std::string XTEA::decrypt(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }

    if (DATA.size() != 8){
        throw std::runtime_error("Error: Data must be 64 bits in length.");
    }

    uint32_t data[2] = {static_cast <uint32_t> (toint(DATA.substr(0, 4), 256)), static_cast <uint32_t> (toint(DATA.substr(4, 4), 256))};
    total = delta * cycles;
    for(uint8_t i = 0; i < cycles; i++){
        data[1] -= (((data[0] << 4) ^ (data[0] >> 5)) + data[0]) ^ (total + key[(total >> 11) & 3]);
        total -= delta;
        data[0] -= (((data[1] << 4) ^ (data[1] >> 5)) + data[1]) ^ (total + key[total & 3]);
    }
    return unhexlify(makehex(data[0], 8) + makehex(data[1], 8));
}

unsigned int XTEA::blocksize() const {
    return 64;
}
