#include "RC5.h"

RC5::RC5()
    : SymAlg(),
      w(0), r(0), b(0),
      mod(0)
{}

RC5::RC5(const std::string & KEY, const uint64_t & W, const uint64_t & R, const uint64_t & B)
    : RC5()
{
    setkey(KEY, W, R, B);
}

void RC5::setkey(std::string KEY, const uint64_t & W, const uint64_t & R, const uint64_t & B){
    if (keyset){
        throw std::runtime_error("Error: Key has already been set.");
    }

    w = W;
    r = R;
    b = B;
    mod = (1ULL << w) - 1;

    uint64_t p, q;
    rc_pq(w, p, q);

    uint64_t t = (r + 1) << 1;
    uint64_t u = (uint64_t) ceil(w / 8.);
    uint64_t c = (uint64_t) ceil((float) b / u);
    while (KEY.size() % u != 0){
        KEY += zero;
    }

    std::vector <uint64_t> L;
    for(unsigned int x = 0; x < c; x++){
        L.push_back(toint(little_end(KEY.substr(u * x, u), 256), 256));
    }

    S.push_back(p);
    for(unsigned int i = 1; i < t; i++){
        S.push_back((S[i - 1] + q) & mod);
    }

    uint64_t a = 0, b = 0, i = 0, j = 0, v = 3 * std::max(c, t);
    for(unsigned int x = 0; x < v; x++){
        a = S[i] = ROL(static_cast <uint32_t> (S[i] + a + b) & mod, 3, w);
        b = L[j] = ROL(static_cast <uint32_t> (L[j] + a + b) & mod, (a + b) % w, w);
        i = (i + 1) % t;
        j = (j + 1) % c;
    }

    keyset = true;
}

std::string RC5::encrypt(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }
    uint64_t A = toint(little_end(DATA.substr(0, w >> 3), 256), 256), B = toint(little_end(DATA.substr(w >> 3, (w >> 3)), 256), 256);
    A = (A + S[0]) & mod;
    B = (B + S[1]) & mod;
    for(uint8_t i = 1; i < r + 1; i++){
        A = (ROL(A ^ B, B % w, 32) + S[i << 1]) & mod;
        B = (ROL(A ^ B, A % w, 32) + S[(i << 1) + 1]) & mod;
    }
    return unhexlify(little_end(makehex(A & mod, w >> 2), 16) + little_end(makehex(B & mod, w >> 2), 16));
}

std::string RC5::decrypt(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }
    uint64_t A = toint(little_end(DATA.substr(0, w >> 3), 256), 256), B = toint(little_end(DATA.substr(w >> 3, (w >> 3)), 256), 256);
    for(uint8_t i = r; i > 0; i--){
        B = ROR((B - S[(i << 1) + 1]) & mod, A % w, 32) ^ A;
        A = ROR((A - S[i << 1]) & mod, B % w, 32) ^ B;
    }
    B = (B - S[1]) & mod;
    A = (A - S[0]) & mod;
    return unhexlify(little_end(makehex(A & mod, w >> 2), 16) + little_end(makehex(B & mod, w >> 2), 16));
}

unsigned int RC5::blocksize() const {
    return w << 1;
}
