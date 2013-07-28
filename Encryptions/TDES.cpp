#include "./TDES.h"

std::string TDES::run(std::string data, std::string & key, const bool & mode){
    if (!keyset){
        error(1);
    }
    if (!mode){
        return DES(key).encrypt(data);
    }
    return DES(key).decrypt(data);
}

TDES::TDES(){
    keyset = false;
}

TDES::TDES(std::string & key1, const std::string & mode1, std::string & key2, const std::string & mode2, std::string & key3, const std::string & mode3){
    keyset = false;
    setkey(key1, mode1, key2, mode2, key3, mode3);
}

void TDES::setkey(std::string & key1, const std::string & mode1, std::string & key2, const std::string & mode2, std::string & key3, const std::string & mode3){
    if (keyset){
        error(2);
    }
    k1 = key1;
    k2 = key2;
    k3 = key3;
    m1 = (mode1 == "d");
    m2 = (mode2 == "d");
    m3 = (mode3 == "d");

    keyset = true;
}

std::string TDES::encrypt(std::string DATA){
    return run(run(run(DATA, k1, m1), k2, m2), k3, m3);
}

std::string TDES::decrypt(std::string DATA){
    return run(run(run(DATA, k1, ~m1), k2, ~m2), k3, ~m3);
}

unsigned int TDES::blocksize(){
    return 64;
}
