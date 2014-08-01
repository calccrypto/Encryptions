#include "AES.h"

void AES::shiftrow(std::vector <uint32_t> & data){
    std::vector <uint32_t> temp;
    for(uint8_t x = 0; x < 4; x++){
        temp.push_back(0);
        for(uint8_t y = 0; y < 4; y++){
            temp[x] += ((data[y] >> ((3 - x) << 3)) & 255) << ((3 - y) << 3);
        }
    }
    data = temp;

    for(uint8_t x = 0; x < 4; x++){
        data[x] = ROL(data[x], x << 3, 32);
    }

    temp.clear();
    for(uint8_t x = 0; x < 4; x++){
        temp.push_back(0);
        for(uint8_t y = 0; y < 4; y++){
            temp[x] += ((data[y] >> ((3 - x) << 3)) & 255) << ((3 - y) << 3);
        }
    }
    data = temp;
}

void AES::invshiftrow(std::vector <uint32_t> & data){
    std::vector <uint32_t> temp;
    for(uint8_t x = 0; x < 4; x++){
        temp.push_back(0);
        for(uint8_t y = 0; y < 4; y++){
            temp[x] += ((data[y] >> ((3 - x) << 3)) & 255) << ((3 - y) << 3);
        }
    }
    data = temp;

    for(uint8_t x = 0; x < 4; x++){
        data[x] = ROR(data[x], x << 3, 32);
    }

    temp.clear();
    for(uint8_t x = 0; x < 4; x++){
        temp.push_back(0);
        for(uint8_t y = 0; y < 4; y++){
            temp[x] += ((data[y] >> ((3 - x) << 3)) & 255) << ((3 - y) << 3);
        }
    }
    data = temp;
}

/*
uint8_t AES::GF(uint8_t a, uint8_t b){
    //rijndael Finite Field multiplication
    uint8_t prim = 0x11b;
    std::string A = makebin(a, 8);
    std::string B = makebin(b, 8);
    uint8_t c = 0;
    for (int i = 7; i >= 0; i--){
        std::string temp = "";
        for (int j = 7; i >= 0; i--){
            temp = str(atoi(a[j]) * atoi(b[i])) + temp;
        }
        c ^= int(temp + "0" * (7-i), 2);
    }
    for i in xrange(15, 8, -1){
        if makebin(c, i)[0] == "1":{
            c ^= prim << (i-9);
        }
    }
    return c
}
*/

uint8_t AES::GF(uint8_t a, uint8_t b){
    /*Rijndael Finite Field multiplication
    Fast but Vulnerable to Timing Attacks
    From Wikipedia*/
    uint8_t prim = 0x1b;
    uint8_t p = 0, i = 0;
    while ((i < 8) && (a != 0) and (b != 0)){
        if (b & 1){
            p ^= a;
        }
        uint8_t hi = a & 0x80;
        a = (a << 1) & 255;
        if (hi){
            a ^= prim;
        }
        b >>= 1;
        i += 1;
    }
    return p;
}

void AES::mixcolumns(std::vector <uint32_t> & data){
    std::vector <uint32_t> temp;
    for(uint8_t i = 0; i < 4; i++){
        temp.push_back( ((GF(2, (data[i] >> 24) & 255) ^ GF(3, (data[i] >> 16) & 255) ^ ((data[i] >> 8) & 255) ^ (data[i] & 255)) << 24) +
                        ((GF(2, (data[i] >> 16) & 255) ^ GF(3, (data[i] >> 8) & 255) ^ (data[i] & 255) ^ ((data[i] >> 24) & 255)) << 16) +
                        ((GF(2, (data[i] >> 8) & 255) ^ GF(3, data[i] & 255) ^ ((data[i] >> 24) & 255) ^ ((data[i] >> 16) & 255)) << 8 ) +
                        ((GF(2, data[i] & 255) ^ GF(3, (data[i] >> 24) & 255) ^ ((data[i] >> 16) & 255) ^ ((data[i] >> 8) & 255))));
    }
    data = temp;
}

