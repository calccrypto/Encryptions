#include "CTR.h"

CTR::CTR(SymAlg * instance, const std::string & iv)
  : algo(instance) {
    blocksize = algo -> blocksize() >> 3;
    const_IV = iv;
    if (const_IV == ""){
        const_IV = std::string(blocksize, 0);
    }
}

std::string CTR::encrypt(const std::string & data){
    std::string temp = pkcs5(data, blocksize);
    std::string out = "";
    std::string IV = const_IV;
    uint32_t x = 0;
    while (x < temp.size()){
        out += unhexlify(makehex(integer(hexlify(algo -> encrypt(IV)), 16) ^ integer(hexlify(temp.substr(0, blocksize)), 16), blocksize << 1));
        x += blocksize;
        IV = unhexlify(makehex(integer(hexlify(IV), 16) + 1, blocksize << 1));
    }
    return out;
}

std::string CTR::decrypt(const std::string & data){
    std::string out = "";
    std::string IV = const_IV;
    uint32_t x = 0;
    while (x < data.size()){
        out += unhexlify(makehex(integer(hexlify(algo -> encrypt(IV)), 16) ^ integer(hexlify(data.substr(x, blocksize)), 16), blocksize << 1));
        x += blocksize;
        IV = unhexlify(makehex(integer(hexlify(IV), 16) + 1, blocksize << 1));
    }
    return remove_padding(out);
}
