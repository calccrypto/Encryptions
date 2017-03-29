#include "GOST.h"

// GOST 28147-89
uint32_t GOST::CM1(const uint32_t a, const uint32_t b){
    return static_cast <uint32_t> (a + b);
}

uint32_t GOST::CM2(const uint32_t a, const uint32_t b){
    return static_cast <uint32_t> (a ^ b);
}

//uint32_t CM3(const uint32_t a, const uint32_t b){
//    return static_cast <uint32_t> (a + b);
//}

//uint32_t CM4(const uint32_t a, const uint32_t b){
//    return static_cast <uint32_t> (a + b) % mod32;
//}

//uint32_t CM5(const uint32_t a, const uint32_t b){
//    return static_cast <uint32_t> (a ^ b);
//}

uint32_t GOST::sub(const uint32_t in){
    uint32_t out = 0;
    for(uint8_t x = 0; x < 8; x++){
        out = (out << 4) + k[x][(in >> (28 - (x << 2))) & 15];
    }
    return out;
}

GOST::GOST()
    : SymAlg(),
      k(),
      X(), N(), C1(0), C2(0)
{}

GOST::GOST(const std::string & KEY, const uint8_t sbox[8][16])
    : GOST()
{
    setkey(KEY, sbox);
}

void GOST::setkey(const std::string & KEY, const uint8_t sbox[8][16]){
    if (keyset){
        throw std::runtime_error("Error: Key has already been set.");
    }

    if (KEY.size() != 32){
        throw std::runtime_error("Error: Key must be 256 bits long.");
    }

    C1 = 0b00000001000000010000000100000100UL;
    C2 = 0b00000001000000010000000100000001UL;
    for(uint8_t x = 0; x < 8; x++){
        X[x] = static_cast <uint32_t> (toint(hexlify(KEY.substr(x << 2, 4)), 16));
        for(int y = 0; y < 16; y++){
            k[x][y] = sbox[x][y];
        }
    }
    keyset = true;
}

std::string GOST::encrypt(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }

    if (DATA.size() != 8){
        throw std::runtime_error("Error: Data must be 64 bits in length.");
    }

    for(uint8_t x = 0; x < 2; x++){
        N[x] = static_cast <uint32_t> (toint(DATA.substr(x << 2, 4), 256));
    }

    for(uint8_t x = 0; x < 3; x++){
        for(uint8_t y = 0; y < 4; y++){
            N[1] = CM2(ROL(sub(CM1(N[0], X[(y << 1) & 7])), 11, 32), N[1]);
            N[0] = CM2(ROL(sub(CM1(N[1], X[((y << 1) + 1) & 7])), 11, 32), N[0]);
        }
    }

    for(int8_t x = 3; x > -1; x--){
        N[1] = CM2(ROL(sub(CM1(N[0], X[((x << 1) + 1) & 7])), 11, 32), N[1]);
        N[0] = CM2(ROL(sub(CM1(N[1], X[(x << 1) & 7])), 11, 32), N[0]);
    }
    return unhexlify(makehex(N[1], 8) + makehex(N[0], 8));
}

std::string GOST::decrypt(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }

    if (DATA.size() != 8){
        throw std::runtime_error("Error: Data must be 64 bits in length.");
    }

    for(uint8_t x = 0; x < 2; x++){
        N[x] = static_cast <uint32_t> (toint(DATA.substr(x << 2, 4), 256));
    }

    for(uint8_t x = 0; x < 4; x++){
        N[1] = CM2(ROL(sub(CM1(N[0], X[(x << 1) & 7])), 11, 32), N[1]);
        N[0] = CM2(ROL(sub(CM1(N[1], X[((x << 1) + 1) & 7])), 11, 32), N[0]);
    }

    for(int8_t x = 2; x > -1; x--){
        for(int8_t y = 3; y > -1; y--){
            N[1] = CM2(ROL(sub(CM1(N[0], X[((y << 1) + 1) & 7])), 11, 32), N[1]);
            N[0] = CM2(ROL(sub(CM1(N[1], X[(y << 1) & 7])), 11, 32), N[0]);
        }
    }
    return unhexlify(makehex(N[1], 8) + makehex(N[0], 8));
}

unsigned int GOST::blocksize() const {
    return 64;
}