void AES::invmixcolumns(std::vector <uint32_t> & data){
    std::vector <uint32_t> temp;
    for(uint8_t i = 0; i < 4; i++){
        temp.push_back( ((GF(14, (data[i] >> 24) & 255) ^ GF(9, (data[i] & 255)) ^ GF(13, (data[i] >> 8) & 255) ^ GF(11, (data[i] >> 16) & 255)) << 24) +
                        ((GF(14, (data[i] >> 16) & 255) ^ GF(9, (data[i] >> 24) & 255) ^ GF(13, (data[i] & 255)) ^ GF(11, (data[i] >> 8) & 255)) << 16) +
                        ((GF(14, (data[i] >> 8) & 255) ^ GF(9, (data[i] >> 16) & 255) ^ GF(13, (data[i] >> 24) & 255) ^ GF(11, (data[i] & 255))) << 8 ) +
                        ((GF(14, (data[i] & 255)) ^ GF(9, (data[i] >> 8) & 255) ^ GF(13, (data[i] >> 16) & 255) ^ GF(11, (data[i] >> 24) & 255))));
    }
    data = temp;
}

std::string AES::OUT(std::vector <uint32_t> & data){
    std::string out = "";
    for(uint8_t x = 0; x < 4; x++){
        out += makehex(data[x], 8);
    }
    return unhexlify(out);
}

AES::AES() :
    SymAlg(),
    b(0), rounds(0), columns(0),
    keys()
{
}

AES::AES(const std::string & KEY) :
    AES()
{
    setkey(KEY);
}

void AES::setkey(const std::string & KEY){
    if (keyset){
        throw std::runtime_error("Error: Key has already been set.");
    }

    uint8_t n = KEY.size();
    if ((n != 16) && (n != 24) && (n != 32)){
        throw std::runtime_error("Error: Key size does not fit defined sizes.");
    }

    rounds = n / 4 + 6;
    columns = rounds - 6;
    b = (rounds + 1) << 4;
    n >>= 2;

    std::vector <uint32_t> key;
    for(uint8_t x = 0; x < columns; x++){
        key.push_back(static_cast <uint32_t> (toint(KEY.substr(x << 2, 4), 256)));
    }

    uint8_t i = 1;
    while ((key.size() << 2) < b){
        uint32_t t = ROL(key[key.size() - 1], 8, 32);
        uint32_t s = 0;

        for(uint8_t j = 0; j < 4; j++){
            s += AES_Subbytes[static_cast <uint8_t> (t >> (j << 3))] << (j << 3);
        }

        t = s ^ key[key.size() - n];
        t ^= ((1 << (i++ - 1)) % 229) << 24;
        key.push_back(t);

        for(uint8_t j = 0; j < 3; j++){
            key.push_back(key[key.size() - 1]^ key[key.size() - n]);
        }

        if (n == 8){
            s = 0;
            for(uint8_t j = 0; j < 4; j++){
                s += AES_Subbytes[static_cast <uint8_t> (key[key.size() - 1] >> (j << 3))] << (j << 3);
            }
            key.push_back(s ^ key[key.size() - n]);
        }

        for(uint8_t j = 0; j < 0 * (n == 4) + 2 * (n == 6) + 3 * (n == 8); j++){
            key.push_back(key[key.size() - 1] ^ key[key.size() - n]);
        }
    }

    for(uint8_t j = 0; j < (b >> 4); j++){
        std::vector <uint32_t> temp;
        for(uint8_t k = 0; k < 4; k++){
            temp.push_back(key[(j << 2) + k]);
        }
        keys.push_back(temp);
    }
    keyset = true;
}

std::string AES::encrypt(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }

    if (DATA.size() != 16){
        throw std::runtime_error("Error: Data must be 128 bits long.");
    }

    std::vector <uint32_t> data;
    for(uint8_t x = 0; x < 4; x++){
        std::string d = "";
        for(uint8_t y = 0; y < 4; y++){
            d += DATA[(x << 2) + y];
        }
        data.push_back(static_cast <uint32_t> (toint(d, 256)));
    }

    for(uint8_t x = 0; x < 4; x++){
        data[x] ^= keys[0][x];
    }

    for(uint8_t r = 1; r < rounds; r++){
        for(uint8_t x = 0; x < 4; x++){
            data[x] = (AES_Subbytes[data[x] >> 24] << 24) + (AES_Subbytes[(data[x] >> 16) & 255] << 16) + (AES_Subbytes[(data[x] >> 8) & 255] << 8) + AES_Subbytes[data[x] & 255];
        }
        shiftrow(data);
        mixcolumns(data);
        for(uint8_t x = 0; x < 4; x++){
            data[x] ^= keys[r][x];
        }
    }

    for(uint8_t x = 0; x < 4; x++){
        data[x] = (AES_Subbytes[data[x] >> 24] << 24) + (AES_Subbytes[(data[x] >> 16) & 255] << 16) + (AES_Subbytes[(data[x] >> 8) & 255] << 8) + AES_Subbytes[data[x] & 255];
    }

    shiftrow(data);

    for(uint8_t x = 0; x < 4; x++){
        data[x] ^= keys[rounds][x];
    }
    return OUT(data);
}

