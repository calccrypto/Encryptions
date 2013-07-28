#include "./CTR.h"

CTR::CTR(SymAlg * instance, std::string iv)
  : algo(instance) {
    blocksize = algo -> blocksize() >> 3;
    const_IV = iv;
    if (const_IV == ""){
        const_IV = std::string(blocksize, '\x00');
    }
}

std::string CTR::encrypt(std::string data){
    data = pkcs5(data, blocksize);
    std::string out = "";
    std::string IV = const_IV;
    while (data.size()){
        out += unhexlify(makehex(integer(hexlify(algo -> encrypt(IV)), 16) ^ integer(hexlify(data.substr(0, blocksize)), 16), blocksize << 1));
        data = data.substr(blocksize, data.size() - blocksize);
        IV = unhexlify(makehex(integer(hexlify(IV), 16) + 1, blocksize << 1));
    }
    return out;
}

std::string CTR::decrypt(std::string data){
    std::string out = "";
    std::string IV = const_IV;
    while (data.size()){
        out += unhexlify(makehex(integer(hexlify(algo -> encrypt(IV)), 16) ^ integer(hexlify(data.substr(0, blocksize)), 16), blocksize << 1));
        data = data.substr(blocksize, data.size() - blocksize);
        IV = unhexlify(makehex(integer(hexlify(IV), 16) + 1, blocksize << 1));
    }
    return remove_padding(out);
}
