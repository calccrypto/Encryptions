#include "CAST128.h"

uint32_t CAST128::F(const uint8_t & round, const uint32_t & D, const uint32_t & Kmi, const uint8_t & Kri){
    uint32_t f = 0, I, Ia, Ib, Ic, Id;
    if ((round == 1) | (round == 4) | (round == 7) | (round == 10)| (round == 13) | (round == 16)){
        I = ROL((Kmi + D) & mod32, Kri, 32);
        Ia = I >> 24;
        Ib = (I >> 16) & 255;
        Ic = (I >> 8) & 255;
        Id = I & 255;
        f = ((CAST_S1[Ia] ^ CAST_S2[Ib]) - CAST_S3[Ic] + CAST_S4[Id]) & mod32;
    }
    if ((round == 2) | (round == 5) | (round == 8) | (round == 11)| (round == 14)){
        I = ROL(Kmi ^ D, Kri, 32);
        Ia = I >> 24;
        Ib = (I >> 16) & 255;
        Ic = (I >> 8) & 255;
        Id = I & 255;
        f = ((CAST_S1[Ia] - CAST_S2[Ib] + CAST_S3[Ic]) & mod32) ^ CAST_S4[Id];
    }
    if ((round == 3) | (round == 6) | (round == 9) | (round == 12)| (round == 15)){
        I = ROL((Kmi - D) & mod32, Kri, 32);
        Ia = I >> 24;
        Ib = (I >> 16) & 255;
        Ic = (I >> 8) & 255;
        Id = I & 255;
        f = ((((CAST_S1[Ia] + CAST_S2[Ib]) & mod32) ^ CAST_S3[Ic]) - CAST_S4[Id]) & mod32;
    }
    return f;
}

std::string CAST128::run(const std::string & DATA, const uint8_t start, const uint8_t stop, const uint8_t step){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }
    if (DATA.size() != 8){
        throw std::runtime_error("Error: Data must be 64 bits long.");
    }
    uint32_t left = toint(DATA.substr(0, 4), 256);
    uint32_t right = toint(DATA.substr(4, 4), 256);
    uint8_t i = start;
    while (i != stop){
        uint32_t temp = right;
        right = left ^ F(i, right, km[i - 1], kr[i - 1]);
        left = temp;
        i += step;
    }
    return unhexlify(makehex(right, 8) + makehex(left, 8));
}

CAST128::CAST128()
    : SymAlg(),
      rounds(0),
      kr(), km()
{}

CAST128::CAST128(const std::string & KEY)
    : CAST128()
{
    setkey(KEY);
}

