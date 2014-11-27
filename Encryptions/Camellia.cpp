#include "./Camellia.h"

unsigned int Camellia::SBOX(const uint8_t s, const uint8_t value){
    if (s == 1){
        return Camellia_SBox[value];
    }
    else if (s == 2){
        return ROL(Camellia_SBox[value], 1, 8);
    }
    else if (s == 3){
        return ROL(Camellia_SBox[value], 7, 8);
    }
    else{//(s == 4)
        return Camellia_SBox[ROL(value, 1, 8)];
    }
}

uint64_t Camellia::FL(const uint64_t & FL_IN, const uint64_t & KE){
    uint64_t x1 = FL_IN >> 32;
    uint64_t x2 = FL_IN & mod32;
    const uint64_t k1 = KE >> 32;
    const uint64_t k2 = KE & mod32;
    x2 ^= ROL(x1 & k1, 1, 32);
    x1 ^= (x2 | k2);
    return (x1 << 32) | x2;
}

uint64_t Camellia::FLINV(const uint64_t & FLINV_IN, const uint64_t & KE){
    uint64_t y1 = FLINV_IN >> 32;
    uint64_t y2 = FLINV_IN & mod32;
    const uint64_t k1 = KE >> 32;
    const uint64_t k2 = KE & mod32;
    y1 ^= (y2 | k2);
    y2 ^= ROL(y1 & k1, 1, 32);
    return (y1 << 32) | y2;
}

uint64_t Camellia::F(const uint64_t & F_IN, const uint64_t & KE){
    uint64_t x = F_IN ^ KE;
    uint8_t t1 = x >> 56;
    uint8_t t2 = (x >> 48) & 255;
    uint8_t t3 = (x >> 40) & 255;
    uint8_t t4 = (x >> 32) & 255;
    uint8_t t5 = (x >> 24) & 255;
    uint8_t t6 = (x >> 16) & 255;
    uint8_t t7 = (x >> 8) & 255;
    uint8_t t8 = x & 255;
    t1 = SBOX(1, t1);
    t2 = SBOX(2, t2);
    t3 = SBOX(3, t3);
    t4 = SBOX(4, t4);
    t5 = SBOX(2, t5);
    t6 = SBOX(3, t6);
    t7 = SBOX(4, t7);
    t8 = SBOX(1, t8);
    uint64_t y1 = t1 ^ t3 ^ t4 ^ t6 ^ t7 ^ t8;
    uint64_t y2 = t1 ^ t2 ^ t4 ^ t5 ^ t7 ^ t8;
    uint64_t y3 = t1 ^ t2 ^ t3 ^ t5 ^ t6 ^ t8;
    uint64_t y4 = t2 ^ t3 ^ t4 ^ t5 ^ t6 ^ t7;
    uint64_t y5 = t1 ^ t2 ^ t6 ^ t7 ^ t8;
    uint64_t y6 = t2 ^ t3 ^ t5 ^ t7 ^ t8;
    uint64_t y7 = t3 ^ t4 ^ t5 ^ t6 ^ t8;
    uint64_t y8 = t1 ^ t4 ^ t5 ^ t6 ^ t7;
    return (y1 << 56) | (y2 << 48) | (y3 << 40) | (y4 << 32) | (y5 << 24) | (y6 << 16) | (y7 << 8) | y8;
}

