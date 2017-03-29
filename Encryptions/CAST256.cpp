#include "CAST256.h"

uint32_t CAST256::F1(const uint32_t Data, const uint32_t Kmi, const uint8_t Kri){
    uint32_t temp = ROL((Kmi + Data) & mod32, Kri, 32);
    uint8_t Ia = temp >> 24, Ib = (temp >> 16) & 255, Ic = (temp >> 8) & 255, Id = temp & 255;
    return ((CAST_S1[Ia] ^ CAST_S2[Ib]) - CAST_S3[Ic] + CAST_S4[Id]) & mod32;
}

uint32_t CAST256::F2(const uint32_t Data, const uint32_t Kmi, const uint8_t Kri){
    uint32_t temp = ROL(Kmi ^ Data, Kri, 32);
    uint8_t Ia = temp >> 24, Ib = (temp >> 16) & 255, Ic = (temp >> 8) & 255, Id = temp & 255;
    return ((CAST_S1[Ia] - CAST_S2[Ib] + CAST_S3[Ic]) & mod32) ^ CAST_S4[Id];
}

uint32_t CAST256::F3(const uint32_t Data, const uint32_t Kmi, const uint8_t Kri){
    uint32_t temp = ROL((Kmi - Data) & mod32, Kri, 32);
    uint8_t Ia = temp >> 24, Ib = (temp >> 16) & 255, Ic = (temp >> 8) & 255, Id = temp & 255;
    return ((((CAST_S1[Ia] + CAST_S2[Ib]) & mod32) ^ CAST_S3[Ic]) - CAST_S4[Id]) & mod32;
}

void CAST256::W(const uint8_t i){
    g ^= F1(h, Tm[0][i], Tr[0][i]);
    f ^= F2(g, Tm[1][i], Tr[1][i]);
    e ^= F3(f, Tm[2][i], Tr[2][i]);
    d ^= F1(e, Tm[3][i], Tr[3][i]);
    c ^= F2(d, Tm[4][i], Tr[4][i]);
    b ^= F3(c, Tm[5][i], Tr[5][i]);
    a ^= F1(b, Tm[6][i], Tr[6][i]);
    h ^= F2(a, Tm[7][i], Tr[7][i]);
}

std::vector <uint8_t> CAST256::kr(){
    std::vector <uint8_t> out;
    out.push_back(a & 31);
    out.push_back(c & 31);
    out.push_back(e & 31);
    out.push_back(g & 31);
    return out;
}

std::vector <uint32_t> CAST256::km(){
    std::vector <uint32_t> out;
    out.push_back(h);
    out.push_back(f);
    out.push_back(d);
    out.push_back(b);
    return out;
}

void CAST256::Q(const uint8_t & i){
    C ^= F1(D, Km[i][0], Kr[i][0]);
    B ^= F2(C, Km[i][1], Kr[i][1]);
    A ^= F3(B, Km[i][2], Kr[i][2]);
    D ^= F1(A, Km[i][3], Kr[i][3]);
}

void CAST256::QBAR(const uint8_t & i){
    D ^= F1(A, Km[i][3], Kr[i][3]);
    A ^= F3(B, Km[i][2], Kr[i][2]);
    B ^= F2(C, Km[i][1], Kr[i][1]);
    C ^= F1(D, Km[i][0], Kr[i][0]);
}

std::string CAST256::run(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }

    if (DATA.size() != 16){
        throw std::runtime_error("Error: Data must be 128 bits in length.");
    }

    A = toint(DATA.substr(0, 4), 256);
    B = toint(DATA.substr(4, 4), 256);
    C = toint(DATA.substr(8, 4), 256);
    D = toint(DATA.substr(12, 4), 256);
    for(uint8_t i = 0; i < 6; i++){
        Q(i);
    }
    for(uint8_t i = 6; i < 12; i++){
        QBAR(i);
    }
    return unhexlify(makehex(A, 8) + makehex(B, 8) + makehex(C, 8) + makehex(D, 8));
}

CAST256::CAST256()
    : SymAlg(),
      A(0), B(0), C(0), D(0), a(0), b(0), c(0), d(0), e(0), f(0), g (0), h(0),
      Kr(0), Tr(0),
      Km(0), Tm(0)
{}

CAST256::CAST256(const std::string & KEY)
    : CAST256()
{
    setkey(KEY);
}

void CAST256::setkey(std::string KEY){
    if (keyset){
        throw std::runtime_error("Error: Key has already been set.");
    }

    if ((KEY.size() != 16) && (KEY.size() != 20) && (KEY.size() != 24) && (KEY.size() != 28) && (KEY.size() != 32)){
        throw std::runtime_error("Error: Key must be 128, 160, 192, 224, or 256 bits in length.");
    }

    KEY += std::string(32 - KEY.size(), 0);
    a = toint(KEY.substr(0, 4), 256);
    b = toint(KEY.substr(4, 4), 256);
    c = toint(KEY.substr(8, 4), 256);
    d = toint(KEY.substr(12, 4), 256);
    e = toint(KEY.substr(16, 4), 256);
    f = toint(KEY.substr(20, 4), 256);
    g = toint(KEY.substr(24, 4), 256);
    h = toint(KEY.substr(28, 4), 256);

    uint32_t Cm = 0x5A827999, Mm = 0x6ED9EBA1, Cr = 19, Mr = 17;

    std::vector <uint8_t> range24_8(24, 0);
    std::vector <uint32_t> range24_32(24, 0);

    Tm.push_back(range24_32); Tr.push_back(range24_8);
    for(uint8_t x = 0; x < 8; x++){
        Tm.push_back(range24_32);
        Tr.push_back(range24_8);
    }
    for(uint8_t i = 0; i < 24; i++){
        for(uint8_t j = 0; j < 8; j++){
            Tm[j][i] = Cm;
            Cm = (Cm + Mm) & mod32;
            Tr[j][i] = Cr;
            Cr = (Cr + Mr) & 31;
        }
    }
    for(uint8_t i = 0; i < 12; i++){
        W(i << 1);
        W((i << 1) + 1);
        Kr.push_back(kr());
        Km.push_back(km());
    }

    keyset = true;
}

std::string CAST256::encrypt(const std::string & DATA){
    return run(DATA);
}

std::string CAST256::decrypt(const std::string & DATA){
    std::reverse(Kr.begin(), Kr.end());
    std::reverse(Km.begin(), Km.end());
    std::string out = run(DATA);
    std::reverse(Kr.begin(), Kr.end());
    std::reverse(Km.begin(), Km.end());
    return out;
}

unsigned int CAST256::blocksize() const {
    return 128;
}
