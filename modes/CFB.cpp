#include "CFB.h"

CFB::CFB(SymAlg * instance, const std::string & iv)
    : algo(instance)
{
    blocksize = algo -> blocksize() >> 3;
    const_IV = iv;
    if (const_IV == ""){
        const_IV = std::string(blocksize, 0);
    }
}

std::string CFB::encrypt(const std::string & data){
    const std::string temp = pkcs5(data, blocksize);
    std::string out = "";
    std::string IV = const_IV;
    for(std::string::size_type x = 0; x < temp.size(); x += blocksize){
        IV = xor_strings(algo -> encrypt(IV), temp.substr(x, blocksize));
        out += IV;
    }
    return out;
}

std::string CFB::decrypt(const std::string & data){
    std::string out = "";
    std::string IV = const_IV;
    for(std::string::size_type x = 0; x < data.size(); x += blocksize){
        out += xor_strings(algo -> encrypt(IV), data.substr(x, blocksize));
        IV = data.substr(x, blocksize);
    }
    return remove_pkcs5(out);
}
