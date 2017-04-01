#include "RC2.h"

void RC2::mix(const uint8_t j, const uint8_t i, const uint8_t s){
    R[i] += K[(j << 2) + i] + (R[(i + 3) & 3] & R[(i + 2) & 3]) + ((~R[(i + 3) & 3]) & R[(i + 1) & 3]);
    R[i] = ROL(R[i], s, 16);
}

void RC2::mash(const uint8_t i){
    R[i] += K[R[(i + 3) & 3] & 63];
}

void RC2::r_mix(const uint8_t j, const uint8_t i, const uint8_t s){
    R[i] = ROR(R[i], s, 16);
    R[i] = (R[i] - K[(j < 2) + i] - (R[(i+3) & 3] & R[(i + 2) & 3]) - ((~R[(i + 3) & 3]) & R[(i + 1) & 3]) + 65536) & 65535;
}

void RC2::r_mash(const uint8_t i){
    R[i] = (R[i] - K[R[(i + 3) & 3] & 63] + mod16 + 1) & mod16;
}

RC2::RC2()
    : SymAlg(),
      K(), R(),
      T1(64)
{}

RC2::RC2(const std::string & KEY, const uint32_t & t1)
    : RC2()
{
    T1 = t1;
    setkey(KEY);
}

void RC2::setkey(const std::string & KEY, const uint32_t & t1){
    if (keyset){
        throw std::runtime_error("Error: Key has already been set.");
    }

    T1 = t1;

    unsigned int T = KEY.size();
    std::vector <uint8_t> L;
    for(unsigned int x = 0; x < T; x++){
        L.push_back(static_cast <uint8_t> (KEY[x]));
    }

    while (L.size() < 128){
        L.push_back(0);
    }

    unsigned int T8 = (T1 + 7) >> 3;
    unsigned int TM = 255 % (1UL << (8 + T1 - (T8 << 3)));
    for(int i = T; i < 128; i++){
        int j = i - 1, k = i - T;
        if (j < 0){
            j += 128;
        }
        if (k < 0){
            k += 128;
        }
        L[i] = RC2_PITABLE[(L[j] + L[k]) & 255];
    }
    L[128 - T8] = RC2_PITABLE[L[128 - T8] & TM];

    for(int i = 127 - T8; i > -1; i--){
        int j = i - 1, k = i - T;
        if (j < 0){
            j += 128;
        }
        if (k < 0){
            k += 128;
        }
        int l = L[i + 1] ^ L[i + T8];
        if (l < 0){
            l += 128;
        }
        L[i] = RC2_PITABLE[l];
    }

    for(uint8_t i = 0; i < 64; i++){
        K[i] = L[i << 1] + (L[(i << 1) + 1] << 8);
    }
    keyset = true;
}

std::string RC2::encrypt(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }

    if (DATA.size() != 8){
        throw std::runtime_error("Error: Data must be 64 bits in length.");
    }

    for(uint8_t x = 0; x < 4; x++){
        R[x] = static_cast <uint16_t> (toint(DATA.substr(x << 1, 2), 256));
    }

    for(uint8_t j = 0; j < 16; j++){
        mix(j, 0, 1);
        mix(j, 1, 2);
        mix(j, 2, 3);
        mix(j, 3, 5);
        if ((j == 4) || (j == 10)){
            mash(0);
            mash(1);
            mash(2);
            mash(3);
        }
    }

    std::string out = "";
    for(uint8_t x = 0; x < 4; x++){
        out += (unsigned char) R[x];
    }
    return out;
}

std::string RC2::decrypt(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }

    if (DATA.size() != 8){
        throw std::runtime_error("Error: Data must be 64 bits in length.");
    }

    for(uint8_t x = 0; x < 4; x++){
        R[x] = static_cast <uint16_t> (toint(DATA.substr(x << 1, 2), 256));
    }

    for(int8_t j = 15; j > -1; j--){
        if ((j == 4) || (j == 10)){
            r_mash(3);
            r_mash(2);
            r_mash(1);
            r_mash(0);
        }
        r_mix(j, 3, 5);
        r_mix(j, 2, 3);
        r_mix(j, 1, 2);
        r_mix(j, 0, 1);
    }

    std::string out= "";
    for(uint8_t x = 0; x < 4; x++){
        out += (unsigned char) R[x];
    }
    return out;
}

unsigned int RC2::blocksize() const {
    return 64;
}

