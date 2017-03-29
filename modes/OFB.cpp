#include "OFB.h"
OFB::OFB(SymAlg * instance, const std::string & iv)
  : algo(instance) {
    blocksize = algo -> blocksize() >> 3;
    const_IV = iv;
    if (const_IV == ""){
        const_IV = std::string(blocksize, 0);
    }
  }

std::string OFB::encrypt(const std::string & data){
    std::string temp = pkcs5(data, blocksize);
    std::string out = "";
    std::string IV = const_IV;
    uint32_t x = 0;
    while (x < temp.size()){
        IV = algo ->encrypt(IV);
        out += unhexlify(makehex(integer(hexlify(IV), 16) ^ integer(hexlify(temp.substr(x, blocksize)), 16), blocksize << 1));
        x += blocksize;
    }
    return out;
}

std::string OFB::decrypt(const std::string & data){
    std::string out = "";
    std::string IV = const_IV;
    uint32_t x = 0;
    while (x < data.size()){
        IV = algo -> encrypt(IV);
        out += unhexlify(makehex(integer(hexlify(IV), 16) ^ integer(hexlify(data.substr(x, blocksize)), 16), blocksize << 1));
        x += blocksize;
    }
    return out;
}
