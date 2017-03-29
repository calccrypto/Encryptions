#include "Camellia.h"

uint8_t Camellia::SBOX(const uint8_t s, const uint8_t value){
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

std::string Camellia::FL(const std::string & FL_IN, const std::string & KE){
    std::string x1 = FL_IN.substr(0, 4);
    std::string x2 = FL_IN.substr(4, 4);
    const std::string k1 = KE.substr(0, 4);
    const std::string k2 = KE.substr(4, 4);
    x2 = xor_strings(x2, ROL(and_strings(x1, k1), 1));
    x1 = xor_strings(x1, or_strings(x2, k2));
    return x1 + x2;
}

std::string Camellia::FLINV(const std::string & FLINV_IN, const std::string & KE){
    std::string y1 = FLINV_IN.substr(0, 4);
    std::string y2 = FLINV_IN.substr(4, 4);
    const std::string k1 = KE.substr(0, 4);
    const std::string k2 = KE.substr(4, 4);
    y1 = xor_strings(y1, or_strings(y2, k2));
    y2 = xor_strings(y2, ROL(and_strings(y1, k1), 1));
    return y1 + y2;
}

std::string Camellia::F(const std::string & F_IN, const std::string & KE){
    const std::string x = xor_strings(F_IN, KE);
    const uint8_t t1 = SBOX(1, x[0]);
    const uint8_t t2 = SBOX(2, x[1]);
    const uint8_t t3 = SBOX(3, x[2]);
    const uint8_t t4 = SBOX(4, x[3]);
    const uint8_t t5 = SBOX(2, x[4]);
    const uint8_t t6 = SBOX(3, x[5]);
    const uint8_t t7 = SBOX(4, x[6]);
    const uint8_t t8 = SBOX(1, x[7]);
    const uint8_t y1 = t1 ^ t3 ^ t4 ^ t6 ^ t7 ^ t8;
    const uint8_t y2 = t1 ^ t2 ^ t4 ^ t5 ^ t7 ^ t8;
    const uint8_t y3 = t1 ^ t2 ^ t3 ^ t5 ^ t6 ^ t8;
    const uint8_t y4 = t2 ^ t3 ^ t4 ^ t5 ^ t6 ^ t7;
    const uint8_t y5 = t1 ^ t2 ^ t6 ^ t7 ^ t8;
    const uint8_t y6 = t2 ^ t3 ^ t5 ^ t7 ^ t8;
    const uint8_t y7 = t3 ^ t4 ^ t5 ^ t6 ^ t8;
    const uint8_t y8 = t1 ^ t4 ^ t5 ^ t6 ^ t7;
    return std::string(1, y1) +
           std::string(1, y2) +
           std::string(1, y3) +
           std::string(1, y4) +
           std::string(1, y5) +
           std::string(1, y6) +
           std::string(1, y7) +
           std::string(1, y8);
}

std::string Camellia::run(const std::string & data){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }

    if (data.size() != 16){
        throw std::runtime_error("Error: Data must be 128 bits in length.");
    }

    std::string D1 = data.substr(0, 8);
    std::string D2 = data.substr(8, 8);
    if (keysize == 16){
        const std::string & kw1 = keys[0];
        const std::string & kw2 = keys[1];
        const std::string & k1  = keys[2];
        const std::string & k2  = keys[3];
        const std::string & k3  = keys[4];
        const std::string & k4  = keys[5];
        const std::string & k5  = keys[6];
        const std::string & k6  = keys[7];
        const std::string & k7  = keys[8];
        const std::string & k8  = keys[9];
        const std::string & k9  = keys[10];
        const std::string & ke1 = keys[11];
        const std::string & ke2 = keys[12];
        const std::string & ke3 = keys[13];
        const std::string & ke4 = keys[14];
        const std::string & k10 = keys[15];
        const std::string & k11 = keys[16];
        const std::string & k12 = keys[17];
        const std::string & k13 = keys[18];
        const std::string & k14 = keys[19];
        const std::string & k15 = keys[20];
        const std::string & k16 = keys[21];
        const std::string & k17 = keys[22];
        const std::string & k18 = keys[23];
        const std::string & kw4 = keys[24];
        const std::string & kw3 = keys[25];
        D1 = xor_strings(D1, kw1);
        D2 = xor_strings(D2, kw2);
        D2 = xor_strings(D2, F(D1, k1));
        D1 = xor_strings(D1, F(D2, k2));
        D2 = xor_strings(D2, F(D1, k3));
        D1 = xor_strings(D1, F(D2, k4));
        D2 = xor_strings(D2, F(D1, k5));
        D1 = xor_strings(D1, F(D2, k6));
        D1 = FL(D1, ke1);
        D2 = FLINV(D2, ke2);
        D2 = xor_strings(D2, F(D1, k7));
        D1 = xor_strings(D1, F(D2, k8));
        D2 = xor_strings(D2, F(D1, k9));
        D1 = xor_strings(D1, F(D2, k10));
        D2 = xor_strings(D2, F(D1, k11));
        D1 = xor_strings(D1, F(D2, k12));
        D1 = FL(D1, ke3);
        D2 = FLINV(D2, ke4);
        D2 = xor_strings(D2, F(D1, k13));
        D1 = xor_strings(D1, F(D2, k14));
        D2 = xor_strings(D2, F(D1, k15));
        D1 = xor_strings(D1, F(D2, k16));
        D2 = xor_strings(D2, F(D1, k17));
        D1 = xor_strings(D1, F(D2, k18));
        D2 = xor_strings(D2, kw3);
        D1 = xor_strings(D1, kw4);
    }
    else{
        const std::string & kw1 = keys[0];
        const std::string & kw2 = keys[1];
        const std::string & k1  = keys[2];
        const std::string & k2  = keys[3];
        const std::string & k3  = keys[4];
        const std::string & k4  = keys[5];
        const std::string & k5  = keys[6];
        const std::string & k6  = keys[7];
        const std::string & k7  = keys[8];
        const std::string & k8  = keys[9];
        const std::string & k9  = keys[10];
        const std::string & k10 = keys[11];
        const std::string & k11 = keys[12];
        const std::string & k12 = keys[13];
        const std::string & ke1 = keys[14];
        const std::string & ke2 = keys[15];
        const std::string & ke3 = keys[16];
        const std::string & ke4 = keys[17];
        const std::string & ke5 = keys[18];
        const std::string & ke6 = keys[19];
        const std::string & k13 = keys[20];
        const std::string & k14 = keys[21];
        const std::string & k15 = keys[22];
        const std::string & k16 = keys[23];
        const std::string & k17 = keys[24];
        const std::string & k18 = keys[25];
        const std::string & k19 = keys[26];
        const std::string & k20 = keys[27];
        const std::string & k21 = keys[28];
        const std::string & k22 = keys[29];
        const std::string & k23 = keys[30];
        const std::string & k24 = keys[31];
        const std::string & kw4 = keys[32];
        const std::string & kw3 = keys[33];
        D1 = xor_strings(D1, kw1);
        D2 = xor_strings(D2, kw2);
        D2 = xor_strings(D2, F(D1, k1));
        D1 = xor_strings(D1, F(D2, k2));
        D2 = xor_strings(D2, F(D1, k3));
        D1 = xor_strings(D1, F(D2, k4));
        D2 = xor_strings(D2, F(D1, k5));
        D1 = xor_strings(D1, F(D2, k6));
        D1 = FL(D1, ke1);
        D2 = FLINV(D2, ke2);
        D2 = xor_strings(D2, F(D1, k7));
        D1 = xor_strings(D1, F(D2, k8));
        D2 = xor_strings(D2, F(D1, k9));
        D1 = xor_strings(D1, F(D2, k10));
        D2 = xor_strings(D2, F(D1, k11));
        D1 = xor_strings(D1, F(D2, k12));
        D1 = FL(D1, ke3);
        D2 = FLINV(D2, ke4);
        D2 = xor_strings(D2, F(D1, k13));
        D1 = xor_strings(D1, F(D2, k14));
        D2 = xor_strings(D2, F(D1, k15));
        D1 = xor_strings(D1, F(D2, k16));
        D2 = xor_strings(D2, F(D1, k17));
        D1 = xor_strings(D1, F(D2, k18));
        D1 = FL(D1, ke5);
        D2 = FLINV(D2, ke6);
        D2 = xor_strings(D2, F(D1, k19));
        D1 = xor_strings(D1, F(D2, k20));
        D2 = xor_strings(D2, F(D1, k21));
        D1 = xor_strings(D1, F(D2, k22));
        D2 = xor_strings(D2, F(D1, k23));
        D1 = xor_strings(D1, F(D2, k24));
        D2 = xor_strings(D2, kw3);
        D1 = xor_strings(D1, kw4);
    }
    return D2 + D1;
}

