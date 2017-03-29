#include "OFB.h"

OFB::OFB(SymAlg * instance, const std::string & iv)
    : algo(instance)
{
    blocksize = algo -> blocksize() >> 3;
    const_IV = iv;
    if (const_IV == ""){
        const_IV = std::string(blocksize, 0);
    }
  }

std::string OFB::encrypt(const std::string & data){
    const std::string temp = pkcs5(data, blocksize);
    std::string out = "";
    std::string IV = const_IV;
    for(std::string::size_type x = 0; x < temp.size(); x += blocksize){
        IV = algo -> encrypt(IV);
        out += xor_strings(IV, temp.substr(x, blocksize));
    }
    return out;
}

std::string OFB::decrypt(const std::string & data){
    std::string out = "";
    std::string IV = const_IV;
    for(std::string::size_type x = 0; x < data.size(); x += blocksize){
        IV = algo -> encrypt(IV);
        out += xor_strings(IV, data.substr(x, blocksize));
    }
    return out;
}
