#include "Twofish.h"

#include "../common/cryptomath.h"

uint32_t Twofish::h_fun(uint32_t x, const std::vector<uint32_t> & key){
    uint32_t b0, b1, b2, b3;
    b0 = byte(x, 0);
    b1 = byte(x, 1);
    b2 = byte(x, 2);
    b3 = byte(x, 3);

    if (key.size() >= 4){
        b0 = q_tab[1][b0] ^ byte(key[3], 0);
        b1 = q_tab[0][b1] ^ byte(key[3], 1);
        b2 = q_tab[0][b2] ^ byte(key[3], 2);
        b3 = q_tab[1][b3] ^ byte(key[3], 3);
    }
    if (key.size() >= 3){
        b0 = q_tab[1][b0] ^ byte(key[2], 0);
        b1 = q_tab[1][b1] ^ byte(key[2], 1);
        b2 = q_tab[0][b2] ^ byte(key[2], 2);
        b3 = q_tab[0][b3] ^ byte(key[2], 3);
    }
    b0 = q_tab[0][q_tab[0][b0] ^ byte(key[1], 0)] ^ byte(key[0], 0);
    b1 = q_tab[0][q_tab[1][b1] ^ byte(key[1], 1)] ^ byte(key[0], 1);
    b2 = q_tab[1][q_tab[0][b2] ^ byte(key[1], 2)] ^ byte(key[0], 2);
    b3 = q_tab[1][q_tab[1][b3] ^ byte(key[1], 3)] ^ byte(key[0], 3);

    return m_tab[0][b0] ^ m_tab[1][b1] ^ m_tab[2][b2] ^ m_tab[3][b3];
}

std::string Twofish::run(const std::string & data, bool enc){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set");
    }

    if (data.size() != 16){
        throw std::runtime_error("Error: Data must be 128 bits in length.");
    }
    uint32_t t0, t1;
    std::vector<uint32_t> blk(4, 0);
    blk[0] = toint(little_end(data.substr(0, 4), 256), 256);
    blk[1] = toint(little_end(data.substr(4, 4), 256), 256);
    blk[2] = toint(little_end(data.substr(8, 4), 256), 256);
    blk[3] = toint(little_end(data.substr(12, 4), 256), 256);

    blk[0] ^= l_key[enc?0:4];
    blk[1] ^= l_key[enc?1:5];
    blk[2] ^= l_key[enc?2:6];
    blk[3] ^= l_key[enc?3:7];

    if (enc){
        for(uint8_t i = 0; i < 8; i++){
            t1 = mk_tab[0][byte(blk[1],3)] ^ mk_tab[1][byte(blk[1],0)] ^ mk_tab[2][byte(blk[1],1)] ^ mk_tab[3][byte(blk[1],2)];
            t0 = mk_tab[0][byte(blk[0],0)] ^ mk_tab[1][byte(blk[0],1)] ^ mk_tab[2][byte(blk[0],2)] ^ mk_tab[3][byte(blk[0],3)];
            blk[2] = ROR(blk[2] ^ (t0 + t1 + l_key[4 * i + 8]), 1, 32);
            blk[3] = ROL(blk[3], 1, 32) ^ (t0 + 2 * t1 + l_key[4 * i + 9]);
            t1 = mk_tab[0][byte(blk[3],3)] ^ mk_tab[1][byte(blk[3],0)] ^ mk_tab[2][byte(blk[3],1)] ^ mk_tab[3][byte(blk[3],2)];
            t0 = mk_tab[0][byte(blk[2],0)] ^ mk_tab[1][byte(blk[2],1)] ^ mk_tab[2][byte(blk[2],2)] ^ mk_tab[3][byte(blk[2],3)];
            blk[0] = ROR(blk[0] ^ (t0 + t1 + l_key[4 * i + 10]), 1, 32);
            blk[1] = ROL(blk[1], 1, 32) ^ (t0 + 2 * t1 + l_key[4 * i + 11]);
        }
    } else {
        for(int i = 7; i >= 0; i--){
            t1 = mk_tab[0][byte(blk[1],3)] ^ mk_tab[1][byte(blk[1],0)] ^ mk_tab[2][byte(blk[1],1)] ^ mk_tab[3][byte(blk[1],2)];
            t0 = mk_tab[0][byte(blk[0],0)] ^ mk_tab[1][byte(blk[0],1)] ^ mk_tab[2][byte(blk[0],2)] ^ mk_tab[3][byte(blk[0],3)];
            blk[2] = ROL(blk[2], 1, 32) ^ (t0 + t1 + l_key[4 * i + 10]);
            blk[3] = ROR(blk[3] ^ (t0 + 2 * t1 + l_key[4 * i + 11]), 1, 32);
            t1 = mk_tab[0][byte(blk[3],3)] ^ mk_tab[1][byte(blk[3],0)] ^ mk_tab[2][byte(blk[3],1)] ^ mk_tab[3][byte(blk[3],2)];
            t0 = mk_tab[0][byte(blk[2],0)] ^ mk_tab[1][byte(blk[2],1)] ^ mk_tab[2][byte(blk[2],2)] ^ mk_tab[3][byte(blk[2],3)];
            blk[0] = ROL(blk[0], 1, 32) ^ (t0 + t1 + l_key[4 * i + 8]);
            blk[1] = ROR(blk[1] ^ (t0 + 2 * t1 + l_key[4 * i + 9]), 1, 32);
        }

    }

    blk[2] ^= l_key[enc?4:0];
    blk[3] ^= l_key[enc?5:1];
    blk[0] ^= l_key[enc?6:2];
    blk[1] ^= l_key[enc?7:3];

    std::swap(blk[0], blk[2]);
    std::swap(blk[1], blk[3]);

    return unhexlify(little_end(makehex(blk[0], 8)) + little_end(makehex(blk[1], 8)) + little_end(makehex(blk[2], 8)) + little_end(makehex(blk[3], 8)));
}

