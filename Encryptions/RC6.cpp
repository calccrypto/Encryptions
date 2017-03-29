#include "RC6.h"

RC6::RC6()
    : SymAlg(),
      w(0), r(0), b(0), lgw(0),
      S(0)
{}

RC6::RC6(const std::string & KEY, const unsigned int & W, const unsigned int & R)
    : RC6()
{
    setkey(KEY, W, R);
}

void RC6::setkey(std::string KEY, const unsigned int & W, const unsigned int & R){
    if (keyset){
        throw std::runtime_error("Error: Key has already been set.");
    }

    w = W;
    r = R;
    b = KEY.size();
    lgw = log2(w);

    uint64_t p, q;
    rc_pq(w, p, q);

    unsigned int u = (w >> 3) + (bool) (w & 7);
    unsigned int c = ceil(float(b) / u);
    while (KEY.size() % u){
        KEY += zero;
    }
    std::vector <uint32_t> L;
    for(unsigned int x = 0; x < c; x++){
        L.push_back(toint(little_end(KEY.substr(u * x, u), 256), 256));
    }
    S.push_back(p);
    for(unsigned int i = 0; i < 2 * r + 3; i++){
        S.push_back((S[i] + q));
    }
    uint32_t A = 0, B = 0, i = 0, j = 0;
    uint32_t v = 3 * std::max(c, (r << 1) + 4);
    for(unsigned int s = 1; s < v + 1; s++){
        A = S[i] = ROL((S[i] + A + B), 3, w);
        B = L[j] = ROL((L[j] + A + B), (A + B) % w, w);
        i = (i + 1) % ((r << 1) + 4);
        j = (j + 1) % c;
    }
    keyset = true;
}

std::string RC6::encrypt(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }

    uint32_t A = toint(little_end(DATA.substr(0, w >> 3), 256), 256), B = toint(little_end(DATA.substr(w >> 3, w >> 3), 256), 256), C = toint(little_end(DATA.substr(w >> 2, w >> 3), 256), 256), D = toint(little_end(DATA.substr(3 * (w >> 3), w >> 3), 256), 256);
    B += S[0];
    D += S[1];
    for(uint8_t i = 1; i < r + 1; i++){
        uint64_t t = ROL((B * (B + B + 1)), lgw, w);
        uint64_t u = ROL((D * (D + D + 1)), lgw, w);
        A = ROL(A ^ t, u % w, w) + S[i << 1];
        C = ROL(C ^ u, t % w, w) + S[(i << 1) + 1];
        uint64_t temp = A; A = B; B = C; C = D; D = temp;
    }
    A += S[(r << 1) + 2];
    C += S[(r << 1) + 3];
    return unhexlify(little_end(makehex(A, w >> 2)) + little_end(makehex(B, w >> 2)) + little_end(makehex(C, w >> 2)) + little_end(makehex(D, w >> 2)));
}

std::string RC6::decrypt(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }

    uint32_t A = toint(little_end(DATA.substr(0, w >> 3), 256), 256), B = toint(little_end(DATA.substr(w >> 3, w >> 3), 256), 256), C = toint(little_end(DATA.substr(w >> 2, w >> 3), 256), 256), D = toint(little_end(DATA.substr(3 * (w >> 3), w >> 3), 256), 256);
    C -= S[(r << 1) + 3];
    A -= S[(r << 1) + 2];
    for(uint8_t i = r; i > 0; i--){
        uint64_t temp = D; D = C; C = B; B = A; A = temp;
        uint64_t u = ROL((uint64_t) ((D * (D + D + 1))), lgw, w);
        uint64_t t = ROL((uint64_t) ((B * (B + B + 1))), lgw, w);
        C = ROR((C - S[(i << 1) + 1]), t % w, w) ^ u;
        A = ROR((A - S[i << 1]), u % w, w) ^ t;
    }
    D -= S[1];
    B -= S[0];
    return unhexlify(little_end(makehex(A, w >> 2)) + little_end(makehex(B, w >> 2)) + little_end(makehex(C, w >> 2)) + little_end(makehex(D, w >> 2)));
}

unsigned int RC6::blocksize() const {
    return w << 2;
}
