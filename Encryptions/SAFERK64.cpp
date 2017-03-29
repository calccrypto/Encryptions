#include "SAFERK64.h"

void SAFERK64::add_bias(std::vector <uint8_t> & key_i, const uint8_t b[8]){
    for(uint8_t i = 0; i < 8; i++){
        key_i[i] += b[i];
    }
}

std::vector <uint8_t> SAFERK64::byte_rotate_3(std::vector <uint8_t> & key_i){
    for(uint8_t i = 0; i < 8; i++){
        key_i[i] = ROL(key_i[i], 3, 8);
    }
    return key_i;
}

void SAFERK64::xor_add(std::vector <uint8_t> & data, std::vector <uint8_t> & key){
    data[0] ^= key[0];
    data[1] += key[1];
    data[2] += key[2];
    data[3] ^= key[3];
    data[4] ^= key[4];
    data[5] += key[5];
    data[6] += key[6];
    data[7] ^= key[7];
}

void SAFERK64::add_xor(std::vector <uint8_t> & data, std::vector <uint8_t> & key){
    data[0] += key[0];
    data[1] ^= key[1];
    data[2] ^= key[2];
    data[3] += key[3];
    data[4] += key[4];
    data[5] ^= key[5];
    data[6] ^= key[6];
    data[7] += key[7];
}

void SAFERK64::xor_sub(std::vector <uint8_t> & data, std::vector <uint8_t> & key){
    data[0] ^= key[0];
    data[1] -= key[1];
    data[2] -= key[2];
    data[3] ^= key[3];
    data[4] ^= key[4];
    data[5] -= key[5];
    data[6] -= key[6];
    data[7] ^= key[7];
}

void SAFERK64::sub_xor(std::vector <uint8_t> & data, std::vector <uint8_t> & key){
    data[0] -= key[0];
    data[1] ^= key[1];
    data[2] ^= key[2];
    data[3] -= key[3];
    data[4] -= key[4];
    data[5] ^= key[5];
    data[6] ^= key[6];
    data[7] -= key[7];
}

void SAFERK64::nonlinear_lajer(std::vector <uint8_t> & data){
    data[0] = SAFERK64_POW45[data[0]];
    data[1] = SAFERK64_LOG45[data[1]];
    data[2] = SAFERK64_LOG45[data[2]];
    data[3] = SAFERK64_POW45[data[3]];
    data[4] = SAFERK64_POW45[data[4]];
    data[5] = SAFERK64_LOG45[data[5]];
    data[6] = SAFERK64_LOG45[data[6]];
    data[7] = SAFERK64_POW45[data[7]];
}

void SAFERK64::inv_nonlinear_lajer(std::vector <uint8_t> & data){
    data[0] = SAFERK64_LOG45[data[0]];
    data[1] = SAFERK64_POW45[data[1]];
    data[2] = SAFERK64_POW45[data[2]];
    data[3] = SAFERK64_LOG45[data[3]];
    data[4] = SAFERK64_LOG45[data[4]];
    data[5] = SAFERK64_POW45[data[5]];
    data[6] = SAFERK64_POW45[data[6]];
    data[7] = SAFERK64_LOG45[data[7]];
}

void SAFERK64::pht(uint8_t & a1, uint8_t & a2){
    uint8_t b1 = (a1 << 1) + a2;
    uint8_t b2 = a1 + a2;
    a1 = b1; a2 = b2;
}

void SAFERK64::inv_pht(uint8_t & b1, uint8_t & b2){
    uint8_t a1 = b1 - b2;
    uint8_t a2 = (b2 << 1) - b1;
    b1 = a1; b2 = a2;
}

void SAFERK64::pht_layer(std::vector <uint8_t> & data){
    for(unsigned int j = 0; j < 4; j++){
        pht(data[j << 1], data[(j << 1) + 1]);
    }
    data = {data[0], data[2], data[4], data[6], data[1], data[3], data[5], data[7]};
    for(unsigned int j = 0; j < 4; j++){
        pht(data[j << 1], data[(j << 1) + 1]);
    }
    data = {data[0], data[2], data[4], data[6], data[1], data[3], data[5], data[7]};
    for(unsigned int j = 0; j < 4; j++){
        pht(data[j << 1], data[(j << 1) + 1]);
    }
}

void SAFERK64::inv_pht_layer(std::vector <uint8_t> & data){
    for(unsigned int j = 0; j < 4; j++){
        inv_pht(data[j << 1], data[(j << 1) + 1]);
    }
    data = {data[0], data[4], data[1], data[5], data[2], data[6], data[3], data[7]};
    for(unsigned int j = 0; j < 4; j++){
        inv_pht(data[j << 1], data[(j << 1) + 1]);
    }
    data = {data[0], data[4], data[1], data[5], data[2], data[6], data[3], data[7]};
    for(unsigned int j = 0; j < 4; j++){
        inv_pht(data[j << 1], data[(j << 1) + 1]);
    }
}

SAFERK64::SAFERK64()
    : SymAlg(),
      r(0),
      keys(0)
{}

SAFERK64::SAFERK64(const std::string & KEY, const uint8_t & rounds)
    : SAFERK64()
{
    setkey(KEY, rounds);
}

void SAFERK64::setkey(const std::string & KEY, const uint8_t & rounds){
    if (keyset){
        throw std::runtime_error("Error: Key has already been set.");
    }

    if (KEY.size() != 8){
        throw std::runtime_error("Error: Key must be 64 bits in length.");
    }

    r = rounds;
    std::vector <uint8_t> k;
    for(uint8_t i = 0; i < 8; i++){
        k.push_back(KEY[i]);
    }
    keys.push_back(k);
    for(uint8_t i = 0; i < (r << 1); i++){
        keys.push_back(byte_rotate_3(k));
        add_bias(keys[keys.size() - 1], (uint8_t *) SAFERK64_BIAS[i + 1]);
    }
    keyset = true;
}

std::string SAFERK64::encrypt(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }

    if (DATA.size() != 8){
        throw std::runtime_error("Error: Data must be 64 bits in length.");
    }

    std::vector <uint8_t> data;
    for(uint8_t i = 0; i < 8; i++){
        data.push_back(DATA[i]);
    }
    for(uint8_t i = 0; i < r; i++){
        xor_add(data, keys[i << 1]);
        nonlinear_lajer(data);
        add_xor(data, keys[(i << 1) + 1]);
        pht_layer(data);
    }
    xor_add(data, keys[r << 1]);
    std::string out = "";
    for(uint8_t i = 0; i < 8; i++){
        out += data[i];
    }
    return out;
}

std::string SAFERK64::decrypt(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }

    if (DATA.size() != 8){
        throw std::runtime_error("Error: Data must be 64 bits in length.");
    }

    std::vector <uint8_t> data;
    for(uint8_t i = 0; i < 8; i++){
        data.push_back(DATA[i]);
    }
    xor_sub(data, keys[r << 1]);
    for(int8_t i = r - 1; i > -1; i--){
        inv_pht_layer(data);
        sub_xor(data, keys[(i << 1) + 1]);
        inv_nonlinear_lajer(data);
        xor_sub(data, keys[i << 1]);
    }
    std::string out = "";
    for(uint8_t i = 0; i < 8; i++){
        out += data[i];
    }
    return out;
}

unsigned int SAFERK64::blocksize() const {
    return 128;
}
