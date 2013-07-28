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

RC4::RC4(std::string KEY){
    i_e = j_e = i_d = j_d = 0;
    keyset = false;
    setkey(KEY);
}

void RC4::setkey(std::string KEY){
    for(unsigned int x = 0; x < KEY.size(); x++){
        key.push_back((uint8_t) KEY[x]);
    }
    keyset = true;
}

std::string RC4::encrypt(std::string DATA){
    if (!keyset){
        error(1);
    }
    ksa(key);
    std::string out = "";
    for(uint8_t x = 0; x < DATA.size(); x++){
        out += (char) ((uint8_t) DATA[x] ^ prga(i_e, j_e));
    }
    return out;
}

std::string RC4::decrypt(std::string DATA){
    if (!keyset){
        error(1);
    }
    ksa(key);
    std::string out = "";
    for(uint8_t x = 0; x < DATA.size(); x++){
        out += (char) ((uint8_t) DATA[x] ^ prga(i_d, j_d));
    }
    return out;
}

unsigned int RC4::blocksize(){
    return 8;
}
