#include "CBC.h"

CBC::CBC(SymAlg * instance, std::string iv)
  : algo(instance) {
    blocksize = algo -> blocksize() >> 3;
    const_IV = iv;
    if (const_IV == ""){
        const_IV = std::string(blocksize, '\x00');
    }
}

std::string CBC::encrypt(std::string data){
    data = pkcs5(data, blocksize);
    std::string out = "";
    std::string IV = const_IV;
    while (data.size()){
        IV = algo -> encrypt(unhexlify(makehex(integer(hexlify(data.substr(0, blocksize)), 16) ^ integer(hexlify(IV), 16), blocksize << 1)));
        out += IV;
        data = data.substr(blocksize, data.size() - blocksize);
    }
    return out;
}

std::string CBC::decrypt(std::string data){
    std::string out = "";
    std::string IV = const_IV;
    while (data.size()){
        out += unhexlify(makehex(integer(hexlify(algo -> decrypt(data.substr(0, blocksize))), 16) ^ integer(hexlify(IV), 16), blocksize << 1));
        IV = data.substr(0, blocksize);
        data = data.substr(blocksize, data.size() - blocksize);
    }
    return remove_padding(out);
}
