#include "CTR.h"

std::string & CTR::increment_IV(std::string & IV){
    std::string::size_type i = IV.size();
    while ((i > 0) && ((uint8_t) IV[i - 1] == (uint8_t) 0xff)){
        IV[i - 1] = 0;
        i--;
    }

    if (i){
        IV[i - 1]++;
    }

    return IV;
}

CTR::CTR(SymAlg * instance, const std::string & iv)
    : algo(instance)
{
    blocksize = algo -> blocksize() >> 3;
    const_IV = iv;
    if (const_IV == ""){
        const_IV = std::string(blocksize, 0);
    }
}

std::string CTR::encrypt(const std::string & data){
    const std::string temp = pkcs5(data, blocksize);
    std::string out = "";
    std::string IV = const_IV;
    for(std::string::size_type x = 0; x < temp.size(); x += blocksize){
        out += xor_strings(algo -> encrypt(IV), temp.substr(x, blocksize));
        increment_IV(IV);
    }
    return out;
}

std::string CTR::decrypt(const std::string & data){
    std::string out = "";
    std::string IV = const_IV;
    for(std::string::size_type x = 0; x < data.size(); x += blocksize){
        out += xor_strings(algo -> encrypt(IV), data.substr(x, blocksize));
        increment_IV(IV);
    }
    return remove_pkcs5(out);
}
