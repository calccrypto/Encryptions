#include "./DESX.h"

DESX::DESX(){
    keyset = false;
}

DESX::DESX(std::string & KEY, std::string & KEY2){
    if (keyset){
        error(2);
    }
    std::string newkey = unhexlify(makehex(toint(KEY, 256) ^ toint(KEY2, 256), 16));
    des.setkey(newkey);
    keyset = true;
}

std::string DESX::encrypt(std::string & DATA, std::string & KEY3){
    if (!keyset){
        error(1);
    }
    return unhexlify(makehex(toint(des.encrypt(DATA), 256) ^ toint(KEY3, 256), 16));
}

std::string DESX::decrypt(std::string & DATA, std::string & KEY3){
    if (!keyset){
        error(1);
    }
    return unhexlify(makehex(toint(des.decrypt(DATA), 256) ^ toint(KEY3, 256), 16));
}

unsigned int DESX::blocksize(){
    return 64;
}

