#include "./GOST.h"

// GOST 28147-89
uint32_t GOST::CM1(uint32_t a, uint32_t b){
    return (uint32_t) (a + b);
}

uint32_t GOST::CM2(uint32_t a, uint32_t b){
    return (uint32_t) (a ^ b);
}

//uint32_t CM3(uint32_t a, uint32_t b){
//    return (uint32_t) (a + b);
//}

//uint32_t CM4(uint32_t a, uint32_t b){
//    return (uint32_t) (a + b) % mod32;
//}

//uint32_t CM5(uint32_t a, uint32_t b){
//    return (uint32_t) (a ^ b);
//}

std::string GOST::reverse(std::string & in){
    for(uint8_t x = 0; x < in.size() >> 1; x++){
        std::swap(in[x], in[in.size() - 1 - x]);
    }
    return in;
}

uint32_t GOST::sub(uint32_t in){
    uint32_t out = 0;
    for(uint8_t x = 0; x < 8; x++){
        out = (out << 4) + k[x][(in >> (28 - (x << 2))) & 15];
    }
    return out;
}


GOST::GOST(){
    keyset = false;
}

GOST::GOST(std::string KEY, const uint8_t sbox[8][16]){
    keyset = false;
    setkey(KEY, sbox);
}

void GOST::setkey(std::string KEY, const uint8_t sbox[8][16]){
    if (keyset)
        error(2);
    C1 = 0b00000001000000010000000100000100UL;
    C2 = 0b00000001000000010000000100000001UL;
    for(uint8_t x = 0; x < 8; x++){
        X[x] = (uint32_t) toint(hexlify(KEY.substr(x << 2, 4)), 16);
        for(int y = 0; y < 16; y++){
            k[x][y] = sbox[x][y];
        }
    }
    keyset = true;
}

std::string GOST::encrypt(std::string DATA){
    if (!keyset){
        error(1);
    }
    while (DATA.size() & 7){
        DATA += zero;
    }
    for(uint8_t x = 0; x < 2; x++){
        N[x] = (uint32_t) toint(DATA.substr(x << 2, 4), 256);
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

std::string GOST::decrypt(std::string DATA){
    if (!keyset){
        error(1);
    }
    while (DATA.size() & 7){
        DATA += zero;
    }
    for(uint8_t x = 0; x < 2; x++){
        N[x] = (uint32_t) toint(DATA.substr(x << 2, 4), 256);
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

unsigned int GOST::blocksize(){
    return 64;
}
