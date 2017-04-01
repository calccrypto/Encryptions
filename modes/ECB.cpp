#include "ECB.h"

ECB::ECB(SymAlg * instance, const std::string & iv)
    : algo(instance)
{
    blocksize = algo -> blocksize() >> 3;
}

std::string ECB::encrypt(const std::string & data){
    std::string temp = pkcs5(data, blocksize);
    std::string out = "";
    for(std::string::size_type x = 0; x < temp.size(); x += blocksize){
        out += algo -> encrypt(data.substr(x, blocksize));
    }
    return out;
}

std::string ECB::decrypt(const std::string & data){
    std::string out = "";
    for(std::string::size_type x = 0; x < data.size(); x += blocksize){
        out += algo -> decrypt(data.substr(x, blocksize));
    }
    return remove_pkcs5(out);
}
