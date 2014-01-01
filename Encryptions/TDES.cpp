#include "TDES.h"

std::string TDES::run(const std::string & data, const std::string & key, const bool & mode){
    if (!keyset){
        std::cerr << "Error: Key has not been set." << std::endl;
        throw 1;
    }

    if (data.size() != 8){
        std::cerr << "Error: Data must be 64 bits in length." << std::endl;
        throw 1;
    }

    if (!mode){
        return DES(key).encrypt(data);
    }
    return DES(key).decrypt(data);
}

TDES::TDES(){
    keyset = false;
}

TDES::TDES(const std::string & key1, const std::string & mode1, const std::string & key2, const std::string & mode2, const std::string & key3, const std::string & mode3){
    keyset = false;
    setkey(key1, mode1, key2, mode2, key3, mode3);
}

void TDES::setkey(const std::string & key1, const std::string & mode1, const std::string & key2, const std::string & mode2, const std::string & key3, const std::string & mode3){
    if (keyset){
        std::cerr << "Error: Key has already been set." << std::endl;
        throw 1;
    }

    if (key1.size() != 8){
        std::cerr << "Error: Key must be 64 bits in length." << std::endl;
        throw 1;
    }

    if (key2.size() != 8){
        std::cerr << "Error: Key must be 64 bits in length." << std::endl;
        throw 1;
    }

    if (key3.size() != 8){
        std::cerr << "Error: Key must be 64 bits in length." << std::endl;
        throw 1;
    }

    k1 = key1;
    k2 = key2;
    k3 = key3;
    m1 = (mode1 == "d");
    m2 = (mode2 == "d");
    m3 = (mode3 == "d");

    keyset = true;
}

std::string TDES::encrypt(const std::string & DATA){
    return run(run(run(DATA, k1, m1), k2, m2), k3, m3);
}

std::string TDES::decrypt(const std::string & DATA){
    return run(run(run(DATA, k1, ~m1), k2, ~m2), k3, ~m3);
}

unsigned int TDES::blocksize(){
    return 64;
}