std::string AES::decrypt(const std::string & DATA){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }

    if (DATA.size() != 16){
        throw std::runtime_error("Error: Data must be 128 bits long.");
    }

    std::reverse(keys.begin(), keys.end());
    std::vector <uint32_t> data;
    for(uint8_t x = 0; x < 4; x++){
        std::string d = "";
        for(uint8_t y = 0; y < 4; y++){
            d += DATA[(x << 2) + y];
        }
        data.push_back(static_cast <uint32_t> (toint(d, 256)));
    }

    for(uint8_t x = 0; x < 4; x++){
        data[x] ^= keys[0][x];
    }

    for(uint8_t r = 1; r < rounds; r++){
        invshiftrow(data);
        for(uint8_t x = 0; x < 4; x++){
            data[x] = (AES_Inv_Subbytes[data[x] >> 24] << 24) + (AES_Inv_Subbytes[(data[x] >> 16) & 255] << 16) + (AES_Inv_Subbytes[(data[x] >> 8) & 255] << 8) + AES_Inv_Subbytes[data[x] & 255];
        }
        for(uint8_t x = 0; x < 4; x++){
            data[x] ^= keys[r][x];
        }
        invmixcolumns(data);
    }

    invshiftrow(data);

    for(uint8_t x = 0; x < 4; x++){
        data[x] = (AES_Inv_Subbytes[data[x] >> 24] << 24) + (AES_Inv_Subbytes[(data[x] >> 16) & 255] << 16) + (AES_Inv_Subbytes[(data[x] >> 8) & 255] << 8) + AES_Inv_Subbytes[data[x] & 255];
    }

    for(uint8_t x = 0; x < 4; x++){
        data[x] ^= keys[rounds][x];
    }

    std::reverse(keys.begin(), keys.end());
    return OUT(data);
}

