#include "MISTY1.h"

uint16_t MISTY1::FI(const uint16_t FI_IN, const uint16_t FI_KEY){
    uint16_t d9 = FI_IN >> 7;
    uint16_t d7 = FI_IN & 0x7f;
    d9 = MISTY1_S9[d9] ^ d7;
    d7 = MISTY1_S7[d7] ^ d9;
    d7 &= 0x7f;
    d7 ^= (FI_KEY >> 9);
    d9 ^= (FI_KEY & 0x1ff);
    d9 = MISTY1_S9[d9] ^ d7;
    return (static_cast <uint16_t> (d7 & 0xffffU) << 9) | d9;
}

uint32_t MISTY1::FO(const uint32_t FO_IN, const uint16_t k){
    uint16_t t0 = FO_IN >> 16;
    uint16_t t1 = FO_IN & 0xffff;
    t0 ^= EK[k];
    t0 = FI(t0, EK[(k+5)%8+8]);
    t0 ^= t1;
    t1 ^= EK[(k+2)%8];
    t1 = FI(t1, EK[(k+1)%8+8]);
    t1 ^= t0;
    t0 ^= EK[(k+7)%8];
    t0 = FI(t0, EK[(k+3)%8+8]);
    t0 ^= t1;
    t1 ^= EK[(k+4)%8];
    return (t1 << 16) | t0;
}

uint32_t MISTY1::FL(const uint32_t FL_IN, const uint32_t k){
    uint16_t d0 = FL_IN >> 16;
    uint16_t d1 = FL_IN & 0xffff;
    if (!(k & 1)){
       d1 ^= (d0 & EK[k/2]);
       d0 ^= (d1 | EK[(k/2+6)%8+8]);
    }
    else{
       d1 ^= (d0 & EK[((k-1)/2+2)%8+8]);
       d0 ^= (d1 | EK[((k-1)/2+4)%8]);
    }
    return (d0 << 16) | d1;
}

uint32_t MISTY1::FLINV(const uint32_t FL_IN, const uint32_t k){
    uint16_t d0 = FL_IN >> 16;
    uint16_t d1 = FL_IN & 0xffff;
    if (!(k & 1)){
        d0 ^= (d1 | EK[(k/2+6)%8+8]);
        d1 ^= (d0 & EK[k/2]);
    }
    else{
        d0 ^= (d1 | EK[((k-1)/2+4)%8]);
        d1 ^= (d0 & EK[((k-1)/2+2)%8+8]);
    }
    return (d0 << 16) | d1;
}

MISTY1::MISTY1()
    : SymAlg(),
      EK()
{}

MISTY1::MISTY1(const std::string & KEY)
    : MISTY1()
{
    setkey(KEY);
}

void MISTY1::setkey(const std::string & KEY){
    if (keyset){
        throw std::runtime_error("Error: Key has already been set.");
    }

    if (KEY.size() != 16){
        throw std::runtime_error("Error: Key must be 128 bits in length.");
    }

    for(uint8_t i = 0; i < 8; i++){
        EK[i] = ((KEY[i*2]*256) & 0xffff) + (KEY[i*2+1] & 0xff);
    }
    for(uint8_t i = 0; i < 8; i++){
        EK[i+ 8] = FI(EK[i], EK[(i+1)%8]);
        EK[i+16] = EK[i+8] & 0x1ff;
        EK[i+24] = EK[i+8] >> 9;
    }
    keyset = true;
}

std::string MISTY1::encrypt(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }

    if (DATA.size() != 8){
        throw std::runtime_error("Error: Data must be 64 bits in length.");
    }

    uint32_t D0 = toint(DATA.substr(0, 4), 256);
    uint32_t D1 = toint(DATA.substr(4, 4), 256);
    // 0 round
    D0 = FL(D0, 0);
    D1 = FL(D1, 1);
    D1 ^= FO(D0, 0);
    // 1 round
    D0 ^= FO(D1, 1);
    // 2 round
    D0 = FL(D0, 2);
    D1 = FL(D1, 3);
    D1 ^= FO(D0, 2);
    // 3 round
    D0 ^= FO(D1, 3);
    // 4 round
    D0 = FL(D0, 4);
    D1 = FL(D1, 5);
    D1 ^= FO(D0, 4);
    // 5 round
    D0 ^= FO(D1, 5);
    // 6 round
    D0 = FL(D0, 6);
    D1 = FL(D1, 7);
    D1 ^= FO(D0, 6);
    // 7 round
    D0 ^= FO(D1, 7);
    // final
    D0 = FL(D0, 8);
    D1 = FL(D1, 9);
    return unhexlify(makehex(D1, 8) + makehex(D0, 8));
}

std::string MISTY1::decrypt(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }

    if (DATA.size() != 8){
        throw std::runtime_error("Error: Data must be 64 bits in length.");
    }

    uint32_t D0 = toint(DATA.substr(4, 4), 256);
    uint32_t D1 = toint(DATA.substr(0, 4), 256);
    D0 = FLINV(D0, 8);
    D1 = FLINV(D1, 9);
    D0 ^= FO(D1, 7);
    D1 ^= FO(D0, 6);
    D0 = FLINV(D0, 6);
    D1 = FLINV(D1, 7);
    D0 ^= FO(D1, 5);
    D1 ^= FO(D0, 4);
    D0 = FLINV(D0, 4);
    D1 = FLINV(D1, 5);
    D0 ^= FO(D1, 3);
    D1 ^= FO(D0, 2);
    D0 = FLINV(D0, 2);
    D1 = FLINV(D1, 3);
    D0 ^= FO(D1, 1);
    D1 ^= FO(D0, 0);
    D0 = FLINV(D0, 0);
    D1 = FLINV(D1, 1);
    return unhexlify(makehex(D0, 8) + makehex(D1));
}

unsigned int MISTY1::blocksize() const {
    return 64;
};
