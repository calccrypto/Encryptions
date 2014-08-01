#include "IDEA.h"

// ////////////////////////
// Thanks for the help, Darkerline !
uint16_t IDEA::mult(uint32_t value1, uint32_t value2){
    //Special condition used by IDEA
    //where 0 is equivalent to 65536//
    if (value1 == 0 && value2 == 0){
        return 1;
    }
    if (value1 == 0){
        value1 = 65536;
    }
    if (value2 == 0){
        value2 = 65536;
    }
    value1 = (value1 * value2) % 65537;
    if (value1 == 65536){
        value1 = 0;
    }
    return static_cast <uint16_t> (value1);
}
// ///////////////////////

std::string IDEA::run(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set");
    }

    if (DATA.size() != 8){
        throw std::runtime_error("Error: Data must be 64 bits in length.");
    }

    uint16_t x1 = toint(DATA.substr(0, 2), 256);
    uint16_t x2 = toint(DATA.substr(2, 2), 256);
    uint16_t x3 = toint(DATA.substr(4, 2), 256);
    uint16_t x4 = toint(DATA.substr(6, 2), 256);
    for(uint8_t x = 0; x < 8; x++){
        uint16_t t1 = mult(x1, keys[x][0]);
        uint16_t t2 = static_cast <uint16_t> (x2 + keys[x][1]);
        uint16_t t3 = static_cast <uint16_t> (x3 + keys[x][2]);
        uint16_t t4 = mult(x4, keys[x][3]);
        uint16_t t5 = t1 ^ t3;
        uint16_t t6 = t2 ^ t4;
        uint16_t t7 = mult(t5, keys[x][4]);
        uint16_t t8 = static_cast <uint16_t> (t6 + t7);
        uint16_t t9 = mult(t8, keys[x][5]);
        uint16_t t10 = static_cast <uint16_t> (t7 + t9);
        x1 = t1 ^ t9;
        x2 = t3 ^ t9;
        x3 = t2 ^ t10;
        x4 = t4 ^ t10;
    }
    std::swap(x2, x3);
    x1 = mult(x1, keys[8][0]);
    x2 = static_cast <uint16_t> (x2 + keys[8][1]);
    x3 = static_cast <uint16_t> (x3 + keys[8][2]);
    x4 = mult(x4, keys[8][3]);
    return unhexlify(makehex(x1, 4) + makehex(x2, 4) + makehex(x3, 4) + makehex(x4, 4));
}

IDEA::IDEA() :
    SymAlg(),
    keys(),
    k()
{
}

IDEA::IDEA(const std::string & KEY) :
    IDEA()
{
    setkey(KEY);
}

void IDEA::setkey(const std::string & KEY){
    if (keyset){
        throw std::runtime_error("Error: Key has already been set.");
    }
    if (KEY.size() != 16){
        throw std::runtime_error("Error: Key must be 128 bits in length.");
    }

    std::string key = hexlify(KEY);
    std::vector <std::string> temp;
    for(uint8_t x = 0; x < 7; x++){

        for(int y  = 0; y < 8; y++){
            temp.push_back(key.substr(y << 2, 4));
        }

        for(uint8_t y = 0; y < 16; y++){
            key += makebin(toint(key.substr(y << 1 , 2), 16), 8);
        }

        key = key.substr(32, 128);
        key = key.substr(25, 103) + key.substr(0, 25);

        for(uint8_t y = 0; y < 16; y++){
            key += makehex(toint(key.substr(y << 3, 8), 2), 2);
        }

        key = key.substr(128, 32);
    }

    temp.erase(temp.begin() + 52, temp.end());

    for(uint8_t x = 0; x < temp.size(); x++){
        k.push_back(toint(temp[x], 16));
    }
    keyset = true;
}

std::string IDEA::encrypt(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }

    if (DATA.size() != 8){
        throw std::runtime_error("Error: Data must be 64 bits in length.");
    }

    keys.clear();
    std::vector <uint16_t> t;
    for(uint8_t x = 0; x < 8; x++){
        for(uint8_t y = 0; y < 6; y++){
            t.push_back(k[6 * x + y]);
        }
        keys.push_back(t);
        t.clear();
    }

    for(uint8_t x = 48; x < 52; x++){
        t.push_back(k[x]);
    }

    keys.push_back(t);
    t.clear();
    return run(DATA);
}

std::string IDEA::decrypt(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }

    if (DATA.size() != 8){
        throw std::runtime_error("Error: Data must be 64 bits in length.");
    }

    keys.clear();
    std::vector <uint16_t> t;
    for(uint8_t x = 0; x < 8; x++){
        k.push_back(invmod(static_cast <int> (65537), static_cast <int> (k[48 - 6 * x])));
        k.push_back(two_comp(k[50 - 6 * x]));
        k.push_back(two_comp(k[49 - 6 * x]));
        k.push_back(invmod(static_cast <int> (65537), static_cast <int> (k[51 - 6 * x])));
        k.push_back(k[46 - 6 * x]);
        k.push_back(k[47 - 6 * x]);
    }
    k.push_back(invmod(static_cast <int> (65537), static_cast <int> (k[0])));
    k.push_back(two_comp(k[1]));
    k.push_back(two_comp(k[2]));
    k.push_back(invmod(static_cast <int> (65537), static_cast <int> (k[3])));
    k.erase(k.begin(), k.begin() + 52);

    for(uint8_t x = 0; x < 8; x++){
        for(uint8_t y = 0; y < 6; y++){
            t.push_back(k[6 * x + y]);
        }
        keys.push_back(t);
        t.clear();
    }

    for(uint8_t x = 48; x < 52; x++){
        t.push_back(k[x]);
    }
    keys.push_back(t);
    t.clear();
    std::swap(keys[0][1], keys[0][2]);
    return run(DATA);
}

unsigned int IDEA::blocksize() const{
    return 64;
}
