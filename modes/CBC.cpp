#include "CBC.h"

CBC::CBC(SymAlg * instance, const std::string & iv)
    : algo(instance)
{
    blocksize = algo -> blocksize() >> 3;
    const_IV = iv;
    if (const_IV == ""){
        const_IV = std::string(blocksize, 0);
    }
}

std::string CBC::encrypt(const std::string & data){
    const std::string temp = pkcs5(data, blocksize);
    std::string out = "";
    std::string IV = const_IV;
    for(std::string::size_type x = 0; x < temp.size(); x += blocksize){
        IV = algo -> encrypt(xor_strings(temp.substr(x, blocksize), IV));
        out += IV;
    }
    return out;
}

std::string CBC::decrypt(const std::string & data){
    std::string out = "";
    std::string IV = const_IV;
    for(std::string::size_type x = 0; x < data.size(); x += blocksize){
        out += xor_strings(algo -> decrypt(data.substr(x, blocksize)), IV);
        IV = data.substr(x, blocksize);
    }
    return remove_pkcs5(out);
}
