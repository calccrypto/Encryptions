#include "./RC4.h"

void RC4::ksa(std::vector <uint8_t> & k){
    for(uint16_t x = 0; x < 256; x++){
        s[x] = x;
    }

    int y = 0;

    for(uint16_t x = 0; x < 256; x++){
        y = (y + s[x] + k[x % k.size()]) & 255;
        std::swap(s[x], s[y]);
    }
}

int RC4::prga(uint8_t & i, uint8_t & j){
    i++;
    j += s[i];
    std::swap(s[j], s[i]);
    return s[(s[i] + s[j]) & 255];
}

RC4::RC4():
    SymAlg(),
    key(0),
    s(), i_e(0), j_e(0), i_d(0), j_d(0)
{
}

RC4::RC4(const std::string & KEY):
    RC4()
{
    setkey(KEY);
}

void RC4::setkey(const std::string & KEY){
    if (keyset){
        throw std::runtime_error("Error: Key has already been set.");
    }

    for(unsigned int x = 0; x < KEY.size(); x++){
        key.push_back(static_cast <uint8_t> (KEY[x]));
    }
    keyset = true;
}

std::string RC4::encrypt(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }

    ksa(key);
    std::string out = "";
    for(uint8_t x = 0; x < DATA.size(); x++){
        out += static_cast <char> (static_cast <uint8_t> (DATA[x]) ^ prga(i_e, j_e));
    }
    return out;
}

std::string RC4::decrypt(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }

    ksa(key);
    std::string out = "";
    for(uint8_t x = 0; x < DATA.size(); x++){
        out += static_cast  <char> (static_cast <uint8_t> (DATA[x]) ^ prga(i_d, j_d));
    }
    return out;
}

unsigned int RC4::blocksize() const{
    return 64;
}
