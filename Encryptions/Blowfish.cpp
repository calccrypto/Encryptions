#include "Blowfish.h"

uint32_t Blowfish::f(const uint32_t & left){
    return ((((sbox[0][ left >> 24] + sbox[1][(left >> 16) & 255]) & mod32) ^ sbox[2][(left >> 8) & 255]) + sbox[3][left & 255]) & mod32;
}

std::string Blowfish::run(const std::string & data){
    if (!keyset ^ settingkey){
        throw std::runtime_error("Error: Key has not been set");
    }

    if (data.size() != 8){
        throw std::runtime_error("Error: Data must be 64 bits in length.");
    }

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

Blowfish::Blowfish() :
    SymAlg(),
    settingkey(true),
    p(), sbox()
{
}

Blowfish::Blowfish(const std::string & KEY) :
    Blowfish()
{
    setkey(KEY);
}

void Blowfish::setkey(const std::string & KEY){
    if (keyset){
        throw std::runtime_error("Error: Key has already been set.");
    }

    if ((KEY.size() < 4) || (KEY.size() > 112)){
        throw std::runtime_error("Error: Key size does not fit defined sizes.");
    }

    for(uint8_t x = 0; x < 18; x++){
        p[x] = Blowfish_P[x];
    }

    for(uint8_t x = 0; x < 4; x++){
        for(uint16_t y = 0; y < 512; y++){
            sbox[x][y] = Blowfish_SBOX[x][y];
        }
    }

    std::string key = KEY;
    uint8_t s = (72 / key.size()) + 1;
    for(uint8_t i = 0; i < s; i++){
        key += key;
    }

    key = key.substr(0, 72);
    for(uint8_t x = 0; x < 18; x++){
        p[x] ^= static_cast <uint32_t> (toint(key.substr(x << 2, 4), 256));
    }

    std::string ini(8, 0);
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

std::string Blowfish::encrypt(const std::string & DATA){
    return run(DATA);
}

std::string Blowfish::decrypt(const std::string & DATA){
    std::reverse(p, p + 18);
    std::string out = run(DATA);
    std::reverse(p, p + 18);
    return out;
}

unsigned int Blowfish::blocksize() const{
    return 64;
}
