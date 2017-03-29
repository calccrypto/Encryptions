#include "Skipjack.h"

uint16_t Skipjack::G_e(const uint16_t quarter, const uint32_t fourkeys){
    uint16_t left = quarter >> 8;
    uint16_t right = quarter & 255;
    uint8_t k0 = fourkeys >> 24;
    uint8_t k1 = (fourkeys >> 16) & 255;
    uint8_t k2 = (fourkeys >> 8) & 255;
    uint8_t k3 = fourkeys & 255;
    left ^= Skipjack_F[right ^ k0];
    right ^= Skipjack_F[left ^ k1];
    left ^= Skipjack_F[right ^ k2];
    right ^= Skipjack_F[left ^ k3];
    return (left << 8) + right;
}

void Skipjack::A(uint16_t & w1, uint16_t & w2, uint16_t & w3, uint16_t & w4, const uint16_t i){
    uint16_t w5 = w4;
    w4 = w3;
    w3 = w2;
    w2 = G_e(w1, toint(key.substr((i << 3) - 8, 8), 16));
    w1 = w2 ^ w5 ^ i;
}

void Skipjack::B(uint16_t & w1, uint16_t & w2, uint16_t & w3, uint16_t & w4, const uint16_t i){
    uint16_t w5 = w4;
    w4 = w3;
    w3 = w1 ^ w2 ^ i;
    w2 = G_e(w1, toint(key.substr((i << 3) - 8, 8), 16));
    w1 = w5;
}

uint16_t Skipjack::G_d(const uint16_t quarter, const uint32_t fourkeys){
    uint16_t left = quarter >> 8;
    uint16_t right = quarter & 255;
    uint8_t k0 = fourkeys >> 24;
    uint8_t k1 = (fourkeys >> 16) & 255;
    uint8_t k2 = (fourkeys >> 8) & 255;
    uint8_t k3 = fourkeys & 255;
    right ^= Skipjack_F[left ^ k3];
    left ^= Skipjack_F[right ^ k2];
    right ^= Skipjack_F[left ^ k1];
    left ^= Skipjack_F[right ^ k0];
    return (left << 8) + right;
}

void Skipjack::invA(uint16_t & w1, uint16_t & w2, uint16_t & w3, uint16_t & w4, const uint16_t i){
    uint16_t w5 = w1 ^ w2 ^ i;
    w1 = G_d(w2, toint(key.substr((i << 3) - 8, 8), 16));
    w2 = w3;
    w3 = w4;
    w4 = w5;
}

void Skipjack::invB(uint16_t & w1, uint16_t & w2, uint16_t & w3, uint16_t & w4, const uint16_t i){
    uint16_t w5 = w1;
    w1 = G_d(w2, toint(key.substr((i << 3) - 8, 8), 16));
    w2 = w1 ^ w3 ^ i;
    w3 = w4;
    w4 = w5;
}

Skipjack::Skipjack()
    : SymAlg(),
      key("")
{}

Skipjack::Skipjack(const std::string & KEY)
    : Skipjack()
{
    setkey(KEY);
}

void Skipjack::setkey(const std::string & KEY){
    if (keyset){
        throw std::runtime_error("Error: Key has already been set.");
    }

    if (KEY.size() != 10){
        throw std::runtime_error("Error: Key must be 80 bits in length.");
    }

    key = hexlify(KEY);
    while (key.size() < 256){
        key = key + key;
    }
    key = key.substr(0, 256);
    keyset = true;
}

std::string Skipjack::encrypt(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set");
    }

    if (DATA.size() != 8){
        throw std::runtime_error("Error: Data must be 64 bits in length.");
    }

    uint16_t w1 = toint(DATA.substr(0, 2), 256);
    uint16_t w2 = toint(DATA.substr(2, 2), 256);
    uint16_t w3 = toint(DATA.substr(4, 2), 256);
    uint16_t w4 = toint(DATA.substr(6, 2), 256);

    for(uint8_t i = 1; i < 9; i++){
        A(w1, w2, w3, w4, i);
    }

    for(uint8_t i = 9; i < 17; i++){
        B(w1, w2, w3, w4, i);
    }

    for(uint8_t i = 17; i < 25; i++){
        A(w1, w2, w3, w4, i);
    }

    for(uint8_t i = 25; i < 33; i++){
        B(w1, w2, w3, w4, i);
    }

    return unhexlify(makehex(w1, 4) + makehex(w2, 4) + makehex(w3, 4) + makehex(w4, 4));
}

std::string Skipjack::decrypt(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set");
    }

    if (DATA.size() != 8){
        throw std::runtime_error("Error: Data must be 64 bits in length.");
    }

    uint16_t w1 = toint(DATA.substr(0, 2), 256);
    uint16_t w2 = toint(DATA.substr(2, 2), 256);
    uint16_t w3 = toint(DATA.substr(4, 2), 256);
    uint16_t w4 = toint(DATA.substr(6, 2), 256);

    for(uint8_t i = 32; i > 24; i--){
        invB(w1, w2, w3, w4, i);
    }

    for(uint8_t i = 24; i > 16; i--){
        invA(w1, w2, w3, w4, i);
    }

    for(uint8_t i = 16; i > 8; i--){
        invB(w1, w2, w3, w4, i);
    }

    for(uint8_t i = 8; i > 0; i--){
        invA(w1, w2, w3, w4, i);
    }

    return unhexlify(makehex(w1, 4) + makehex(w2, 4) + makehex(w3, 4) + makehex(w4, 4));
}

unsigned int Skipjack::blocksize() const {
    return 64;
}