Twofish::Twofish()
    : SymAlg(),
      l_key(),
      mk_tab()
{}

Twofish::Twofish(const std::string & KEY)
    : Twofish()
{
    setkey(KEY);
}

void Twofish::setkey(const std::string & KEY){
    if (keyset){
        throw std::runtime_error("Error: Key has already been set.");
    }

    uint8_t n = KEY.size();
    if ((n != 16) && (n != 24) && (n != 32)){
        throw std::runtime_error("Error: Key size does not fit defined sizes.");
    }
    uint8_t k_len = n >> 3;

    uint32_t a, b;
    std::vector<uint32_t> me_key(k_len, 0), mo_key(k_len, 0), s_key(k_len, 0);

    std::vector<uint32_t> in_key(k_len<<1, 0);
    for( uint8_t i = 0; i < (k_len<<1); i++ ){
       in_key[i] = toint(little_end(KEY.substr(i*4, 4), 256), 256);
    }

    l_key.resize(40, 0);
    for(uint8_t i = 0; i < k_len; i++){
        a = in_key[i<<1];
        me_key[i] = a;
        b = in_key[(i<<1)+1];
        mo_key[i] = b;

        uint32_t t, u;
        for(uint8_t x = 0; x < 8; x++){
            // get most significant coefficient
            t = b >> 24;

            // shift others up
            b = (b << 8) | (a >> 24);
            a <<= 8;

            // multiply t by a (the primitive element - i.e. left shift)

            u = (t << 1);

            // subtract modular polynomial on overflow
            if(t & 0x80){
                u ^= G_MOD;
            }

            // remove t * (a * x^2 + 1)
            b ^= t ^ (u << 16);

            // form u = a * t + t / a = t * (a + 1 / a);
            u ^= (t >> 1);

            // add the modular polynomial on underflow
            if(t & 0x01){
                u ^= G_MOD >> 1;
            }

            // remove t * (a + 1/a) * (x^3 + x)
            b ^= (u << 24) | (u << 8);
        }
        s_key[k_len - i - 1] = b;
    }

    for(uint8_t i = 0; i < 40; i += 2){
        a = 0x01010101 * i;
        b = a + 0x01010101;
        a = h_fun(a, me_key);
        b = ROL(h_fun(b, mo_key), 8, 32);
        l_key[i] = a + b;
        l_key[i + 1] = ROL(a + (b<<1), 9, 32);
    }

    mk_tab.resize(4, std::vector<uint32_t>(256, 0));
    if (k_len == 2){
        for (uint16_t i = 0; i < 256; i++){
            mk_tab[0][i] = m_tab[0][q_tab[0][q_tab[0][i] ^ byte(s_key[1],0)] ^ byte(s_key[0],0)];
            mk_tab[1][i] = m_tab[1][q_tab[0][q_tab[1][i] ^ byte(s_key[1],1)] ^ byte(s_key[0],1)];
            mk_tab[2][i] = m_tab[2][q_tab[1][q_tab[0][i] ^ byte(s_key[1],2)] ^ byte(s_key[0],2)];
            mk_tab[3][i] = m_tab[3][q_tab[1][q_tab[1][i] ^ byte(s_key[1],3)] ^ byte(s_key[0],3)];
        }
    } else if (k_len == 3){
        for (uint16_t i = 0; i < 256; i++){
            mk_tab[0][i] = m_tab[0][q_tab[0][q_tab[0][q_tab[1][i] ^ byte(s_key[2], 0)] ^ byte(s_key[1], 0)] ^ byte(s_key[0], 0)];
            mk_tab[1][i] = m_tab[1][q_tab[0][q_tab[1][q_tab[1][i] ^ byte(s_key[2], 1)] ^ byte(s_key[1], 1)] ^ byte(s_key[0], 1)];
            mk_tab[2][i] = m_tab[2][q_tab[1][q_tab[0][q_tab[0][i] ^ byte(s_key[2], 2)] ^ byte(s_key[1], 2)] ^ byte(s_key[0], 2)];
            mk_tab[3][i] = m_tab[3][q_tab[1][q_tab[1][q_tab[0][i] ^ byte(s_key[2], 3)] ^ byte(s_key[1], 3)] ^ byte(s_key[0], 3)];
        }
    } else if (k_len == 4){
        for (uint16_t i = 0; i < 256; i++){
            mk_tab[0][i] = m_tab[0][q_tab[0][q_tab[0][q_tab[1][q_tab[1][i] ^ byte(s_key[3], 0)] ^ byte(s_key[2], 0)] ^ byte(s_key[1], 0)] ^ byte(s_key[0], 0)];
            mk_tab[1][i] = m_tab[1][q_tab[0][q_tab[1][q_tab[1][q_tab[0][i] ^ byte(s_key[3], 1)] ^ byte(s_key[2], 1)] ^ byte(s_key[1], 1)] ^ byte(s_key[0], 1)];
            mk_tab[2][i] = m_tab[2][q_tab[1][q_tab[0][q_tab[0][q_tab[0][i] ^ byte(s_key[3], 2)] ^ byte(s_key[2], 2)] ^ byte(s_key[1], 2)] ^ byte(s_key[0], 2)];
            mk_tab[3][i] = m_tab[3][q_tab[1][q_tab[1][q_tab[0][q_tab[1][i] ^ byte(s_key[3], 3)] ^ byte(s_key[2], 3)] ^ byte(s_key[1], 3)] ^ byte(s_key[0], 3)];
        }
    }

    keyset = true;
}

std::string Twofish::encrypt(const std::string & DATA){
    return run(DATA, true);
}
std::string Twofish::decrypt(const std::string & DATA){
    return run(DATA, false);
}

unsigned int Twofish::blocksize() const {
    return 128;
}