Camellia::Camellia()
    : SymAlg(),
    keysize(0),
    keys()
{}

Camellia::Camellia(const std::string & KEY) 
    : Camellia()
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

    std::string KL, KR;
    if (keysize == 16){
        KL = KEY;
        KR = std::string(16, 0);
    }
    else if (keysize == 24){
        KL = KEY.substr(0, 16);
        KR = KEY.substr(16, 8); KR += xor_strings(KR, unhexlify("ffffffffffffffff"));
    }
    else if (keysize == 32){
        KL = KEY.substr(0, 16);
        KR = KEY.substr(16, 16);
    }

    const std::string D = xor_strings(KL, KR);
    std::string D1 = D.substr(0, 8);
    std::string D2 = D.substr(8, 8);

    D2 = xor_strings(D2, F(D1, Camellia_Sigma[0]));
    D1 = xor_strings(D1, F(D2, Camellia_Sigma[1]));
    D1 = xor_strings(D1, KL.substr(0, 8));
    D2 = xor_strings(D2, KL.substr(8, 8));
    D2 = xor_strings(D2, F(D1, Camellia_Sigma[2]));
    D1 = xor_strings(D1, F(D2, Camellia_Sigma[3]));
    std::string KA = D1 + D2;

    const std::string AR = xor_strings(KA, KR);
    D1 = AR.substr(0, 8);
    D2 = AR.substr(8, 8);
    D2 = xor_strings(D2, F(D1, Camellia_Sigma[4]));
    D1 = xor_strings(D1, F(D2, Camellia_Sigma[5]));
    std::string KB = D1 + D2;

    std::string T;
    if (keysize == 16){
        T = ROL(KL, 0);
        keys.push_back(T.substr(0, 8)); // kw1
        keys.push_back(T.substr(8, 8)); // kw2
        T = ROL(KA, 0);
        keys.push_back(T.substr(0, 8)); // k1
        keys.push_back(T.substr(8, 8)); // k2
        T = ROL(KL, 15);
        keys.push_back(T.substr(0, 8)); // k3
        keys.push_back(T.substr(8, 8)); // k4
        T = ROL(KA, 15);
        keys.push_back(T.substr(0, 8)); // k5
        keys.push_back(T.substr(8, 8)); // k6
        T = ROL(KL, 45);
        keys.push_back(T.substr(0, 8)); // k7
        keys.push_back(T.substr(8, 8)); // k8
        T = ROL(KA, 45);
        keys.push_back(T.substr(0, 8)); // k9
        T = ROL(KA, 30);
        keys.push_back(T.substr(0, 8)); // ke1
        keys.push_back(T.substr(8, 8)); // ke2
        T = ROL(KL, 77);
        keys.push_back(T.substr(0, 8)); // ke3
        keys.push_back(T.substr(8, 8)); // ke4
        T = ROL(KL, 60);
        keys.push_back(T.substr(8, 8)); // k10
        T = ROL(KA, 60);
        keys.push_back(T.substr(0, 8)); // k11
        keys.push_back(T.substr(8, 8)); // k12
        T = ROL(KL, 94);
        keys.push_back(T.substr(0, 8)); // k13
        keys.push_back(T.substr(8, 8)); // k14
        T = ROL(KA, 94);
        keys.push_back(T.substr(0, 8)); // k15
        keys.push_back(T.substr(8, 8)); // k16
        T = ROL(KL, 111);
        keys.push_back(T.substr(0, 8)); // k17
        keys.push_back(T.substr(8, 8)); // k18
        T = ROL(KA, 111);
        keys.push_back(T.substr(8, 8)); // kw4
        keys.push_back(T.substr(0, 8)); // kw3
    }
    else{
        T = ROL(KL, 0);
        keys.push_back(T.substr(0, 8)); // kw1
        keys.push_back(T.substr(8, 8)); // kw2
        T = ROL(KB, 0);
        keys.push_back(T.substr(0, 8)); // k1
        keys.push_back(T.substr(8, 8)); // k2
        T = ROL(KR, 15);
        keys.push_back(T.substr(0, 8)); // k3
        keys.push_back(T.substr(8, 8)); // k4
        T = ROL(KA, 15);
        keys.push_back(T.substr(0, 8)); // k5
        keys.push_back(T.substr(8, 8)); // k6
        T = ROL(KB, 30);
        keys.push_back(T.substr(0, 8)); // k7
        keys.push_back(T.substr(8, 8)); // k8
        T = ROL(KL, 45);
        keys.push_back(T.substr(0, 8)); // k9
        keys.push_back(T.substr(8, 8)); // k10
        T = ROL(KA, 45);
        keys.push_back(T.substr(0, 8)); // k11
        keys.push_back(T.substr(8, 8)); // k12
        T = ROL(KR, 30);
        keys.push_back(T.substr(0, 8)); // ke1
        keys.push_back(T.substr(8, 8)); // ke2
        T = ROL(KL, 60);
        keys.push_back(T.substr(0, 8)); // ke3
        keys.push_back(T.substr(8, 8)); // ke4
        T = ROL(KA, 77);
        keys.push_back(T.substr(0, 8)); // ke5
        keys.push_back(T.substr(8, 8)); // ke6
        T = ROL(KR, 60);
        keys.push_back(T.substr(0, 8)); // k13
        keys.push_back(T.substr(8, 8)); // k14
        T = ROL(KB, 60);
        keys.push_back(T.substr(0, 8)); // k15
        keys.push_back(T.substr(8, 8)); // k16
        T = ROL(KL, 77);
        keys.push_back(T.substr(0, 8)); // k17
        keys.push_back(T.substr(8, 8)); // k18
        T = ROL(KR, 94);
        keys.push_back(T.substr(0, 8)); // k19
        keys.push_back(T.substr(8, 8)); // k20
        T = ROL(KA, 94);
        keys.push_back(T.substr(0, 8)); // k21
        keys.push_back(T.substr(8, 8)); // k22
        T = ROL(KL, 111);
        keys.push_back(T.substr(0, 8)); // k23
        keys.push_back(T.substr(8, 8)); // k24
        T = ROL(KB, 111);
        keys.push_back(T.substr(8, 8)); // kw4
        keys.push_back(T.substr(0, 8)); // kw3
    }

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

unsigned int Camellia::blocksize() const {
    return 128;
}
