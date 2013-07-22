#include "Blowfish.h"

uint32_t Blowfish::f(uint32_t & left){
    uint32_t a = left >> 24, b = (left >> 16) & 255, c = (left >> 8) & 255, d = left & 255;
    return ((((sbox[0][a] + sbox[1][b]) & mod32) ^ sbox[2][c]) + sbox[3][d]) & mod32;
}

std::string Blowfish::run(std::string & data){
    if (!keyset ^ settingkey)
        error(1);
    uint32_t left = toint(data.substr(0, 4), 256), right = toint(data.substr(4, 4), 256);
    for(uint8_t i = 0; i < 16; i++){
        left ^= p[i];
        right ^= f(left);
        std::swap(left,right);
    }
    //std::swap(right, left);       // Save 513 swaps
    right ^= p[17];
    left ^= p[16];
    return unhexlify(makehex(right, 8) + makehex(left, 8));
}

Blowfish::Blowfish(){
    keyset = false;
    settingkey = true;
}

Blowfish::Blowfish(std::string KEY){
    keyset = false;
    settingkey = true;
    setkey(KEY);
}

void Blowfish::setkey(std::string KEY){
    if (keyset)
        error(2);
    for(uint8_t x = 0; x < 18; x++)
        p[x] = Blowfish_P[x];
    for(uint8_t x = 0; x < 4; x++)
        for(uint16_t y = 0; y < 512; y++)
            sbox[x][y] = Blowfish_SBOX[x][y];
    uint8_t s = (72 / KEY.size()) + 1;
    for(uint8_t i = 0; i < s; i++)
        KEY += KEY;
    KEY = KEY.substr(0, 72);
    for(uint8_t x = 0; x < 18; x++)
        p[x] ^= (uint32_t) toint(KEY.substr(x << 2, 4), 256);
    std::string ini("\0\0\0\0\0\0\0\0", 8);
    for(uint8_t x = 0; x < 9; x++){
        std::string NEW = run(ini);
        ini = NEW;
        p[x << 1] = toint(NEW.substr(0, 4), 256);
        p[(x << 1) + 1] = toint(NEW.substr(4, 4), 256);
    }
    for(uint8_t x = 0; x < 4; x++){
        for(uint8_t y = 0; y < 128; y++){
            std::string NEW = run(ini);
            ini = NEW;
            sbox[x][y << 1] = toint(NEW.substr(0, 4), 256);
            sbox[x][(y << 1) + 1] = toint(NEW.substr(4, 4), 256);
        }
    }
    keyset = true;
    settingkey = false;
}

std::string Blowfish::encrypt(std::string DATA){
    return run(DATA);
}

std::string Blowfish::decrypt(std::string DATA){
    std::reverse(p, p + 18);
    std::string out = run(DATA);
    std::reverse(p, p + 18);
    return out;
}

unsigned int Blowfish::blocksize(){
    return 64;
}
