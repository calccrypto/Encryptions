#include "./CFB.h"
CFB::CFB(SymAlg * instance, const std::string & iv)
  : algo(instance) {
    blocksize = algo -> blocksize() >> 3;
    const_IV = iv;
    if (const_IV == ""){
        const_IV = std::string(blocksize, 0);
    }
}

std::string CFB::encrypt(const std::string & data){
    std::string temp = pkcs5(data, blocksize);
    std::string out = "";
    std::string IV = const_IV;
    uint32_t x = 0;
    while (x < temp.size()){
        IV = unhexlify(makehex(integer(hexlify(algo -> encrypt(IV)), 16) ^ integer(hexlify(temp.substr(x, blocksize)), 16), blocksize << 1));
        out += IV;
        x += blocksize;
    }
    return out;
}

std::string CFB::decrypt(const std::string & data){
    std::string out = "";
    std::string IV = const_IV;
    uint32_t x = 0;
    while (data.size()){
        out += unhexlify(makehex(integer(hexlify(algo -> encrypt(IV)), 16) ^ integer(hexlify(data.substr(x, blocksize)), 16), blocksize << 1));
        IV = data.substr(x, blocksize);
        x += blocksize;
    }
    return remove_padding(out);
}