std::string Camellia::run(const std::string & data){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }

    if (data.size() != 16){
        throw std::runtime_error("Error: Data must be 128 bits in length.");
    }

    uint64_t D1 = toint(data.substr(0, 8), 256);
    uint64_t D2 = toint(data.substr(8, 8), 256);
    if (keysize == 16){
        uint64_t kw1 = keys[0];
        uint64_t kw2 = keys[1];
        uint64_t k1 = keys[2];
        uint64_t k2 = keys[3];
        uint64_t k3 = keys[4];
        uint64_t k4 = keys[5];
        uint64_t k5 = keys[6];
        uint64_t k6 = keys[7];
        uint64_t k7 = keys[8];
        uint64_t k8 = keys[9];
        uint64_t k9 = keys[10];
        uint64_t ke1 = keys[11];
        uint64_t ke2 = keys[12];
        uint64_t ke3 = keys[13];
        uint64_t ke4 = keys[14];
        uint64_t k10 = keys[15];
        uint64_t k11 = keys[16];
        uint64_t k12 = keys[17];
        uint64_t k13 = keys[18];
        uint64_t k14 = keys[19];
        uint64_t k15 = keys[20];
        uint64_t k16 = keys[21];
        uint64_t k17 = keys[22];
        uint64_t k18 = keys[23];
        uint64_t kw4 = keys[24];
        uint64_t kw3 = keys[25];
        D1 ^= kw1;
        D2 ^= kw2;
        D2 ^= F(D1, k1);
        D1 ^= F(D2, k2);
        D2 ^= F(D1, k3);
        D1 ^= F(D2, k4);
        D2 ^= F(D1, k5);
        D1 ^= F(D2, k6);
        D1 = FL(D1, ke1);
        D2 = FLINV(D2, ke2);
        D2 ^= F(D1, k7);
        D1 ^= F(D2, k8);
        D2 ^= F(D1, k9);
        D1 ^= F(D2, k10);
        D2 ^= F(D1, k11);
        D1 ^= F(D2, k12);
        D1 = FL(D1, ke3);
        D2 = FLINV(D2, ke4);
        D2 ^= F(D1, k13);
        D1 ^= F(D2, k14);
        D2 ^= F(D1, k15);
        D1 ^= F(D2, k16);
        D2 ^= F(D1, k17);
        D1 ^= F(D2, k18);
        D2 ^= kw3;
        D1 ^= kw4;
    }
    else{
        uint64_t kw1 = keys[0];
        uint64_t kw2 = keys[1];
        uint64_t k1 = keys[2];
        uint64_t k2 = keys[3];
        uint64_t k3 = keys[4];
        uint64_t k4 = keys[5];
        uint64_t k5 = keys[6];
        uint64_t k6 = keys[7];
        uint64_t k7 = keys[8];
        uint64_t k8 = keys[9];
        uint64_t k9 = keys[10];
        uint64_t k10 = keys[11];
        uint64_t k11 = keys[12];
        uint64_t k12 = keys[13];
        uint64_t ke1 = keys[14];
        uint64_t ke2 = keys[15];
        uint64_t ke3 = keys[16];
        uint64_t ke4 = keys[17];
        uint64_t ke5 = keys[18];
        uint64_t ke6 = keys[19];
        uint64_t k13 = keys[20];
        uint64_t k14 = keys[21];
        uint64_t k15 = keys[22];
        uint64_t k16 = keys[23];
        uint64_t k17 = keys[24];
        uint64_t k18 = keys[25];
        uint64_t k19 = keys[26];
        uint64_t k20 = keys[27];
        uint64_t k21 = keys[28];
        uint64_t k22 = keys[29];
        uint64_t k23 = keys[30];
        uint64_t k24 = keys[31];
        uint64_t kw4 = keys[32];
        uint64_t kw3 = keys[33];
        D1 ^= kw1;
        D2 ^= kw2;
        D2 ^= F(D1, k1);
        D1 ^= F(D2, k2);
        D2 ^= F(D1, k3);
        D1 ^= F(D2, k4);
        D2 ^= F(D1, k5);
        D1 ^= F(D2, k6);
        D1 = FL(D1, ke1);
        D2 = FLINV(D2, ke2);
        D2 ^= F(D1, k7);
        D1 ^= F(D2, k8);
        D2 ^= F(D1, k9);
        D1 ^= F(D2, k10);
        D2 ^= F(D1, k11);
        D1 ^= F(D2, k12);
        D1 = FL(D1, ke3);
        D2 = FLINV(D2, ke4);
        D2 ^= F(D1, k13);
        D1 ^= F(D2, k14);
        D2 ^= F(D1, k15);
        D1 ^= F(D2, k16);
        D2 ^= F(D1, k17);
        D1 ^= F(D2, k18);
        D1 = FL(D1, ke5);
        D2 = FLINV(D2, ke6);
        D2 ^= F(D1, k19);
        D1 ^= F(D2, k20);
        D2 ^= F(D1, k21);
        D1 ^= F(D2, k22);
        D2 ^= F(D1, k23);
        D1 ^= F(D2, k24);
        D2 ^= kw3;
        D1 ^= kw4;
    }
    return unhexlify(makehex(D2, 16) + makehex(D1, 16));
}

Camellia::Camellia() :
    SymAlg(),
    keysize(0),
    keys()
{
}

Camellia::Camellia(const std::string & KEY) :
    Camellia()
{
    setkey(KEY);
}