unsigned int AES::blocksize() const{
    return 128;
}
/*
// More readable/easier to understand version of AES
// slightly less efficient though

void AES::shiftrow(std::vector <std::vector <uint8_t> > & data){
    std::vector <std::vector <uint8_t> > temp;
    for(uint8_t x = 0; x < 4; x++){
        std::vector <uint8_t> row;
        for(uint8_t y = 0; y < 4; y++){
            row.push_back(data[y][x]);
        }
        temp.push_back(row);
    }
    for(uint8_t x = 0; x < 4; x++){
        std::vector <uint8_t> t = temp[x];
        uint8_t count = 0;
        for(uint8_t y = x; y < 4; y++){
            temp[x][count] = t[y];
            count++;
        }
        for(uint8_t y = 0; y < x; y++){
            temp[x][count] = t[y];
            count++;
        }
    }
    for(uint8_t x = 0; x < 4; x++)
        for(uint8_t y = 0; y < 4; y++)
            data[x][y] = temp[y][x];
}

void AES::invshiftrow(std::vector <std::vector <uint8_t> > & data){
    std::vector <std::vector <uint8_t> > temp;
    for(uint8_t x = 0; x < 4; x++){
        std::vector <uint8_t> row;
        for(uint8_t y = 0; y < 4; y++){
            row.push_back(data[y][x]);
        }
        temp.push_back(row);
    }
    for(uint8_t x = 0; x < 4; x++){
        std::vector <uint8_t> t = temp[x];
        uint8_t count = 0;
        for(uint8_t y = (4 - x) & 3; y < 4; y++){
            temp[x][count] = t[y];
            count++;
        }
        for(uint8_t y = 0; y < (4 - x) & 3; y++){
            temp[x][count] = t[y];
            count++;
        }
    }
    for(uint8_t x = 0; x < 4; x++){
        for(uint8_t y = 0; y < 4; y++){
            data[x][y] = temp[y][x];
        }
    }
}

//uint8_t AES::GF(uint8_t a, uint8_t b){
//    //rijndael Finite Field multiplication
//    uint8_t prim = 0x11b;
//    std::string A = makebin(a, 8);
//    std::string B = makebin(b, 8);
//    uint8_t c = 0;
//    for (uint8_t i = 7; i >= 0; i--){
//        std::string temp = "";
//        for (uint8_t j = 7; i >= 0; i--){
//            temp = str(atoi(a[j]) * atoi(b[i])) + temp;
//        }
//        c ^= int(temp + "0" * (7-i), 2);
//    }
//    for (uint8_t i = 15; i > 7; i--){
//        if (makebin(c, i)[0] == "1"){
//            c ^= prim << (i-9);
//        }
//    }
//    return c
//}

uint8_t AES::GF(uint8_t a, uint8_t b){
//    Rijndael Finite Field multiplication
//    Fast but Vulnerable to Timing Attacks
//    From Wikipedia
    uint8_t prim = 0x1b;
    uint8_t p = 0, i = 0;
    while ((i < 8) && (a != 0) and (b != 0)){
        if (b & 1){
            p ^= a;
        }
        uint8_t hi = a & 0x80;
        a = (a << 1) & 255;
        if ((char) makebin(hi)[0] == '1'){
            a ^= prim;
        }
        b >>= 1;
        i += 1;
    }
    return p;
}

void AES::mixcolumns(std::vector <std::vector <uint8_t> > & data){
    std::vector <std::vector <uint8_t> > temp;
    for(uint8_t i = 0; i < 4; i++){
        std::vector <uint8_t> a;
        a.push_back(GF(2, data[i][0]) ^ GF(3, data[i][1]) ^ data[i][2] ^ data[i][3]);
        a.push_back(GF(2, data[i][1]) ^ GF(3, data[i][2]) ^ data[i][3] ^ data[i][0]);
        a.push_back(GF(2, data[i][2]) ^ GF(3, data[i][3]) ^ data[i][0] ^ data[i][1]);
        a.push_back(GF(2, data[i][3]) ^ GF(3, data[i][0]) ^ data[i][1] ^ data[i][2]);
        temp.push_back(a);
    }
    data = temp;
}

void AES::invmixcolumns(std::vector <std::vector <uint8_t> > & data){
    std::vector <std::vector <uint8_t> > temp;
    for(uint8_t i = 0; i < 4; i++){
        std::vector <uint8_t> a;
        a.push_back(GF(14, data[i][0]) ^ GF(9, data[i][3]) ^ GF(13, data[i][2]) ^ GF(11, data[i][1]));
        a.push_back(GF(14, data[i][1]) ^ GF(9, data[i][0]) ^ GF(13, data[i][3]) ^ GF(11, data[i][2]));
        a.push_back(GF(14, data[i][2]) ^ GF(9, data[i][1]) ^ GF(13, data[i][0]) ^ GF(11, data[i][3]));
        a.push_back(GF(14, data[i][3]) ^ GF(9, data[i][2]) ^ GF(13, data[i][1]) ^ GF(11, data[i][0]));
        temp.push_back(a);
    }
    data = temp;
}

std::string AES::OUT(std::vector <std::vector <uint8_t> > & data){
    std::string out = "";
    for(uint8_t x = 0; x < 4; x++){
        for(uint8_t y = 0; y < 4; y++){
            out += data[x][y];
        }
    }
    return out;
}

AES::AES(){
    keyset = false;
}

AES::AES(const std::string & KEY){
    keyset = false;
    setkey(KEY);
}

void setkey(std::string KEY){
    if (keyset){
        error(2);
    }
    for(uint8_t x = 0; x < 256; x++){
        AES_Subbytes[x] = s[x];
        AES_Inv_Subbytes[x] = is[x];
    }
    if (KEY.size() > 32){
        KEY = KEY.substr(0, 32);
    }
    while ((KEY.size() != 16) & (KEY.size() != 24) & (KEY.size() != 32)){// not part of standard
        KEY += zero;
    }
    unsigned uint8_t n = KEY.size();
    rounds = n / 4 + 6;
    columns = rounds - 6;
    b = (rounds + 1) << 4;
    n >>= 2;
    std::vector <std::vector <uint8_t> > key;
    for(uint8_t i = 0; i < columns; i++){
        std::vector <uint8_t> temp;
        for(uint8_t j = 0; j < 4; j++){
            temp.push_back(KEY[4 * i + j]);
        }
        key.push_back(temp);
    }
    uint8_t i = 1;
    while ((key.size() << 2) < b){
        std::vector <uint8_t> t;
        t.push_back(key[key.size() - 1][1]);
        t.push_back(key[key.size() - 1][2]);
        t.push_back(key[key.size() - 1][3]);
        t.push_back(key[key.size() - 1][0]);
        for(uint8_t j = 0; j < 4; j++){
            t[j] = AES_Subbytes[t[j]] ^ key[key.size() - n][j];
        }
        t[0] ^= (1 << (i++ - 1)) % 229;
        key.push_back(t);
        for(uint8_t j = 0; j < 3; j++){
            std::vector <uint8_t> next;
            for(uint8_t k = 0; k < 4; k++){
                next.push_back(key[key.size() - 1][k]^ key[key.size() - n][k]);
            }
            key.push_back(next);
        }
        if (n == 8){
            t = key[key.size() - 1];
            for(uint8_t j = 0; j < 4; j++){
                t[j] = AES_Subbytes[t[j]] ^ key[key.size() - n][j];
            }
            key.push_back(t);
        }
        for(uint8_t j = 0; j < 0 * (n == 4) + 2 * (n == 6) + 3 * (n == 8); j++){
            t.clear();
            for(uint8_t k = 0; k < 4; k++){
                t.push_back(key[key.size() - 1][k] ^ key[key.size() - n][k]);
            }
            key.push_back(t);
        }
    }
    for(uint8_t j = 0; j < (b >> 4); j++){
        std::vector <std::vector <uint8_t> > temp;
        for(uint8_t k = 0; k < 4; k++){
            temp.push_back(key[4 * j + k]);
        }
        keys.push_back(temp);
    }
    keyset = true;
}

std::string AES::encrypt(const std::string & DATA){
    if (!keyset)
        error(1);
    std::vector <std::vector <uint8_t> > data;
    for(uint8_t x = 0; x < 4; x++){
        std::vector <uint8_t> temp;
        for(uint8_t y = 0; y < 4; y++){
            temp.push_back(DATA[x << 2 + y]);
        }
        data.push_back(temp);
    }
    for(uint8_t x = 0; x < 4; x++){
        for(uint8_t y = 0; y < 4; y++){
            data[x][y] ^= keys[0][x][y];
        }
    }
    for(uint8_t r = 1; r < rounds; r++){
        for(uint8_t x = 0; x < 4; x++){
            for(uint8_t y = 0; y < 4; y++){
                data[x][y] = AES_Subbytes[data[x][y]];
            }
        }
        shiftrow(data);
        mixcolumns(data);
        for(uint8_t x = 0; x < 4; x++)
            for(uint8_t y = 0; y < 4; y++)
                data[x][y] ^= keys[r][x][y];
    }
    for(uint8_t x = 0; x < 4; x++){
        for(uint8_t y = 0; y < 4; y++){
            data[x][y] = AES_Subbytes[data[x][y]];
        }
    }
    shiftrow(data);
    for(uint8_t x = 0; x < 4; x++){
        for(uint8_t y = 0; y < 4; y++){
            data[x][y] ^= keys[rounds][x][y];
        }
    }
    return OUT(data);
}

std::string AES::decrypt(const std::string & DATA){
    if (!keyset){
        error(1);
    }
    std::reverse(keys.begin(), keys.end());
    std::vector <std::vector <uint8_t> > data;
    for(uint8_t x = 0; x < 4; x++){
        std::vector <uint8_t> temp;
        for(uint8_t y = 0; y < 4; y++){
            temp.push_back(DATA[x << 2 + y]);
        }
        data.push_back(temp);
    }
    for(uint8_t x = 0; x < 4; x++){
        for(uint8_t y = 0; y < 4; y++){
            data[x][y] ^= keys[0][x][y];
        }
    }
    for(uint8_t r = 1; r < rounds; r++){
        invshiftrow(data);
        for(uint8_t x = 0; x < 4; x++){
            for(uint8_t y = 0; y < 4; y++){
                data[x][y] = AES_Inv_Subbytes[data[x][y]];
            }
        }
        for(uint8_t x = 0; x < 4; x++){
            for(uint8_t y = 0; y < 4; y++){
                data[x][y] ^= keys[r][x][y];
            }
        }
        invmixcolumns(data);
    }
    invshiftrow(data);
    for(uint8_t x = 0; x < 4; x++){
        for(uint8_t y = 0; y < 4; y++){
            data[x][y] = AES_Inv_Subbytes[data[x][y]];
        }
    }
    for(uint8_t x = 0; x < 4; x++){
        for(uint8_t y = 0; y < 4; y++){
            data[x][y] ^= keys[rounds][x][y];
        }
    }
    std::reverse(keys.begin(), keys.end());
    return OUT(data);
}

unsigned int AES::blocksize(){
    return 128;
}
*/
