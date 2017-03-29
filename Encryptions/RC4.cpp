#include "RC4.h"

void RC4::ksa(const std::string & k){
    // Original SBox
    for(uint16_t i = 0; i < 256; i++){
        s_e[i] = i;
    }

    uint8_t j = 0;
    for(uint16_t i = 0; i < 256; i++){
        j = (j + s_e[i] + k[i % k.size()]);
        std::swap(s_e[i], s_e[j]);
    }

    for(uint16_t i = 0; i < 256; i++){
        s_d[i] = s_e[i];
    }
}

uint8_t RC4::prga(const char mode){
    if (mode == 'e'){
        i_e++;
        j_e += s_e[i_e];
        std::swap(s_e[j_e], s_e[i_e]);
        return s_e[(s_e[i_e] + s_e[j_e]) & 255];
    }
    else if (mode == 'd'){
        i_d++;
        j_d += s_d[i_d];
        std::swap(s_d[j_d], s_d[i_d]);
        return s_d[(s_d[i_d] + s_d[j_d]) & 255];
    }
    else{
        throw std::runtime_error("Error: Unknown mode used in prga.");
    }
    return 0; // get rid of compiler warnings
}

RC4::RC4()
    : SymAlg(),
      s_e(), i_e(0), j_e(0), s_d(), i_d(0), j_d(0)
{}

RC4::RC4(const std::string & KEY)
    : RC4()
{
    setkey(KEY);
}

void RC4::setkey(const std::string & KEY){
    if (keyset){
        throw std::runtime_error("Error: Key has already been set.");
    }

    ksa(KEY);
    keyset = true;
}

std::string RC4::encrypt(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }

    std::string out = "";
    for(uint8_t x = 0; x < DATA.size(); x++){
        out += static_cast <char> (static_cast <uint8_t> (DATA[x]) ^ prga('e'));
    }
    return out;
}

std::string RC4::decrypt(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }

    std::string out = "";
    for(uint8_t x = 0; x < DATA.size(); x++){
        out += static_cast  <char> (static_cast <uint8_t> (DATA[x]) ^ prga('d'));
    }
    return out;
}

unsigned int RC4::blocksize() const {
    return 64;
}
