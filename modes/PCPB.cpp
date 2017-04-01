#include "PCPB.h"

PCPB::PCPB(SymAlg * instance, const std::string & iv)
    : algo(instance)
{
    blocksize = algo -> blocksize() >> 3;
    const_IV = iv;
    if (const_IV == ""){
        const_IV = std::string(blocksize, 0);
    }
}

std::string PCPB::encrypt(const std::string & data){
    std::string temp = pkcs5(data, blocksize);
    std::string out = "";
    std::string IV = const_IV;
    for(std::string::size_type x = 0; x < temp.size(); x += blocksize){
        const std::string block = temp.substr(x, blocksize);
        out += algo -> encrypt(xor_strings(block, IV));
        IV = xor_strings(out.substr(out.size() - blocksize, blocksize), block);
    }
    return out;
}

std::string PCPB::decrypt(const std::string & data){
    std::string out = "";
    std::string IV = const_IV;
    for(std::string::size_type x = 0; x < data.size(); x += blocksize){
        const std::string block = data.substr(x, blocksize);
        out += xor_strings(algo -> decrypt(block), IV);
        IV = xor_strings(out.substr(out.size() - blocksize, blocksize), block);
    }
    return remove_pkcs5(out);
}
