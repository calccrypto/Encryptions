#include "DES.h"

std::string DES::run(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }

    if (DATA.size() != 8){
        throw std::runtime_error("Error: Data must be 64 bits in length.");
    }

    std::string data = "", temp = "";
    for(uint8_t x = 0; x < 8; x++){
        data += makebin(static_cast <uint8_t> (DATA[x]), 8);
    }
    // IP
    for(uint8_t x = 0; x < 64; x++){
        temp += data[DES_IP[x] - 1];
    }
    data = temp;
    for(uint8_t x = 0; x < 16; x++){
        // split left and right and duplicate right
        std::string left = data.substr(0, 32);
        std::string right = data.substr(32, 32);
        std::string old_right = right;

        // expand right side
        uint64_t t = 0;
        temp = "";
        for(uint8_t y = 0; y < 48; y++){
            temp += right[DES_EX[y] - 1];
        }
        t = toint(temp, 2);

        // expanded_right xor key
        right = makebin(t ^ keys[x], 48);

        // split right into 8 parts
        std::string RIGHT[8];
        for(uint8_t y = 0; y < 8; y++){
            RIGHT[y] = right.substr(6 * y, 6);
        }
        // use sboxes
        temp = "";
        for(uint8_t y = 0; y < 8; y++){
            std::string s = "";
            s += RIGHT[y][0];
            s += RIGHT[y][5];
            temp += makebin(DES_S_BOX[y][toint(s, 2)][toint(RIGHT[y].substr(1, 4), 2)], 4);
        }

        // permutate
        right = "";
        for(uint8_t y = 0; y < 32; y++){
            right += temp[DES_P[y]-1];
        }

        // right xor left and combine with old right
        data = old_right + makebin(toint(left, 2) ^ toint(right, 2), 32);
    }
    // reverse last switch
    data = data.substr(32, 32) + data.substr(0, 32);

    // IP^-1
    uint64_t out = 0;
    for(uint8_t x = 0; x < 64; x++){
        out += static_cast <uint64_t> (data[DES_INVIP[x] - 1] == '1') << (63 - x);
    }
    return unhexlify(makehex(out, 16));
}

DES::DES() :
    SymAlg(),
    keys()
{
}

DES::DES(const std::string & KEY) :
    DES()
{
    setkey(KEY);
}

void DES::setkey(const std::string & KEY){
    if (keyset){
        throw std::runtime_error("Error: Key has already been set.");
    }
    if (KEY.size() != 8){
        throw std::runtime_error("Error: Key must be 64 bits long.");
    }

    std::string key = "";
    for(int x = 0; x < 8; x++){
        key += makebin(static_cast <uint8_t> (KEY[x]), 8);
    }

    std::string left = "", right = "";
    for (uint8_t x = 0; x < 28; x++){
        left += key[DES_PC1_l[x] - 1];
        right += key[DES_PC1_r[x] - 1];
    }

    for(uint8_t x = 0; x < 16; x++){
        left = (left + left).substr(DES_rot[x], 28);
        right = (right + right).substr(DES_rot[x], 28);
        std::string k = "";
        for(uint8_t y = 0; y < 48; y++)
            k += (left + right)[DES_PC2[y] - 1];
        keys[x] = toint(k, 2);
    }

    keyset = true;
}

std::string DES::encrypt(const std::string & DATA){
    return run(DATA);
}

std::string DES::decrypt(const std::string & DATA){
    std::reverse(keys, keys + 16);
    std::string out = run(DATA);
    std::reverse(keys, keys + 16);
    return out;
}

unsigned int DES::blocksize() const{
    return 64;
}