void Camellia::setkey(const std::string & KEY){
    if (keyset){
        throw std::runtime_error("Error: Key has already been set.");
    }

    keysize = KEY.size();
    if ((keysize != 16) && (keysize != 24) && (keysize != 32)){
        throw std::runtime_error("Error: Key size does not fit defined sizes.");
    }

    integer KL, KR;
    if (keysize == 16){
        KL = integer(KEY, 256);
        KR = 0;
    }
    else if (keysize == 24){
        KL = integer(KEY.substr(0, 16), 256);
        KR = integer(KEY.substr(16, 8), 256); KR = (KR << 64) + (KR ^ integer("ffffffffffffffff", 16));
    }
    else if (keysize == 32){
        KL = integer(KEY.substr(0, 16), 256);
        KR = integer(KEY.substr(16, 16), 256);
    }

    uint64_t D1 = static_cast <uint64_t> ((KL ^ KR) >> 64);
    uint64_t D2 = static_cast <uint64_t> (KL ^ KR);
    D2 ^= F(D1, Camellia_Sigma1);
    D1 ^= F(D2, Camellia_Sigma2);
    D1 ^= static_cast <uint64_t> (KL >> 64);
    D2 ^= static_cast <uint64_t> (KL);
    D2 ^= F(D1, Camellia_Sigma3);
    D1 ^= F(D2, Camellia_Sigma4);
    integer KA = (integer(D1) << 64) + D2;
    D1 = static_cast <uint64_t> ((KA ^ KR) >> 64);
    D2 = static_cast <uint64_t> (KA ^ KR);
    D2 ^= F(D1, Camellia_Sigma5);
    D1 ^= F(D2, Camellia_Sigma6);
    integer KB = (integer(D1) << 64) + D2;
    integer T;
    if (keysize == 16){
        T = ROL(KL, 0, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               // kw1
        keys.push_back(static_cast <uint64_t> (T));                     // kw2
        T = ROL(KA, 0, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               // k1
        keys.push_back(static_cast <uint64_t> (T));                     // k2
        T = ROL(KL, 15, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               // k3
        keys.push_back(static_cast <uint64_t> (T));                     // k4
        T = ROL(KA, 15, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               // k5
        keys.push_back(static_cast <uint64_t> (T));                     // k6
        T = ROL(KL, 45, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               // k7
        keys.push_back(static_cast <uint64_t> (T));                     // k8
        T = ROL(KA, 45, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               // k9
        T = ROL(KA, 30, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               // ke1
        keys.push_back(static_cast <uint64_t> (ROL(KA, 30, 128)));      // ke2
        T = ROL(KL, 77, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               // ke3
        keys.push_back(static_cast <uint64_t> (T));                     // ke4
        T = ROL(KL, 60, 128);
        keys.push_back(static_cast <uint64_t> (T));                     // k10
        T = ROL(KA, 60, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               // k11
        keys.push_back(static_cast <uint64_t> (T));                     // k12
        T = ROL(KL, 94, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               // k13
        keys.push_back(static_cast <uint64_t> (T));                     // k14
        T = ROL(KA, 94, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               // k15
        keys.push_back(static_cast <uint64_t> (T));                     // k16
        T = ROL(KL, 111, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               // k17
        keys.push_back(static_cast <uint64_t> (T));                     // k18
        T = ROL(KA, 111, 128);
        keys.push_back(static_cast <uint64_t> (T));                     // kw4
        keys.push_back(static_cast <uint64_t> (T >> 64));               // kw3
    }
    else{
        T = ROL(KL, 0, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               //kw1
        keys.push_back(static_cast <uint64_t> (T));                     //kw2
        T = ROL(KB, 0, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               //k1
        keys.push_back(static_cast <uint64_t> (T));                     //k2
        T = ROL(KR, 15, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               //k3
        keys.push_back(static_cast <uint64_t> (T));                     //k4
        T = ROL(KA, 15, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               //k5
        keys.push_back(static_cast <uint64_t> (T));                     //k6
        T = ROL(KB, 30, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               //k7
        keys.push_back(static_cast <uint64_t> (T));                     //k8
        T = ROL(KL, 45, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               //k9
        keys.push_back(static_cast <uint64_t> (T));                     //k10
        T = ROL(KA, 45, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               //k11
        keys.push_back(static_cast <uint64_t> (T));                     //k12
        T = ROL(KR, 30, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               //ke1
        keys.push_back(static_cast <uint64_t> (T));                     //ke2
        T = ROL(KL, 60, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               //ke3
        keys.push_back(static_cast <uint64_t> (T));                     //ke4
        T = ROL(KA, 77, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               //ke5
        keys.push_back(static_cast <uint64_t> (T));                     //ke6
        T = ROL(KR, 60, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               //k13
        keys.push_back(static_cast <uint64_t> (T));                     //k14
        T = ROL(KB, 60, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               //k15
        keys.push_back(static_cast <uint64_t> (T));                     //k16
        T = ROL(KL, 77, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               //k17
        keys.push_back(static_cast <uint64_t> (T));                     //k18
        T = ROL(KR, 94, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               //k19
        keys.push_back(static_cast <uint64_t> (T));                     //k20
        T = ROL(KA, 94, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               //k21
        keys.push_back(static_cast <uint64_t> (T));                     //k22
        T = ROL(KL, 111, 128);
        keys.push_back(static_cast <uint64_t> (T >> 64));               //k23
        keys.push_back(static_cast <uint64_t> (T));                     //k24
        T = ROL(KB, 111, 128);
        keys.push_back(static_cast <uint64_t> (T));                     //kw4
        keys.push_back(static_cast <uint64_t> (T >> 64));               //kw3
    }
//// More clear way of implementing
//    if (keysize == 16){
//        uint64_t kw1 = static_cast <uint64_t> (ROL(KL, 0, 128) >> 64);
//        uint64_t kw2 = static_cast <uint64_t> (ROL(KL, 0, 128));
//        uint64_t k1 = static_cast <uint64_t> (ROL(KA, 0, 128) >> 64);
//        uint64_t k2 = static_cast <uint64_t> (ROL(KA, 0, 128));
//        uint64_t k3 = static_cast <uint64_t> (ROL(KL, 15, 128) >> 64);
//        uint64_t k4 = static_cast <uint64_t> (ROL(KL, 15, 128));
//        uint64_t k5 = static_cast <uint64_t> (ROL(KA, 15, 128) >> 64);
//        uint64_t k6 = static_cast <uint64_t> (ROL(KA, 15, 128));
//        uint64_t ke1 = static_cast <uint64_t> (ROL(KA, 30, 128) >> 64);
//        uint64_t ke2 = static_cast <uint64_t> (ROL(KA, 30, 128));
//        uint64_t k7 = static_cast <uint64_t> (ROL(KL, 45, 128) >> 64);
//        uint64_t k8 = static_cast <uint64_t> (ROL(KL, 45, 128));
//        uint64_t k9 = static_cast <uint64_t> (ROL(KA, 45, 128) >> 64);
//        uint64_t k10 = static_cast <uint64_t> (ROL(KL, 60, 128));
//        uint64_t k11 = static_cast <uint64_t> (ROL(KA, 60, 128) >> 64);
//        uint64_t k12 = static_cast <uint64_t> (ROL(KA, 60, 128));
//        uint64_t ke3 = static_cast <uint64_t> (ROL(KL, 77, 128) >> 64);
//        uint64_t ke4 = static_cast <uint64_t> (ROL(KL, 77, 128));
//        uint64_t k13 = static_cast <uint64_t> (ROL(KL, 94, 128) >> 64);
//        uint64_t k14 = static_cast <uint64_t> (ROL(KL, 94, 128));
//        uint64_t k15 = static_cast <uint64_t> (ROL(KA, 94, 128) >> 64);
//        uint64_t k16 = static_cast <uint64_t> (ROL(KA, 94, 128));
//        uint64_t k17 = static_cast <uint64_t> (ROL(KL, 111, 128) >> 64);
//        uint64_t k18 = static_cast <uint64_t> (ROL(KL, 111, 128));
//        uint64_t kw4 = static_cast <uint64_t> (ROL(KA, 111, 128));
//        uint64_t kw3 = static_cast <uint64_t> (ROL(KA, 111, 128) >> 64);
//
//        keys.push_back(kw1);
//        keys.push_back(kw2);
//        keys.push_back(k1);
//        keys.push_back(k2);
//        keys.push_back(k3);
//        keys.push_back(k4);
//        keys.push_back(k5);
//        keys.push_back(k6);
//        keys.push_back(k7);
//        keys.push_back(k8);
//        keys.push_back(k9);
//        keys.push_back(ke1);
//        keys.push_back(ke2);
//        keys.push_back(ke3);
//        keys.push_back(ke4);
//        keys.push_back(k10);
//        keys.push_back(k11);
//        keys.push_back(k12);
//        keys.push_back(k13);
//        keys.push_back(k14);
//        keys.push_back(k15);
//        keys.push_back(k16);
//        keys.push_back(k17);
//        keys.push_back(k18);
//        keys.push_back(kw4);
//        keys.push_back(kw3);
//    }
//    else{
//        uint64_t kw1 = static_cast <uint64_t> (ROL(KL, 0, 128) >> 64);
//        uint64_t kw2 = static_cast <uint64_t> (ROL(KL, 0, 128));
//        uint64_t k1 = static_cast <uint64_t> (ROL(KB, 0, 128) >> 64);
//        uint64_t k2 = static_cast <uint64_t> (ROL(KB, 0, 128));
//        uint64_t k3 = static_cast <uint64_t> (ROL(KR, 15, 128) >> 64);
//        uint64_t k4 = static_cast <uint64_t> (ROL(KR, 15, 128));
//        uint64_t k5 = static_cast <uint64_t> (ROL(KA, 15, 128) >> 64);
//        uint64_t k6 = static_cast <uint64_t> (ROL(KA, 15, 128));
//        uint64_t ke1 = static_cast <uint64_t> (ROL(KR, 30, 128) >> 64);
//        uint64_t ke2 = static_cast <uint64_t> (ROL(KR, 30, 128));
//        uint64_t k7 = static_cast <uint64_t> (ROL(KB, 30, 128) >> 64);
//        uint64_t k8 = static_cast <uint64_t> (ROL(KB, 30, 128));
//        uint64_t k9 = static_cast <uint64_t> (ROL(KL, 45, 128) >> 64);
//        uint64_t k10 = static_cast <uint64_t> (ROL(KL, 45, 128));
//        uint64_t k11 = static_cast <uint64_t> (ROL(KA, 45, 128) >> 64);
//        uint64_t k12 = static_cast <uint64_t> (ROL(KA, 45, 128));
//        uint64_t ke3 = static_cast <uint64_t> (ROL(KL, 60, 128) >> 64);
//        uint64_t ke4 = static_cast <uint64_t> (ROL(KL, 60, 128));
//        uint64_t k13 = static_cast <uint64_t> (ROL(KR, 60, 128) >> 64);
//        uint64_t k14 = static_cast <uint64_t> (ROL(KR, 60, 128));
//        uint64_t k15 = static_cast <uint64_t> (ROL(KB, 60, 128) >> 64);
//        uint64_t k16 = static_cast <uint64_t> (ROL(KB, 60, 128));
//        uint64_t k17 = static_cast <uint64_t> (ROL(KL, 77, 128) >> 64);
//        uint64_t k18 = static_cast <uint64_t> (ROL(KL, 77, 128));
//        uint64_t ke5 = static_cast <uint64_t> (ROL(KA, 77, 128) >> 64);
//        uint64_t ke6 = static_cast <uint64_t> (ROL(KA, 77, 128));
//        uint64_t k19 = static_cast <uint64_t> (ROL(KR, 94, 128) >> 64);
//        uint64_t k20 = static_cast <uint64_t> (ROL(KR, 94, 128));
//        uint64_t k21 = static_cast <uint64_t> (ROL(KA, 94, 128) >> 64);
//        uint64_t k22 = static_cast <uint64_t> (ROL(KA, 94, 128));
//        uint64_t k23 = static_cast <uint64_t> (ROL(KL, 111, 128) >> 64);
//        uint64_t k24 = static_cast <uint64_t> (ROL(KL, 111, 128));
//        uint64_t kw3 = static_cast <uint64_t> (ROL(KB, 111, 128) >> 64);
//        uint64_t kw4 = static_cast <uint64_t> (ROL(KB, 111, 128));
//        keys.push_back(kw1);
//        keys.push_back(kw2);
//        keys.push_back(k1);
//        keys.push_back(k2);
//        keys.push_back(k3);
//        keys.push_back(k4);
//        keys.push_back(k5);
//        keys.push_back(k6);
//        keys.push_back(k7);
//        keys.push_back(k8);
//        keys.push_back(k9);
//        keys.push_back(k10);
//        keys.push_back(k11);
//        keys.push_back(k12);
//        keys.push_back(ke1);
//        keys.push_back(ke2);
//        keys.push_back(ke3);
//        keys.push_back(ke4);
//        keys.push_back(ke5);
//        keys.push_back(ke6);
//        keys.push_back(k13);
//        keys.push_back(k14);
//        keys.push_back(k15);
//        keys.push_back(k16);
//        keys.push_back(k17);
//        keys.push_back(k18);
//        keys.push_back(k19);
//        keys.push_back(k20);
//        keys.push_back(k21);
//        keys.push_back(k22);
//        keys.push_back(k23);
//        keys.push_back(k24);
//        keys.push_back(kw4);
//        keys.push_back(kw3);
//    }
    keyset = true;
}

std::string Camellia::encrypt(const std::string & DATA){
    return run(DATA);
}

std::string Camellia::decrypt(const std::string & DATA){
    std::reverse(keys.begin(), keys.end());
    std::string out = run(DATA);
    std::reverse(keys.begin(), keys.end());
    return out;
}

unsigned int Camellia::blocksize() const{
    return 128;
}
