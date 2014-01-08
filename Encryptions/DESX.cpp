#include "./DESX.h"

DESX::DESX(){
    keyset = false;
}

DESX::DESX(const std::string & KEY, const std::string & KEY2){
    if (keyset){
        throw std::runtime_error("Error: Key has already been set.");
    }
    std::string newkey = unhexlify(makehex(toint(KEY, 256) ^ toint(KEY2, 256), 16));
    des.setkey(newkey);
    keyset = true;
}

std::string DESX::encrypt(const std::string & DATA, const std::string & KEY3){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }
    return unhexlify(makehex(toint(des.encrypt(DATA), 256) ^ toint(KEY3, 256), 16));
}

std::string DESX::decrypt(const std::string & DATA, const std::string & KEY3){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }
    return unhexlify(makehex(toint(des.decrypt(DATA), 256) ^ toint(KEY3, 256), 16));
}

unsigned int DESX::blocksize(){
    return 64;
}
