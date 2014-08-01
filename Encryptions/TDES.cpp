#include "TDES.h"

std::string TDES::run(const std::string & data, const std::string & key, const bool & mode){
    if (!keyset){
        throw std::runtime_error("Error: Key has not been set.");
    }

    if (data.size() != 8){
        throw std::runtime_error("Error: Data must be 64 bits in length.");
    }

    if (!mode){
        return DES(key).encrypt(data);
    }
    return DES(key).decrypt(data);
}

TDES::TDES() :
    SymAlg(),
    k1(), k2(), k3(),
    m1(), m2(), m3()
{
}

TDES::TDES(const std::string & key1, const std::string & mode1, const std::string & key2, const std::string & mode2, const std::string & key3, const std::string & mode3) :
    TDES()
{
    setkey(key1, mode1, key2, mode2, key3, mode3);
}

void TDES::setkey(const std::string & key1, const std::string & mode1, const std::string & key2, const std::string & mode2, const std::string & key3, const std::string & mode3){
    if (keyset){
        throw std::runtime_error("Error: Key has already been set.");
    }

    if (key1.size() != 8){
        throw std::runtime_error("Error: Key must be 64 bits in length.");
    }

    if (key2.size() != 8){
        throw std::runtime_error("Error: Key must be 64 bits in length.");
    }

    if (key3.size() != 8){
        throw std::runtime_error("Error: Key must be 64 bits in length.");
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
    return run(run(run(DATA, k1, !m1), k2, !m2), k3, !m3);
}

unsigned int TDES::blocksize() const{
    return 64;
}