void CAST128::setkey(std::string KEY){
    if (keyset){
        throw std::runtime_error("Error: Key has already been set.");
    }
    rounds = 12 + ((KEY.size() > 10) << 2);
    while (KEY.size() < 16){
        KEY += zero;
    }

    uint32_t x0 = static_cast <uint8_t> (KEY[0]);
    uint32_t x1 = static_cast <uint8_t> (KEY[1]);
    uint32_t x2 = static_cast <uint8_t> (KEY[2]);
    uint32_t x3 = static_cast <uint8_t> (KEY[3]);
    uint32_t x4 = static_cast <uint8_t> (KEY[4]);
    uint32_t x5 = static_cast <uint8_t> (KEY[5]);
    uint32_t x6 = static_cast <uint8_t> (KEY[6]);
    uint32_t x7 = static_cast <uint8_t> (KEY[7]);
    uint32_t x8 = static_cast <uint8_t> (KEY[8]);
    uint32_t x9 = static_cast <uint8_t> (KEY[9]);
    uint32_t xA = static_cast <uint8_t> (KEY[10]);
    uint32_t xB = static_cast <uint8_t> (KEY[11]);
    uint32_t xC = static_cast <uint8_t> (KEY[12]);
    uint32_t xD = static_cast <uint8_t> (KEY[13]);
    uint32_t xE = static_cast <uint8_t> (KEY[14]);
    uint32_t xF = static_cast <uint8_t> (KEY[15]);

    uint32_t z0, z1, z2, z3, z4, z5, z6, z7, z8, z9, zA, zB, zC, zD, zE, zF, temp;

    temp = ((x0 << 24) + (x1 << 16) + (x2 << 8) + x3) ^ CAST128_S5[xD] ^ CAST128_S6[xF] ^ CAST128_S7[xC] ^ CAST128_S8[xE] ^ CAST128_S7[x8];
    z0 = temp >> 24; z1 = (temp >> 16) & 255; z2 = (temp >> 8) & 255; z3 = temp & 255;
    temp = ((x8 << 24) + (x9 << 16) + (xA << 8) + xB) ^ CAST128_S5[z0] ^ CAST128_S6[z2] ^ CAST128_S7[z1] ^ CAST128_S8[z3] ^ CAST128_S8[xA];
    z4 = temp >> 24; z5 = (temp >> 16) & 255; z6 = (temp >> 8) & 255; z7 = temp & 255;
    temp = ((xC << 24) + (xD << 16) + (xE << 8) + xF) ^ CAST128_S5[z7] ^ CAST128_S6[z6] ^ CAST128_S7[z5] ^ CAST128_S8[z4] ^ CAST128_S5[x9];
    z8 = temp >> 24; z9 = (temp >> 16) & 255; zA = (temp >> 8) & 255; zB = temp & 255;
    temp = ((x4 << 24) + (x5 << 16) + (x6 << 8) + x7) ^ CAST128_S5[zA] ^ CAST128_S6[z9] ^ CAST128_S7[zB] ^ CAST128_S8[z8] ^ CAST128_S6[xB];
    zC = temp >> 24; zD = (temp >> 16) & 255; zE = (temp >> 8) & 255; zF = temp & 255;
    km[ 0] = CAST128_S5[z8] ^ CAST128_S6[z9] ^ CAST128_S7[z7] ^ CAST128_S8[z6] ^ CAST128_S5[z2];
    km[ 1] = CAST128_S5[zA] ^ CAST128_S6[zB] ^ CAST128_S7[z5] ^ CAST128_S8[z4] ^ CAST128_S6[z6];
    km[ 2] = CAST128_S5[zC] ^ CAST128_S6[zD] ^ CAST128_S7[z3] ^ CAST128_S8[z2] ^ CAST128_S7[z9];
    km[ 3] = CAST128_S5[zE] ^ CAST128_S6[zF] ^ CAST128_S7[z1] ^ CAST128_S8[z0] ^ CAST128_S8[zC];
    temp = ((z8 << 24) + (z9 << 16) + (zA << 8) + zB) ^ CAST128_S5[z5] ^ CAST128_S6[z7] ^ CAST128_S7[z4] ^ CAST128_S8[z6] ^ CAST128_S7[z0];
    x0 = temp >> 24; x1 = (temp >> 16) & 255; x2 = (temp >> 8) & 255; x3 = temp & 255;
    temp = ((z0 << 24) + (z1 << 16) + (z2 << 8) + z3) ^ CAST128_S5[x0] ^ CAST128_S6[x2] ^ CAST128_S7[x1] ^ CAST128_S8[x3] ^ CAST128_S8[z2];
    x4 = temp >> 24; x5 = (temp >> 16) & 255; x6 = (temp >> 8) & 255; x7 = temp & 255;
    temp = ((z4 << 24) + (z5 << 16) + (z6 << 8) + z7) ^ CAST128_S5[x7] ^ CAST128_S6[x6] ^ CAST128_S7[x5] ^ CAST128_S8[x4] ^ CAST128_S5[z1];
    x8 = temp >> 24; x9 = (temp >> 16) & 255; xA = (temp >> 8) & 255; xB = temp & 255;
    temp = ((zC << 24) + (zD << 16) + (zE << 8) + zF) ^ CAST128_S5[xA] ^ CAST128_S6[x9] ^ CAST128_S7[xB] ^ CAST128_S8[x8] ^ CAST128_S6[z3];
    xC = temp >> 24; xD = (temp >> 16) & 255; xE = (temp >> 8) & 255; xF = temp & 255;
    km[ 4] = CAST128_S5[x3] ^ CAST128_S6[x2] ^ CAST128_S7[xC] ^ CAST128_S8[xD] ^ CAST128_S5[x8];
    km[ 5] = CAST128_S5[x1] ^ CAST128_S6[x0] ^ CAST128_S7[xE] ^ CAST128_S8[xF] ^ CAST128_S6[xD];
    km[ 6] = CAST128_S5[x7] ^ CAST128_S6[x6] ^ CAST128_S7[x8] ^ CAST128_S8[x9] ^ CAST128_S7[x3];
    km[ 7] = CAST128_S5[x5] ^ CAST128_S6[x4] ^ CAST128_S7[xA] ^ CAST128_S8[xB] ^ CAST128_S8[x7];
    temp = ((x0 << 24) + (x1 << 16) + (x2 << 8) + x3) ^ CAST128_S5[xD] ^ CAST128_S6[xF] ^ CAST128_S7[xC] ^ CAST128_S8[xE] ^ CAST128_S7[x8];
    z0 = temp >> 24; z1 = (temp >> 16) & 255; z2 = (temp >> 8) & 255; z3 = temp & 255;
    temp = ((x8 << 24) + (x9 << 16) + (xA << 8) + xB) ^ CAST128_S5[z0] ^ CAST128_S6[z2] ^ CAST128_S7[z1] ^ CAST128_S8[z3] ^ CAST128_S8[xA];
    z4 = temp >> 24; z5 = (temp >> 16) & 255; z6 = (temp >> 8) & 255; z7 = temp & 255;
    temp = ((xC << 24) + (xD << 16) + (xE << 8) + xF) ^ CAST128_S5[z7] ^ CAST128_S6[z6] ^ CAST128_S7[z5] ^ CAST128_S8[z4] ^ CAST128_S5[x9];
    z8 = temp >> 24; z9 = (temp >> 16) & 255; zA = (temp >> 8) & 255; zB = temp & 255;
    temp = ((x4 << 24) + (x5 << 16) + (x6 << 8) + x7) ^ CAST128_S5[zA] ^ CAST128_S6[z9] ^ CAST128_S7[zB] ^ CAST128_S8[z8] ^ CAST128_S6[xB];
    zC = temp >> 24; zD = (temp >> 16) & 255; zE = (temp >> 8) & 255; zF = temp & 255;
    km[ 8] = CAST128_S5[z3] ^ CAST128_S6[z2] ^ CAST128_S7[zC] ^ CAST128_S8[zD] ^ CAST128_S5[z9];
    km[ 9] = CAST128_S5[z1] ^ CAST128_S6[z0] ^ CAST128_S7[zE] ^ CAST128_S8[zF] ^ CAST128_S6[zC];
    km[10] = CAST128_S5[z7] ^ CAST128_S6[z6] ^ CAST128_S7[z8] ^ CAST128_S8[z9] ^ CAST128_S7[z2];
    km[11] = CAST128_S5[z5] ^ CAST128_S6[z4] ^ CAST128_S7[zA] ^ CAST128_S8[zB] ^ CAST128_S8[z6];
    temp = ((z8 << 24) + (z9 << 16) + (zA << 8) + zB) ^ CAST128_S5[z5] ^ CAST128_S6[z7] ^ CAST128_S7[z4] ^ CAST128_S8[z6] ^ CAST128_S7[z0];
    x0 = temp >> 24; x1 = (temp >> 16) & 255; x2 = (temp >> 8) & 255; x3 = temp & 255;
    temp = ((z0 << 24) + (z1 << 16) + (z2 << 8) + z3) ^ CAST128_S5[x0] ^ CAST128_S6[x2] ^ CAST128_S7[x1] ^ CAST128_S8[x3] ^ CAST128_S8[z2];
    x4 = temp >> 24; x5 = (temp >> 16) & 255; x6 = (temp >> 8) & 255; x7 = temp & 255;
    temp = ((z4 << 24) + (z5 << 16) + (z6 << 8) + z7) ^ CAST128_S5[x7] ^ CAST128_S6[x6] ^ CAST128_S7[x5] ^ CAST128_S8[x4] ^ CAST128_S5[z1];
    x8 = temp >> 24; x9 = (temp >> 16) & 255; xA = (temp >> 8) & 255; xB = temp & 255;
    temp = ((zC << 24) + (zD << 16) + (zE << 8) + zF) ^ CAST128_S5[xA] ^ CAST128_S6[x9] ^ CAST128_S7[xB] ^ CAST128_S8[x8] ^ CAST128_S6[z3];
    xC = temp >> 24; xD = (temp >> 16) & 255; xE = (temp >> 8) & 255; xF = temp & 255;
    km[12] = CAST128_S5[x8] ^ CAST128_S6[x9] ^ CAST128_S7[x7] ^ CAST128_S8[x6] ^ CAST128_S5[x3];
    km[13] = CAST128_S5[xA] ^ CAST128_S6[xB] ^ CAST128_S7[x5] ^ CAST128_S8[x4] ^ CAST128_S6[x7];
    km[14] = CAST128_S5[xC] ^ CAST128_S6[xD] ^ CAST128_S7[x3] ^ CAST128_S8[x2] ^ CAST128_S7[x8];
    km[15] = CAST128_S5[xE] ^ CAST128_S6[xF] ^ CAST128_S7[x1] ^ CAST128_S8[x0] ^ CAST128_S8[xD];
    temp = ((x0 << 24) + (x1 << 16) + (x2 << 8) + x3) ^ CAST128_S5[xD] ^ CAST128_S6[xF] ^ CAST128_S7[xC] ^ CAST128_S8[xE] ^ CAST128_S7[x8];
    z0 = temp >> 24; z1 = (temp >> 16) & 255; z2 = (temp >> 8) & 255; z3 = temp & 255;
    temp = ((x8 << 24) + (x9 << 16) + (xA << 8) + xB) ^ CAST128_S5[z0] ^ CAST128_S6[z2] ^ CAST128_S7[z1] ^ CAST128_S8[z3] ^ CAST128_S8[xA];
    z4 = temp >> 24; z5 = (temp >> 16) & 255; z6 = (temp >> 8) & 255; z7 = temp & 255;
    temp = ((xC << 24) + (xD << 16) + (xE << 8) + xF) ^ CAST128_S5[z7] ^ CAST128_S6[z6] ^ CAST128_S7[z5] ^ CAST128_S8[z4] ^ CAST128_S5[x9];
    z8 = temp >> 24; z9 = (temp >> 16) & 255; zA = (temp >> 8) & 255; zB = temp & 255;
    temp = ((x4 << 24) + (x5 << 16) + (x6 << 8) + x7) ^ CAST128_S5[zA] ^ CAST128_S6[z9] ^ CAST128_S7[zB] ^ CAST128_S8[z8] ^ CAST128_S6[xB];
    zC = temp >> 24; zD = (temp >> 16) & 255; zE = (temp >> 8) & 255; zF = temp & 255;
    kr[ 0] = (CAST128_S5[z8] ^ CAST128_S6[z9] ^ CAST128_S7[z7] ^ CAST128_S8[z6] ^ CAST128_S5[z2]) & 31;
    kr[ 1] = (CAST128_S5[zA] ^ CAST128_S6[zB] ^ CAST128_S7[z5] ^ CAST128_S8[z4] ^ CAST128_S6[z6]) & 31;
    kr[ 2] = (CAST128_S5[zC] ^ CAST128_S6[zD] ^ CAST128_S7[z3] ^ CAST128_S8[z2] ^ CAST128_S7[z9]) & 31;
    kr[ 3] = (CAST128_S5[zE] ^ CAST128_S6[zF] ^ CAST128_S7[z1] ^ CAST128_S8[z0] ^ CAST128_S8[zC]) & 31;
    temp = ((z8 << 24) + (z9 << 16) + (zA << 8) + zB) ^ CAST128_S5[z5] ^ CAST128_S6[z7] ^ CAST128_S7[z4] ^ CAST128_S8[z6] ^ CAST128_S7[z0];
    x0 = temp >> 24; x1 = (temp >> 16) & 255; x2 = (temp >> 8) & 255; x3 = temp & 255;
    temp = ((z0 << 24) + (z1 << 16) + (z2 << 8) + z3) ^ CAST128_S5[x0] ^ CAST128_S6[x2] ^ CAST128_S7[x1] ^ CAST128_S8[x3] ^ CAST128_S8[z2];
    x4 = temp >> 24; x5 = (temp >> 16) & 255; x6 = (temp >> 8) & 255; x7 = temp & 255;
    temp = ((z4 << 24) + (z5 << 16) + (z6 << 8) + z7) ^ CAST128_S5[x7] ^ CAST128_S6[x6] ^ CAST128_S7[x5] ^ CAST128_S8[x4] ^ CAST128_S5[z1];
    x8 = temp >> 24; x9 = (temp >> 16) & 255; xA = (temp >> 8) & 255; xB = temp & 255;
    temp = ((zC << 24) + (zD << 16) + (zE << 8) + zF) ^ CAST128_S5[xA] ^ CAST128_S6[x9] ^ CAST128_S7[xB] ^ CAST128_S8[x8] ^ CAST128_S6[z3];
    xC = temp >> 24; xD = (temp >> 16) & 255; xE = (temp >> 8) & 255; xF = temp & 255;
    kr[ 4] = (CAST128_S5[x3] ^ CAST128_S6[x2] ^ CAST128_S7[xC] ^ CAST128_S8[xD] ^ CAST128_S5[x8]) & 31;
    kr[ 5] = (CAST128_S5[x1] ^ CAST128_S6[x0] ^ CAST128_S7[xE] ^ CAST128_S8[xF] ^ CAST128_S6[xD]) & 31;
    kr[ 6] = (CAST128_S5[x7] ^ CAST128_S6[x6] ^ CAST128_S7[x8] ^ CAST128_S8[x9] ^ CAST128_S7[x3]) & 31;
    kr[ 7] = (CAST128_S5[x5] ^ CAST128_S6[x4] ^ CAST128_S7[xA] ^ CAST128_S8[xB] ^ CAST128_S8[x7]) & 31;
    temp = ((x0 << 24) + (x1 << 16) + (x2 << 8) + x3) ^ CAST128_S5[xD] ^ CAST128_S6[xF] ^ CAST128_S7[xC] ^ CAST128_S8[xE] ^ CAST128_S7[x8];
    z0 = temp >> 24; z1 = (temp >> 16) & 255; z2 = (temp >> 8) & 255; z3 = temp & 255;
    temp = ((x8 << 24) + (x9 << 16) + (xA << 8) + xB) ^ CAST128_S5[z0] ^ CAST128_S6[z2] ^ CAST128_S7[z1] ^ CAST128_S8[z3] ^ CAST128_S8[xA];
    z4 = temp >> 24; z5 = (temp >> 16) & 255; z6 = (temp >> 8) & 255; z7 = temp & 255;
    temp = ((xC << 24) + (xD << 16) + (xE << 8) + xF) ^ CAST128_S5[z7] ^ CAST128_S6[z6] ^ CAST128_S7[z5] ^ CAST128_S8[z4] ^ CAST128_S5[x9];
    z8 = temp >> 24; z9 = (temp >> 16) & 255; zA = (temp >> 8) & 255; zB = temp & 255;
    temp = ((x4 << 24) + (x5 << 16) + (x6 << 8) + x7) ^ CAST128_S5[zA] ^ CAST128_S6[z9] ^ CAST128_S7[zB] ^ CAST128_S8[z8] ^ CAST128_S6[xB];
    zC = temp >> 24; zD = (temp >> 16) & 255; zE = (temp >> 8) & 255; zF = temp & 255;
    kr[ 8] = (CAST128_S5[z3] ^ CAST128_S6[z2] ^ CAST128_S7[zC] ^ CAST128_S8[zD] ^ CAST128_S5[z9]) & 31;
    kr[ 9] = (CAST128_S5[z1] ^ CAST128_S6[z0] ^ CAST128_S7[zE] ^ CAST128_S8[zF] ^ CAST128_S6[zC]) & 31;
    kr[10] = (CAST128_S5[z7] ^ CAST128_S6[z6] ^ CAST128_S7[z8] ^ CAST128_S8[z9] ^ CAST128_S7[z2]) & 31;
    kr[11] = (CAST128_S5[z5] ^ CAST128_S6[z4] ^ CAST128_S7[zA] ^ CAST128_S8[zB] ^ CAST128_S8[z6]) & 31;
    temp = ((z8 << 24) + (z9 << 16) + (zA << 8) + zB) ^ CAST128_S5[z5] ^ CAST128_S6[z7] ^ CAST128_S7[z4] ^ CAST128_S8[z6] ^ CAST128_S7[z0];
    x0 = temp >> 24; x1 = (temp >> 16) & 255; x2 = (temp >> 8) & 255; x3 = temp & 255;
    temp = ((z0 << 24) + (z1 << 16) + (z2 << 8) + z3) ^ CAST128_S5[x0] ^ CAST128_S6[x2] ^ CAST128_S7[x1] ^ CAST128_S8[x3] ^ CAST128_S8[z2];
    x4 = temp >> 24; x5 = (temp >> 16) & 255; x6 = (temp >> 8) & 255; x7 = temp & 255;
    temp = ((z4 << 24) + (z5 << 16) + (z6 << 8) + z7) ^ CAST128_S5[x7] ^ CAST128_S6[x6] ^ CAST128_S7[x5] ^ CAST128_S8[x4] ^ CAST128_S5[z1];
    x8 = temp >> 24; x9 = (temp >> 16) & 255; xA = (temp >> 8) & 255; xB = temp & 255;
    temp = ((zC << 24) + (zD << 16) + (zE << 8) + zF) ^ CAST128_S5[xA] ^ CAST128_S6[x9] ^ CAST128_S7[xB] ^ CAST128_S8[x8] ^ CAST128_S6[z3];
    xC = temp >> 24; xD = (temp >> 16) & 255; xE = (temp >> 8) & 255; xF = temp & 255;
    kr[12] = (CAST128_S5[x8] ^ CAST128_S6[x9] ^ CAST128_S7[x7] ^ CAST128_S8[x6] ^ CAST128_S5[x3]) & 31;
    kr[13] = (CAST128_S5[xA] ^ CAST128_S6[xB] ^ CAST128_S7[x5] ^ CAST128_S8[x4] ^ CAST128_S6[x7]) & 31;
    kr[14] = (CAST128_S5[xC] ^ CAST128_S6[xD] ^ CAST128_S7[x3] ^ CAST128_S8[x2] ^ CAST128_S7[x8]) & 31;
    kr[15] = (CAST128_S5[xE] ^ CAST128_S6[xF] ^ CAST128_S7[x1] ^ CAST128_S8[x0] ^ CAST128_S8[xD]) & 31;

    keyset = true;
}

std::string CAST128::encrypt(const std::string & DATA){
    return run(DATA, 1, rounds + 1, 1);
}

std::string CAST128::decrypt(const std::string & DATA){
    return run(DATA, rounds, 0, -1);
}

unsigned int CAST128::blocksize() const {
    return 64;
}
